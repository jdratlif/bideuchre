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
 
// $Id: TextPlayer.hh,v 1.1.1.1 2005/08/06 09:52:53 technoplaza Exp $

#ifndef _TEXTPLAYER_HH_
#define _TEXTPLAYER_HH_

#include "engine/Player.hh"

/**
 * Text interface for a Player.
 */
class TextPlayer : public Player {
private:
    static const wxString TRICK_CHOICES[];
    static const wxString TRUMP_CHOICES[];

public:
    /**
     * Creates a new TextPlayer.
     *
     * @param id The Player ID.
     */
    TextPlayer(int id);
    
    /**
     * Creates a new TextPlayer.
     *
     * @param id The Player ID.
     * @param name The TextPlayer's name.
     */
    TextPlayer(int id, const wxString &name);

    /**
     * Plays a Card on a Trick.
     *
     * @param trick The Trick.
     */
    void playCard(Trick &trick);
    
    /**
     * Makes a Bid for the next round.
     *
     * @param bids The BidHistory.
     */
    void bid(BidHistory &bids);
    
    /**
     * Gives a Card to the bidder going alone.
     *
     * @param bid The Bid.
     */
    void giveLonerCard(const Bid &bid);
    
    /**
     * Discards extra cards when going alone.
     *
     * @param bid The Bid.
     */
    void discard(const Bid &bid);
};

inline TextPlayer::TextPlayer(int id) : Player(id) {}
inline TextPlayer::TextPlayer(int id, const wxString &name) : Player(id, name) {}

#endif

