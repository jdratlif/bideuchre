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
 
// $Id: RoundHistory.cc,v 1.4 2005/08/11 08:28:44 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "model/RoundHistory.hh"

RoundHistory *RoundHistory::singleton = NULL;

RoundHistory &RoundHistory::instance() {
    if (singleton == NULL) {
        singleton = new RoundHistory;
    }
    
    return *singleton;
}

void RoundHistory::startRound() {
    played.clear();
    lead = 0;
}

void RoundHistory::startTrick(const Trick *trick) {
    this->trick = trick;
    plays = 0;
}

void RoundHistory::endTrick() {
    lead |= (1 << trick->getLead().getSuit(trick->getBid().getTrump()));
}

void RoundHistory::add(const Play &play) {
    // add the card to the played vector
    played.push_back(play.getCard());
    ++plays;
}

