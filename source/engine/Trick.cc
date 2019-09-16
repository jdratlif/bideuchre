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
 
// $Id: Trick.cc,v 1.1.1.1 2005/08/06 09:52:50 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "engine/Player.hh"
#include "engine/Trick.hh"
#include "bridge/Bridge.hh"

Trick::Trick(Bridge *bridge, const Bid &bid, int first) : bid(bid), 
                                                          bridge(bridge),
                                                          first(first) {
    bridge->startTrick(this);
}

void Trick::play(const Play &play) {
    if (play.getPlayer()->getID() == first) {
        lead = play.getCard();
    }
    
    Winner current(play, score(play.getCard()));

    if (current.compareTo(winner) > 0) {
        winner = current;
    }
    
    plays.push_back(play);
    bridge->play();
}

int Trick::score(const Card &card) const {
    int score = 0;
    enum Suit trump = bid.getTrump();
    enum Suit suit = card.getSuit(trump);
    enum Face face = card.getFace();
    
    if (face == ACE) {
        score += ((trump != LOW) ? 600 : 100);
    } else if (face == KING) {
        score += ((trump != LOW) ? 500 : 200);
    } else if (face == QUEEN) {
        score += ((trump != LOW) ? 400 : 300);
    } else if (face == TEN) {
        score += ((trump != LOW) ? 200 : 500);
    } else if (face == NINE) {
        score += ((trump != LOW) ? 100 : 600);
    } else {
        if (card.isBower(trump, EUCHRE_RIGHT_BOWER)) {
            score += 800;
        } else if (card.isBower(trump, EUCHRE_LEFT_BOWER)) {
            score += 700;
        } else {
            score += ((trump != LOW) ? 300 : 400);
        }
    }
    
    if (suit == trump) {
        score += 2000;
    } else if (suit == lead.getSuit(trump)) {
        score += 1000;
    }
    
    return score;
}

