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
 
// $Id: Player.cc,v 1.2 2005/08/08 10:22:58 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "model/BidHistory.hh"
#include "model/Card.hh"
#include "model/Deck.hh"
#include "engine/Player.hh"
#include "engine/Trick.hh"

const wxString Player::NAMES[] =
    {
        wxT("David"), wxT("Elton"), wxT("Thelma"),
        wxT("Geri"), wxT("Keith"), wxT("Dixie")
    };

void Player::giveCard(Player *player, int card) {
    player->hand.add(hand[card]);
    hand.remove(card);
}

bool Player::isValidPlay(const Card &card, const Trick &trick) {
    enum Suit trump = trick.getBid().getTrump();
    enum Suit leadSuit = trick.getLead().getSuit(trump);
    
    if (hand.hasSuit(leadSuit, trump)) {
        return (card.getSuit(trump) == leadSuit);
    }
    
    return true;
}

void Player::deal(Deck &deck, Player **player) {
    int card = 0;
    
    deck.shuffle();
    
    for (int i = 0; i < 6; i++) {
        player[i]->hand.clear();
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            int dealee = (j + id + 1) % 6;
            
            for (int deal = 0; deal < ((i < 2) ? 3 : 2); deal++) {
                player[dealee]->hand.add(deck[card++]);
            }
        }
    }
    
    for (int i = 0; i < 6; i++) {
        player[i]->hand.sort(HIGH);
    }
}

