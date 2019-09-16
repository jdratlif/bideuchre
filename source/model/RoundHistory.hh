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
 
// $Id: RoundHistory.hh,v 1.1 2005/08/08 12:00:37 technoplaza Exp $

#ifndef _ROUNDHISTORY_HH_
#define _ROUNDHISTORY_HH_

#include <vector>

#include "model/Card.hh"
#include "engine/Round.hh"
#include "engine/Trick.hh"

/**
 * Class used to track and query the history of plays in a Round.
 */
class RoundHistory {
private:
    std::vector<Card> played;
    
    static RoundHistory *singleton;
    
    /// declare Round::start() a friend
    friend void Round::start();
    
    /// declare Trick::play() a friend
    friend void Trick::play(const Play &play);
    
    /**
     * Creates a new RoundHistory. Private to disallow instantiation; we are a
     * singleton.
     */
    RoundHistory();
    
    /**
     * Resets this RoundHistory.
     */
    void reset();
    
    /**
     * Adds a Play to this RoundHistory.
     *
     * @param play The Play.
     */
    void add(const Play &play);
public:
    /**
     * Destructor for a RoundHistory.
     */
    ~RoundHistory();
    
    /**
     * Gets the singleton RoundHistory instance.
     */
    static RoundHistory &instance();
};

inline RoundHistory::RoundHistory() {}
inline RoundHistory::~RoundHistory() { delete singleton; }
inline RoundHistory &RoundHistory::instance() { return *singleton; }

#endif

