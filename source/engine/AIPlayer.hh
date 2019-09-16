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
 
// $Id: AIPlayer.hh,v 1.1.1.1 2005/08/06 09:52:50 technoplaza Exp $

#ifndef _AIPLAYER_HH_
#define _AIPLAYER_HH_

#include "engine/Player.hh"

class AIPlayer : public Player {
private:
    /**
     * Scores a Card according to trump.
     *
     * @param card The Card.
     * @param trump The trump suit.
     *
     * @return The card score.
     */
    int score(const Card &card, enum Suit trump);

    /**
     * Gets the index of the bower card specified.
     *
     * @param trump The trump suit.
     * @param bower The bower to get.
     *
     * @return The card index, or -1 if no such card is found.
     */
    int getBower(enum Suit trump, enum Bower bower = EUCHRE_ANY_BOWER);
    
    /**
     * Gets the index of a high lead card.
     *
     * @param trump The trump suit.
     *
     * @return The card index, or -1 if not such card is found.
     */
    int getHigh(enum Suit trump);
    
    /**
     * Checks if the current winning card is likely to take the trick.
     *
     * @param trick The trick.
     *
     * @return true if the winning card should take the trick; false otherwise.
     */
    bool isTrickTaker(Trick &trick);
    
    /**
     * Checks if the player should try and take the trick.
     *
     * @param trick The trick.
     *
     * @return true if the player should take the trick; false otherwise.
     */
    bool shouldTake(Trick &trick);
    
    /**
     * Gets the index of a card that will take the trick.
     *
     * @param trick The trick.
     *
     * @return The card index, or -1 if no such card is found.
     */
    int getTake(Trick &trick);
    
    /**
     * Gets a loser card from the player's hand.
     *
     * @param trick The Trick to play on.
     *
     * @return The loser card index.
     */
    int getLoser(Trick &trick);
    
    /**
     * Counts the number of trump in this AIPlayer's hand.
     *
     * @param trump The trump suit.
     *
     * @return The number of trump cards.
     */
    int countTrump(enum Suit trump);
    
    /**
     * Counts the number of high off-trump cards.
     *
     * @param trump The trump suit.
     *
     * @return The number of high off-trump cards.
     */
    int countHigh(enum Suit trump);
    
public:
    /**
     * Creates a new AIPlayer.
     *
     * @param id The player id.
     */
    AIPlayer(int id);
    
    /**
     * Creates a new AIPlayer.
     *
     * @param id The player id.
     * @param name The player's name.
     */
    AIPlayer(int id, const wxString &name);
    
    /**
     * Plays a Card on the Trick.
     *
     * @param trick The Trick to play on.
     */
    void playCard(Trick &trick);
    
    /**
     * Makes a Bid for the next round.
     *
     * @param bids The BidHistory.
     *
     * @return The Bid.
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

inline AIPlayer::AIPlayer(int id) : Player(id) {}
inline AIPlayer::AIPlayer(int id, const wxString &name) : Player(id, name) {}
inline void AIPlayer::discard(const Bid &) {}

#endif

