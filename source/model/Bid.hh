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
 
// $Id: Bid.hh,v 1.1.1.1 2005/08/06 09:52:50 technoplaza Exp $

#ifndef _BID_HH_
#define _BID_HH_

#include <cstdio>

#include "model/ModelConstants.hh"

class wxString;
class Player;

/**
 * Class to represent a bid in Bid Euchre.
 */
class Bid {
private:
    const Player *player;
    enum Suit trump;
    int tricks;
    bool alone;
    
public:
    /**
     * Creates a new Bid.
     *
     * @param player The Player who made this Bid.
     * @param tricks The number of tricks bid.
     * @param trump The trump suit value.
     * @param alone Whether this is a loner Bid.
     */
    Bid(const Player *player = NULL, int tricks = 0, 
        enum Suit trump = SPADES, bool alone = false);
    
    /**
     * Gets the Player who made this Bid.
     *
     * @return The Player.
     */
    const Player *getPlayer() const;
    
    /**
     * Gets the trump suit.
     *
     * @return The trump suit.
     */
    enum Suit getTrump() const;
    
    /**
     * Sets the trump suit.
     *
     * @param trump The new trump suit.
     */
    void setTrump(enum Suit trump);
    
    /**
     * Gets the number of tricks bid.
     *
     * @return The number of tricks.
     */
    int getTricks() const;
    
    /**
     * Sets the number of tricks bid.
     *
     * @param tricks The new number of tricks.
     */
    void setTricks(int tricks);
    
    /**
     * Checks if this Bid is a loner Bid or not.
     *
     * @return true if this is a loner Bid; false otherwise.
     */
    bool isAlone() const;
    
    /**
     * Sets whether this Bid is alone or not.
     *
     * @param alone true if alone; false otherwise.
     */
    void setAlone(bool alone);
    
    /**
     * Compares this Bid to another Bid. Returns 0 if they are equal, less than
     * 0 if this Bid is less than the given one, or greater than 0 if this bid
     * is higher than the given one.
     *
     * @param bid The other Bid.
     *
     * @return The comparison value.
     */
    int compareTo(const Bid &bid) const;
    
    /**
     * Gets the team string for this Bid. ("Us" or "Them")
     *
     * @return The team string.
     */
    wxString getTeamString() const;
    
    /**
     * Gets a string of this Bid in the form (tricks trump), e.g. (6 Spades).
     *
     * @return The string bid.
     */
    wxString getBidString() const;
    
    /**
     * Returns a string representation of this Bid.
     *
     * @return A string representation.
     */
    wxString toString() const;
};

inline Bid::Bid(const Player *player, int tricks, enum Suit trump, bool alone) : 
                player(player), trump(trump), tricks(tricks), alone(alone) {}
inline const Player *Bid::getPlayer() const { return player; }
inline enum Suit Bid::getTrump() const { return trump; }
inline void Bid::setTrump(enum Suit trump) { this->trump = trump; }
inline int Bid::getTricks() const { return tricks; }
inline void Bid::setTricks(int tricks) { this->tricks = tricks; }
inline bool Bid::isAlone() const { return alone; }
inline void Bid::setAlone(bool alone) { this->alone = alone; }

#endif

