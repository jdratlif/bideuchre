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
 
// $Id: Trick.hh,v 1.2 2005/08/09 04:04:07 technoplaza Exp $

#ifndef _TRICK_HH_
#define _TRICK_HH_

#include <vector>

#include "model/Bid.hh"
#include "model/Card.hh"
#include "model/Play.hh"
#include "model/Winner.hh"

class Player;
class Bridge;

/**
 * Class representing a single trick in a Bid Euchre round.
 */
class Trick {
private:
    std::vector<Play> plays;
    const Bid &bid;
    Card lead;
    Winner winner;
    Bridge *bridge;
    int first;

public:
    /**
     * Create a new Trick object.
     *
     * @param bridge The Bridge.
     * @param bid The Bid.
     * @param first The first player.
     */
    Trick(Bridge *bridge, const Bid &bid, int first);
    
    /**
     * Plays on this Trick.
     *
     * @param play The play.
     */
    void play(const Play &play);
    
    /**
     * Checks if the next person to play on this Trick is the lead player.
     *
     * @return true if they are the lead; false otherwise.
     */
    bool isFirstPlayer() const;
    
    /**
     * Checks if the next person to play on this Trick is the last player.
     *
     * @return true if they are the last player; false otherwise.
     */
    bool isLastPlayer() const;
    
    /**
     * Gets the Winner of this Trick
     *
     * @return The Winner.
     */
    const Winner &getWinner() const;
    
    /**
     * Gets the lead Card played on this Trick.
     *
     * @return The lead Card.
     */
    const Card &getLead() const;
    
    /**
     * Gets the bid for this Trick.
     *
     * @return The bid.
     */
    const Bid &getBid() const;
    
    /**
     * Gets the plays for this Trick.
     *
     * @return The play vector.
     */
    const std::vector<Play> &getPlayHistory() const;
    
    /**
     * Gets the trick score for a Card.
     *
     * @param card The Card to score.
     *
     * @return The score.
     */
    int score(const Card &card) const;
};

inline bool Trick::isFirstPlayer() const { return (plays.size() == 0); }
inline bool Trick::isLastPlayer() const { return (plays.size() == (bid.isAlone() ? 3 : 5)); }
inline const Winner &Trick::getWinner() const { return winner; }
inline const Card &Trick::getLead() const { return lead; }
inline const Bid &Trick::getBid() const { return bid; }
inline const std::vector<Play> &Trick::getPlayHistory() const { return plays; }

#endif

