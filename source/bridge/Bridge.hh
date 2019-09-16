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
 
// $Id: Bridge.hh,v 1.1.1.1 2005/08/06 09:52:49 technoplaza Exp $

#ifndef _BRIDGE_HH_
#define _BRIDGE_HH_

#include <cstdio>

#include "engine/Game.hh"
#include "ui/UI.hh"

class Round;
class Trick;

/**
 * Abstract bridge used to pass messages between the UI and game.
 */
class Bridge {
protected:
    const Round *round;
    const Trick *trick;
    UI *ui;
    
    /// declare the Game::stop() method a friend
    friend void Game::stop();
    
public:
    /**
     * Creates a new Bridge.
     */
    Bridge();
    
    /**
     * Gets the Round used by this Bridge.
     *
     * @return The Round.
     */
    const Round *getRound() const;
    
    /**
     * Gets the Trick used by this Bridge.
     *
     * @return The Trick.
     */
    const Trick *getTrick() const;
    
    /**
     * Sets the UI used by this Bridge.
     *
     * @param ui The UI.
     */
    void setUI(UI *ui);
    
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
     *
     * @param round The Round.
     */
    void startRound(const Round *round);
    
    /**
     * Called when a round has ended.
     */
    void endRound();
    
    /**
     * Called when a trick is started.
     *
     * @param trick The Trick.
     */
    void startTrick(const Trick *trick);
    
    /**
     * Called when a trick has ended.
     */
    void endTrick();
    
    /**
     * Called when a card is played.
     */
    void play();
};

inline Bridge::Bridge() : round(NULL), trick(NULL), ui(NULL) {}
inline const Round *Bridge::getRound() const { return round; }
inline const Trick *Bridge::getTrick() const { return trick; }
inline void Bridge::setUI(UI *ui) { this->ui = ui; }
inline void Bridge::startGame() { ui->startGame(); }
inline void Bridge::endGame() { ui->endGame(); }
inline void Bridge::deal() { ui->deal(); }
inline void Bridge::startBidding() { ui->startBidding(); }
inline void Bridge::bid() { ui->bid(); }
inline void Bridge::endBidding() { ui->endBidding(); }
inline void Bridge::play() { ui->play(); }

#endif

