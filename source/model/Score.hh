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
 
// $Id: Score.hh,v 1.1.1.1 2005/08/06 09:52:51 technoplaza Exp $

#ifndef _SCORE_HH_
#define _SCORE_HH_

#include "model/Bid.hh"

class wxString;
class Player;

/**
 * A class to encapsulate the score for a round.
 */
class Score {
private:
    Bid bid;
    const Player *dealer;
    int score[2];
    
public:
    /**
     * Create a new Score.
     *
     * @param dealer The dealer.
     * @param bid The Bid.
     * @param us The score for 'us' team.
     * @param them The score for 'them' team.
     */
    Score(const Player *dealer, const Bid &bid, int us, int them);
    
    /**
     * Gets the dealer.
     *
     * @return The dealer.
     */
    const Player *getDealer() const;
    
    /**
     * Gets the Bid.
     *
     * @return The Bid.
     */
    const Bid &getBid() const;
    
    /**
     * Gets a team score.
     *
     * @param team The team number (0 or 1).
     *
     * @return The score.
     */
    int getScore(int team) const;
    
    /**
     * Returns a wxString representation of this Score.
     *
     * @return A wxString representation.
     */
    wxString toString() const;
};

inline const Player *Score::getDealer() const { return dealer; }
inline const Bid &Score::getBid() const { return bid; }
inline int Score::getScore(int team) const { return score[team]; }

#endif

