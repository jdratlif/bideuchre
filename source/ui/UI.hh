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
 
// $Id: UI.hh,v 1.9 2005/07/28 11:30:22 technoplaza Exp $

#ifndef _UI_HH_
#define _UI_HH_

#include <cstdio>

class Bridge;

/**
 * Abstraction to provide a user interface (display) for the game engine using
 * the Bridge.
 */
class UI {
protected:
    Bridge *bridge;
    
public:
    /**
     * Creates a new UI object.
     */
    UI();

    /**
     * Sets the Bridge used by this UI.
     *
     * @param bridge The Bridge.
     */
    void setBridge(Bridge *bridge);
    
    /**
     * Called when a game is started.
     */
    virtual void startGame() = 0;
    
    /**
     * Called when a game has ended.
     */
    virtual void endGame() = 0;
    
    /**
     * Called when the cards have been dealt.
     */
    virtual void deal() = 0;
    
    /**
     * Called when bidding is started.
     */
    virtual void startBidding() = 0;
    
    /**
     * Called when a new bid is made.
     */
    virtual void bid() = 0;
    
    /**
     * Called when bidding has ended.
     */
    virtual void endBidding() = 0;
    
    /**
     * Called when a round is started.
     */
    virtual void startRound() = 0;
    
    /**
     * Called when a round has ended.
     */
    virtual void endRound() = 0;
    
    /**
     * Called when a trick is started.
     */
    virtual void startTrick() = 0;
    
    /**
     * Called when a trick has ended.
     */
    virtual void endTrick() = 0;
    
    /**
     * Called when a card is played.
     */
    virtual void play() = 0;
};

inline UI::UI() : bridge(NULL) {}
inline void UI::setBridge(Bridge *bridge) { this->bridge = bridge; }

#endif

