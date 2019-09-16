/*
 * Bid Euchre
 * Copyright (C) 2005 John David Ratliff
 * http://bideuchre.sourceforge.net/
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
 
// $Id: Hand.cc,v 1.11 2005/07/29 04:27:33 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "model/Hand.hh"

int Hand::score(int index, enum Suit trump) const {
    Card card = hand[index];
    int score = 0;
    enum Suit suit = card.getSuit(trump);
    enum Face face = card.getFace();
    
    if (suit == SPADES) {
        score += 4000;
    } else if (suit == DIAMONDS) {
        score += 3000;
    } else if (suit == CLUBS) {
        score += 2000;
    } else {
        score += 1000;
    }
    
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
    
    return score;
}

void Hand::remove(int index) {
    for (int i = index; i < (count - 1); i++) {
        hand[i] = hand[i + 1];
    }
    
    --count;
}

bool Hand::hasSuit(enum Suit suit, enum Suit trump) const {
    for (int i = 0; i < count; i++) {
        if (hand[i].getSuit(trump) == suit) {
            return true;
        }
    }
    
    return false;
}

void Hand::sort(enum Suit trump) {
    for (int i = (count - 1); i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            int a = score(j, trump);
            int b = score((j + 1), trump);
            
            if (a < b) {
                Card temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            }
        }
    }
}

