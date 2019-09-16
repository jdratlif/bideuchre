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
 
// $Id: TextUI.cc,v 1.1.1.1 2005/08/06 09:52:53 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <iostream>
#include <vector>
#include <cstdio>

#include "model/Bid.hh"
#include "model/BidHistory.hh"
#include "model/Score.hh"
#include "engine/Game.hh"
#include "engine/Round.hh"
#include "engine/Trick.hh"
#include "bridge/Bridge.hh"
#include "ui/TextUI.hh"

using std::cout;

void TextUI::bid() {
    const BidHistory &bids = bridge->getRound()->getBidHistory();
    
    cout << "---------------------------------------------\n";
    cout << "| Bid History\n";
    cout << "---------------------------------------------\n";
    
    for (unsigned int i = 0; i < bids.size(); i++) {
        const Bid &bid = bids.get(i);
        cout << "| " << bid.toString().c_str() << '\n';
    }
    
    cout << "---------------------------------------------\n\n";
}

void TextUI::play() {
    const std::vector<Play> &plays = bridge->getTrick()->getPlayHistory();
    
    cout << "---------------------------------------------\n";
    cout << "| Trick Recap\n";
    cout << "---------------------------------------------\n";
    
    for (unsigned int i = 0; i < plays.size(); i++) {
        cout << "| " << plays[i].toString().c_str() << '\n';
    }
    
    cout << "---------------------------------------------\n\n";
}

void TextUI::endTrick() {
    int us = bridge->getRound()->getTricks(0);
    int them = bridge->getRound()->getTricks(1);
    
    cout << "---------------------------------------------\n";
    cout << "| Trick Count [ Us: " << us << " Them: " << them << " ]\n";
    cout << "---------------------------------------------\n\n";
}

void TextUI::endRound() {
    const std::vector<Score> &scores = Game::getInstance().getScoreHistory();

    cout << "---------------------------------------------\n";
    cout << "| Dealer     Us   Them   Bid\n";
    
    for (unsigned int i = 0; i < scores.size(); i++) {
        cout << "| " << scores[i].toString().c_str() << '\n';
    }
    
    cout << "---------------------------------------------\n\n";
}

void TextUI::endGame() {
    bool us = Game::getInstance().isWinner(0);
    
    cout << "---------------------------------------------\n";
    cout << "| Winner: " << (us ? "Us" : "Them") << '\n';
    cout << "---------------------------------------------\n\n";
}

