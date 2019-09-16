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
 
// $Id: Game.cc,v 1.1.1.1 2005/08/06 09:52:50 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <cstring>

#include "AppConstants.hh"
#include "model/Bid.hh"
#include "model/BidHistory.hh"
#include "model/Score.hh"
#include "engine/Game.hh"
#include "engine/Round.hh"
#include "bridge/Bridge.hh"

Game *Game::singleton = new Game;

Game::Game() : thread(NULL), dealer(0), players(0), 
               paused(false), playing(false) {
    memset(player, 0, 6 * sizeof(Player *));
    memset(teamScore, 0, 2 * sizeof(unsigned int));
}

Game::~Game() {
    stop();
    
    delete this;
}

void Game::score(Round &round) {
    int bidder = bid.getPlayer()->getID() % 2;
    int other = (bidder == 0) ? 1 : 0;
    
    teamScore[other] += round.getTricks(other);
    
    int bonus = (bid.isAlone() ? 8 : 0);
    
    if (round.getTricks(bidder) >= bid.getTricks()) {
        teamScore[bidder] += (round.getTricks(bidder) + bonus);
    } else {
        teamScore[bidder] -= (bid.getTricks() + bonus);
    }
}

bool Game::isWinner(int id) const {
    const int target = 54;
    int a = teamScore[id];
    int b = teamScore[(id == 0) ? 1 : 0];
    
    if ((a >= target) && (b < target)) {
        return true;
    }
    
    if (b <= -target) {
        return true;
    }
    
    if ((a >= target) && (b >= target)) {
        return ((bid.getPlayer()->getID() % 2) == id);
    }
    
    return false;
}

void Game::play() {
    bridge->startGame();
    
    teamScore[0] = teamScore[1] = 0;

    while (!hasWinner()) {
        mutex->Lock();
        
        while (paused && playing) {
            cond->Wait();
        }
        
        mutex->Unlock();
        
        if (!playing) {
            return;
        }
        
        player[dealer]->deal(deck, player);
        bridge->deal();
        
        Round round(bridge, player);
        bridge->startBidding();
        round.bid(((dealer + 1) < 6) ? (dealer + 1) : 0);
        bid = round.getBidHistory().getWinning();
        
        if (!playing) {
            return;
        }
        
        if (bid.getTricks() == 0) {
            bridge->endBidding();
            bridge->endRound();
            dealer = (++dealer < 6) ? dealer : 0;
            continue;
        }
        
        for (int i = 0; i < 6; i++) {
            player[i]->sortHand(bid.getTrump());
        }
        
        bridge->endBidding();
        round.start();
        
        if (!playing) {
            return;
        }
        
        score(round);
        scores.push_back(Score(player[dealer], bid, 
                               teamScore[0], teamScore[1]));
        bridge->endRound();
        
        dealer = (++dealer < 6) ? dealer : 0;
    }
    
    bridge->endGame();
}

void Game::start(Bridge *bridge) {
    stop();
    
    if (!playing) {
        playing = true;
        this->bridge = bridge;
        scores.clear();
        
        thread = new GameThread(this);
        thread->Run();
    }
}

void Game::stop() {
    if (playing) {
        mutex->Lock();
        
        playing = false;
        bridge->trick = NULL;
        bridge->round = NULL;
        
        mutex->Unlock();
        cond->Signal();
        
        thread->Wait();
        delete thread;
        thread = NULL;
    }
}

void Game::setPause(bool paused) {
    this->paused = paused;
    cond->Signal();
}

void Game::addPlayer(Player *player) {
    int id = player->getID();
    
    if (this->player[id] == NULL) {
        players++;
    }
    
    this->player[id] = player;
}

