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
 
// $Id: Round.cc,v 1.1.1.1 2005/08/06 09:52:50 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/thread.h>
#include <wx/utils.h>

#include "model/Bid.hh"
#include "engine/Game.hh"
#include "engine/Player.hh"
#include "engine/Round.hh"
#include "engine/Trick.hh"
#include "bridge/Bridge.hh"

Round::Round(Bridge *bridge, Player **player) : player(player), bridge(bridge) {
    tricks[0] = tricks[1] = 0;
    bridge->startRound(this);
}

void Round::bid(int first) {
    bids = BidHistory();
    
    for (int i = 0; i < 6; i++) {
        int bidder = (first + i) % 6;
        player[bidder]->bid(bids);
        
        if (!Game::getInstance().isPlaying()) {
            return;
        }
       
        const Bid &bid = bids.getLast();
        bridge->bid();
        
        if (bid.isAlone()) {
            int a = (bidder + 2) % 6;
            int b = (bidder + 4) % 6;
            
            player[a]->sortHand(bid.getTrump());
            player[a]->giveLonerCard(bid);
            
            player[b]->sortHand(bid.getTrump());
            player[b]->giveLonerCard(bid);
            
            player[bidder]->sortHand(bid.getTrump());
            player[bidder]->discard(bid);
            
            break;
        }
    }
}

void Round::start() {
    const Bid &winning = bids.getWinning();
    int first = winning.getPlayer()->getID();

    for (int i = 0; i < 8; i++) {
        Trick trick(bridge, winning, first);
        
        for (int j = 0; j < 6; j++) {
            int next = (first + j) % 6;
            
            if (winning.isAlone()) {
                int id = winning.getPlayer()->getID();
                
                if ((id != next) && 
                    (player[next]->getTeam() == player[id]->getTeam())) {
                    continue;
                }
            }
            
            player[next]->playCard(trick);
            
            if (!Game::getInstance().isPlaying()) {
                return;
            }
        }
        
        const Winner &winner = trick.getWinner();
        first = winner.getPlay().getPlayer()->getID();
        tricks[first % 2]++;
        
        bridge->endTrick();
    }
}

