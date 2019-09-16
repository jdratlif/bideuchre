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
 
// $Id: GUIPlayer.hh,v 1.11 2005/08/01 03:52:05 technoplaza Exp $

#ifndef _GUIPLAYER_HH_
#define _GUIPLAYER_HH_

#include <queue>
#include <utility>

#include "engine/Player.hh"

/**
 * A class used to represent a player with a graphical interface.
 */
class GUIPlayer : public Player {
private:
    std::queue< std::pair<wxPoint, bool> > clicks;
    GamePanel *panel;
    
    static const wxString BEST_NAMES[];
    
    /**
     * Waits for a card to be selected and returns the card index.
     *
     * @return The card index.
     */
    std::pair<int, bool> getCard();
    
public:
    /**
     * Creates a new GUIPlayer.
     *
     * @param panel The GamePanel.
     * @param id The Player ID.
     */
    GUIPlayer(GamePanel *panel, int id);
    
    /**
     * Creates a new GUIPlayer.
     *
     * @param panel The GamePanel.
     * @param id The Player ID.
     * @param name The GUIPlayer's name.
     */
    GUIPlayer(GamePanel *panel, int id, const wxString &name);
    
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

inline GUIPlayer::GUIPlayer(GamePanel *panel, int id) : 
                            Player(id), panel(panel) {}
inline GUIPlayer::GUIPlayer(GamePanel *panel, int id, const wxString &name) : 
                            Player(id, name), panel(panel) {}

#endif

