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

// $Id: Hand.hh,v 1.12 2005/07/29 04:27:33 technoplaza Exp $

#ifndef _HAND_HH_
#define _HAND_HH_

#include "model/Card.hh"

/**
 * Class representing the cards in a player's hand.
 */
class Hand {
private:
    Card hand[10];
    int count;
    
    /**
     * Scores a card in the Hand according to trump. Used for sorting.
     *
     * @param index The Card index to score.
     * @param trump The trump suit value.
     *
     * @return The score.
     */
    int score(int index, enum Suit trump) const;

public:
    /**
     * Creates a new Hand object.
     */
    Hand();
    
    /**
     * Adds a Card to this Hand.
     *
     * @param card The Card to add.
     */
    void add(const Card &card);
    
    /**
     * Gets a Card from this Hand.
     *
     * @param index The Card index.
     *
     * @return The selected Card.
     */
    const Card &get(int index) const;
    
    /**
     * Removes a Card from this Hand.
     *
     * @param index The Card index.
     */
    void remove(int index);
    
    /**
     * Empties this Hand of all cards.
     */
    void clear();
    
    /**
     * Gets the size of this Hand.
     *
     * @return The size (number of Cards).
     */
    unsigned int size() const;
    
    /**
     * Checks if this Hand has a particular suit.
     *
     * @param suit The suit to check.
     * @param trump The trump suit.
     *
     * @return true if the suit is in the Hand; false otherwise.
     */
    bool hasSuit(enum Suit suit, enum Suit trump) const;
    
    /**
     * Sorts the Hand according to trump.
     *
     * @param trump The trump suit.
     */
    void sort(enum Suit trump);
};

inline Hand::Hand() : count(0) {}
inline void Hand::add(const Card &card) { hand[count++] = card; }
inline const Card &Hand::get(int index) const { return hand[index]; }
inline void Hand::clear() { count = 0; }
inline unsigned int Hand::size() const { return count; }

#endif

