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
 
// $Id: Play.hh,v 1.1.1.1 2005/08/06 09:52:51 technoplaza Exp $

#ifndef _PLAY_HH_
#define _PLAY_HH_

#include <cstdio>

#include "model/Card.hh"

class wxString;
class Player;

/**
 * Class to represent a single Play on a Bid Euchre trick.
 */
class Play {
private:
    Card card;
    const Player *player;
    bool signal;
    
public:
    /**
     * Creates a new Play object.
     *
     * @param player The Player.
     * @param card The Card.
     * @param signal true if this Play is a signal; false otherwise.
     */
    Play(const Player *player, const Card &card, bool signal = false);
    
    /**
     * Gets the Player who made this Play.
     *
     * @return The Player.
     */
    const Player *getPlayer() const;
    
    /**
     * Gets the Card.
     *
     * @return The Card.
     */
    const Card &getCard() const;
    
    /**
     * Checks if this Play is a signal or not;
     *
     * @return true if this Play is a signal; false otherwise.
     */
    bool isSignal() const;
    
    /**
     * Returns a String representation of this Play.
     *
     * @return A String representation.
     */
    wxString toString() const;
};

inline Play::Play(const Player *player, const Card &card, bool signal) :
                  card(card), player(player), signal(signal) {}
inline const Player *Play::getPlayer() const { return player; }
inline const Card &Play::getCard() const { return card; }
inline bool Play::isSignal() const { return signal; }

#endif

