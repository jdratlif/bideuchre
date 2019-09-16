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
 
// $Id: Winner.hh,v 1.8 2005/07/31 23:31:07 technoplaza Exp $

#ifndef _WINNER_HH_
#define _WINNER_HH_

#include <cstdio>

#include "model/Play.hh"

/**
 * Class used to identify the winner of a Bid Euchre trick.
 */
class Winner {
private:
    Play *play;
    int score;
    
    /**
     * Initializes this Winner from another Winner object.
     *
     * @param winner The other winner object.
     */
    void init(const Winner &winner);

public:
    /**
     * Creates a new Winner object.
     */
    Winner();

    /**
     * Creates a new Winner object.
     *
     * @param play The Play.
     * @param score This Winner's play score.
     */
    Winner(const Play &play, int score = 0);
    
    /**
     * Copy constructor for a Winner object.
     *
     * @param winner The Winner being copied.
     */
    Winner(const Winner &winner);
    
    /**
     * Destructor for a Winner object.
     */
    ~Winner();
    
    /**
     * Overloaded equality operator.
     *
     * @param winner The winner.
     *
     * @return The Winner object.
     */
    Winner &operator=(const Winner &winner);
    
    /**
     * Gets this Winner's Play.
     *
     * @return The Play.
     */
    const Play &getPlay() const;
    
    /**
     * Gets this Winner's trick score.
     *
     * @return The trick score.
     */
    int getScore() const;
    
    /**
     * Compares this Winner to another and returns 0 if they are equal, less
     * than 0 if this Winner is less, and greater than 0 if this Winner is
     * greater.
     *
     * @param winner The other Winner.
     *
     * @return The comparison value.
     */
    int compareTo(const Winner &winner) const;
};

inline Winner::Winner() : play(NULL), score(0) {}
inline const Play &Winner::getPlay() const { return *play; }
inline int Winner::getScore() const { return score; }
inline int Winner::compareTo(const Winner &winner) const { return (score - winner.score); }

#endif

