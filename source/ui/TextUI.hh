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
 
// $Id: TextUI.hh,v 1.7 2005/07/28 11:30:22 technoplaza Exp $

#ifndef _TEXTUI_HH_
#define _TEXTUI_HH_

#include "ui/UI.hh"

/**
 * Text implementation of the UI abstraction.
 */
class TextUI : public UI {
public:
    /**
     * Creates a new TextUI.
     */
    TextUI();
    
    /**
     * Called when a game is started.
     */
    void startGame();
    
    /**
     * Called when a game has ended.
     */
    void endGame();
    
    /**
     * Called when the cards have been dealt.
     */
    void deal();
    
    /**
     * Called when bidding is started.
     */
    void startBidding();
    
    /**
     * Called when a new bid is made.
     */
    void bid();
    
    /**
     * Called when bidding has ended.
     */
    void endBidding();
    
    /**
     * Called when a round is started.
     */
    void startRound();
    
    /**
     * Called when a round has ended.
     */
    void endRound();
    
    /**
     * Called when a trick is started.
     */
    void startTrick();
    
    /**
     * Called when a trick has ended.
     */
    void endTrick();
    
    /**
     * Called when a card is played.
     */
    void play();
};

inline TextUI::TextUI() : UI() {}
inline void TextUI::startGame() {}
inline void TextUI::deal() {}
inline void TextUI::startBidding() {}
inline void TextUI::endBidding() {}
inline void TextUI::startRound() {}
inline void TextUI::startTrick() {}

#endif

