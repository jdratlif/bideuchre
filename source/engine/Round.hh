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
 
// $Id: Round.hh,v 1.13 2005/07/29 03:35:43 technoplaza Exp $

#ifndef _ROUND_HH_
#define _ROUND_HH_

#include "model/BidHistory.hh"

class Bid;
class Player;
class Bridge;

/**
 * Class used to play a Round of Bid Euchre.
 */
class Round {
private:
    BidHistory bids;
    Player **player;
    Bridge *bridge;
    int tricks[2];

public:
    /**
     * Creates a new Round.
     *
     * @param bridge The Bridge.
     * @param player The Players.
     */
    Round(Bridge *bridge, Player **player);
    
    /**
     * Gets the BidHistory for this Round.
     *
     * @return The BidHistory.
     */
    const BidHistory &getBidHistory() const;

    /**
     * Starts the bidding for this Round.
     *
     * @param first The first bidder.
     */
    void bid(int first);

    /**
     * Starts this Round.
     */
    void start();
    
    /**
     * Gets the number of tricks a team took.
     *
     * @param team The team number.
     *
     * @return The number of tricks took.
     */
    int getTricks(int team) const;
};

inline const BidHistory &Round::getBidHistory() const { return bids; }
inline int Round::getTricks(int team) const { return tricks[team]; }

#endif

