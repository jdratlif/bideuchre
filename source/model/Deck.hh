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
 
// $Id: Deck.hh,v 1.8 2005/07/28 11:30:22 technoplaza Exp $

#ifndef _DECK_HH_
#define _DECK_HH_

#include "model/Card.hh"

/**
 * Class representing a Bid Euchre deck.
 */
class Deck {
private:
    Card deck[48];

public:
    /**
     * Creates a new Deck object.
     */
    Deck();
    
    /**
     * Shuffles this Deck.
     */
    void shuffle();
    
    /**
     * Gets a Card from this Deck.
     *
     * @param index The Card to get.
     *
     * @return The selected Card.
     */
    const Card &getCard(int index) const;
};

inline const Card &Deck::getCard(int index) const { return deck[index]; }

#endif

