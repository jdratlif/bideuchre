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
 
// $Id: Game.hh,v 1.1.1.1 2005/08/06 09:52:50 technoplaza Exp $

#ifndef _GAME_HH_
#define _GAME_HH_

#include <vector>

#include "model/Bid.hh"
#include "model/Deck.hh"
#include "model/Score.hh"
#include "engine/GameThread.hh"
#include "engine/Player.hh"

class Round;
class Bridge;

/**
 * Class used to play a game of Bid Euchre.
 */
class Game {
private:
    std::vector<Score> scores;
    Bid bid;
    Deck deck;
    GameThread *thread;
    Player *player[6];
    Bridge *bridge;
    int dealer, players;
    unsigned int teamScore[2];
    bool paused, playing;
    
    static Game *singleton;
    
    /// Declare GameThread::Entry a friend of the Game
    friend void *GameThread::Entry();
    
    /**
     * Create a new Game. Private to disallow instantiation. Game is a
     * singleton.
     */
    Game();
    
    /**
     * Scores the last Round.
     *
     * @param round The Round.
     */
    void score(Round &round);
    
    /**
     * Called to play the Game.
     */
    void play();
    
public:
    /**
     * Destructor for the Game.
     */
    ~Game();
    
    /**
     * Gets the singleton instance 
     */
    static Game &getInstance();

    /**
     * Add a player to the Game.
     *
     * @param player The Player to add.
     */
    void addPlayer(Player *player);
    
    /**
     * Gets one of the Game's Players.
     *
     * @param index The Player's index.
     *
     * @return The Player.
     */
    const Player *getPlayer(int index) const;
    
    /**
     * Gets the ScoreHistory for the Game.
     *
     * @return The ScoreHistory.
     */
    const std::vector<Score> &getScoreHistory() const;
    
    /**
     * Gets the score for a team.
     *
     * @param id The team id.
     *
     * @return The score.
     */
    int getScore(int id) const;
    
    /**
     * Checks if a team is the winner.
     *
     * @param id The team id.
     *
     * @return true if the Team is the winner; false otherwise.
     */
    bool isWinner(int id) const;
    
    /**
     * Checks if the Game has a Winner.
     *
     * @return true if one team has won; false otherwise.
     */
    bool hasWinner() const;
    
    /**
     * Checks if the Game is paused.
     *
     * @return true if the Game is paused; false otherwise.
     */
    bool isPaused() const;
    
    /**
     * (Un)pauses the Game.
     *
     * @param paused true to pause the Gamse; false to unpause.
     */
    void setPause(bool paused = true);
    
    /**
     * Checks if the Game is being played.
     *
     * @return true if the Game is being played; false otherwise.
     */
    bool isPlaying() const;
    
    /**
     * Starts the Game.
     *
     * @param bridge The Bridge to the UI.
     */
    void start(Bridge *bridge);
    
    /**
     * Stops the Game.
     */
    void stop();
};

inline Game &Game::getInstance() { return *singleton; }
inline const Player *Game::getPlayer(int index) const { return player[index]; }
inline const std::vector<Score> &Game::getScoreHistory() const { return scores; }
inline int Game::getScore(int id) const { return teamScore[id]; }
inline bool Game::hasWinner() const { return (isWinner(0) || isWinner(1)); }
inline bool Game::isPaused() const { return paused; }
inline bool Game::isPlaying() const { return playing; }

#endif

