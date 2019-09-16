/*
 * Bid Euchre
 * Copyright (C) 2005 John David Ratliff
 * http://games.technoplaza.net/
 *
 * This file is part of Bid Euchre.
 *
 * Bid Euchre is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Bid Euchre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bid Euchre; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
 
// $Id: GUIPlayer.cc,v 1.4 2005/08/08 12:00:37 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/thread.h>

#include "AppConstants.hh"
#include "model/Bid.hh"
#include "model/BidHistory.hh"
#include "model/Play.hh"
#include "engine/Game.hh"
#include "engine/Trick.hh"
#include "ui/BidDialog.hh"
#include "ui/GamePanel.hh"
#include "ui/GUIPlayer.hh"

const wxString GUIPlayer::BEST_NAMES[] =
    {
        wxT("Low"), wxT("Spade"), wxT("Diamond"),
        wxT("Club"), wxT("Heart"), wxT("High")
    };

std::pair<int, bool> GUIPlayer::getCard() {
    Game &game = Game::instance();
    unsigned int card;
    bool signal;
    
    for (;;) {
        mutex->Lock();
        
        while (clicks.empty() && game.isPlaying()) {
            cond->Wait();
        }
        
        mutex->Unlock();
        
        if (!game.isPlaying()) {
            return std::pair<int, bool>(0, false);
        }
        
        std::pair<wxPoint, bool> &pair = clicks.front();
        wxPoint &point = pair.first;
        signal = pair.second;
        
        point.x -= GamePanel::HAND_POS[id].x;
        point.y -= GamePanel::HAND_POS[id].y;
        
        if ((id == 1) || (id == 4)) {
            int temp = point.x;
            point.x = point.y;
            point.y = temp;
        }
        
        int maxx = ((hand.size() - 1) * 15) + 71;
        
        if ((point.x < 0) || (point.x > maxx) ||
            (point.y < 0) || (point.y > 96)) {
            clicks.pop();
            continue;
        }
        
        card = point.x / 15;
        
        if (card >= hand.size()) {
            card = hand.size() - 1;
        }
        
        clicks.pop();
        break;
    }
    
    return std::pair<int, bool>(card, signal);
}

void GUIPlayer::playCard(Trick &trick) {
    int index = 0;
    bool signal = false;
    
    if (hand.size() > 1) {
        while (!clicks.empty()) {
            clicks.pop();
        }
        
        panel->requestClicks(&clicks);
        
        wxString str = name + wxT("'s Turn");
        panel->setMessage(str);
        panel->Refresh(false);

        for (;;) {
            std::pair<int, bool> pair = getCard();
            index = pair.first;
            signal = pair.second;
            
            if (!Game::instance().isPlaying()) {
                return;
            }
            
            if (isValidPlay(hand[index], trick)) {
                break;
            }
            
            str = name + wxT(": Must follow suit!");
            panel->setMessage(str);
            panel->Refresh(false);
        }
        
        panel->requestClicks();
    }
    
    Card card = hand[index];
    hand.remove(index);
    
    trick.play(Play(this, card, signal));
}

void GUIPlayer::bid(BidHistory &bids) {
    Bid bid(this);
    BidDialog *dialog = panel->getBidDialog();
    dialog->setBid(&bid);
    
    wxString str = name + wxT("'s Bid");
    dialog->SetTitle(str);
    dialog->setMinimum(bids.getWinning().getTricks() + 1);
    
    wxCommandEvent event(EVT_BID_DIALOG, panel->GetId());
    event.SetEventObject(panel);
    panel->AddPendingEvent(event);
    
    mutex->Lock();
    
    while (dialog->isBidding() && Game::instance().isPlaying()) {
        cond->Wait();
    }
    
    mutex->Unlock();
    
    bids.add(bid);
}

void GUIPlayer::giveLonerCard(const Bid &bid) {
    while (!clicks.empty()) {
        clicks.pop();
    }
    
    panel->requestClicks(&clicks);
    
    wxString str = name + wxT(": Give Best ") + BEST_NAMES[bid.getTrump()];
    panel->setMessage(str);
    panel->Refresh(false);
    
    std::pair<int, bool> pair = getCard();
    int card = pair.first;
    
    if (!Game::instance().isPlaying()) {
        return;
    }

    Player *bidder = const_cast<Player *>(bid.getPlayer());
    giveCard(bidder, card);
    hand.clear();
    
    panel->requestClicks();
}

void GUIPlayer::discard(const Bid &) {
    while (!clicks.empty()) {
        clicks.pop();
    }
    
    panel->requestClicks(&clicks);
    
    wxString str = name + wxT(": Choose Two Discards");
    panel->setMessage(str);
    panel->Refresh(false);
    
    while (hand.size() > 8) {
        std::pair<int, bool> pair = getCard();
        int card = pair.first;
        
        if (!Game::instance().isPlaying()) {
            return;
        }
        
        hand.remove(card);
        
        panel->Refresh(false);
    }
    
    panel->requestClicks();
}

