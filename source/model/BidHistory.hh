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
 
// $Id: BidHistory.hh,v 1.2 2005/08/08 10:22:58 technoplaza Exp $

#ifndef _BIDHISTORY_HH_
#define _BIDHISTORY_HH_

#include "model/Bid.hh"

/**
 * A storage structure for holding the bids of a round.
 */
class BidHistory {
private:
    Bid bids[6];
    int index, winning;
    
public:
    /**
     * Creates a new BidHistory object.
     */
    BidHistory();
    
    /**
     * Adds a Bid to this Bid history.
     */
    void add(const Bid &bid);
    
    /**
     * Gets a Bid from this BidHistory.
     *
     * @param index The index of the Bid.
     *
     * @return The Bid.
     */
    const Bid &operator[](unsigned int index) const;
    
    /**
     * Gets the number of bids in this BidHistory.
     *
     * @return The size (Bid count).
     */
    unsigned int size() const;
    
    /**
     * Gets the current winning Bid.
     *
     * @return The winning Bid.
     */
    const Bid &getWinning() const;
    
    /**
     * Gets the last bid added to this BidHistory.
     *
     * @return The last Bid.
     */
    const Bid &getLast() const;
};

inline BidHistory::BidHistory() : index(-1), winning(0) {}
inline const Bid &BidHistory::operator[](unsigned int index) const { return bids[index]; }
inline unsigned int BidHistory::size() const { return (index + 1); }
inline const Bid &BidHistory::getWinning() const { return bids[winning]; }
inline const Bid &BidHistory::getLast() const { return bids[index]; }

#endif

