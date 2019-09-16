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
 
// $Id: AIPlayer.hh,v 1.6 2005/08/11 08:28:44 technoplaza Exp $

#ifndef _AIPLAYER_HH_
#define _AIPLAYER_HH_

#include <vector>

#include "engine/Player.hh"

class RoundHistory;
class Trick;

class AIPlayer : public Player {
private:
    std::vector<int> plays;
    const Trick *trick;
    
    static RoundHistory &history;

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
     * Finds all the specified bowers in this AIPlayer's hand.
     *
     * @param bower The bower to get.
     */
    void findBower(enum Bower bower = EUCHRE_ANY_BOWER);
    
    /**
     * Finds all the high lead cards.
     */
    void findHigh();
    
    /**
     * Finds all the good lead cards.
     */
    void findLead();
    
    /**
     * Checks if the current winning card is likely to take the trick.
     *
     * @return true if the winning card should take the trick; false otherwise.
     */
    bool isTrickTaker();
    
    /**
     * Checks if the player should try and take the trick.
     *
     * @return true if the player should take the trick; false otherwise.
     */
    bool shouldTake();
    
    /**
     * Finds all the cards that will take the trick.
     *
     * @return true if a trick taker is found; false otherwise.
     */
    bool findTake();
    
    /**
     * Finds all the playable cards.
     */
    void findPlayable();
    
    /**
     * Selects the index of the lowest scored card from the play vector.
     *
     * @return The card index.
     */
    int selectLowest();
    
    /**
     * Selects the index of the highest scored card from the play vector.
     *
     * @return The card index.
     */
    int selectHighest();
    
    /**
     * Selects the index of the best lead card from the play vector.
     *
     * @return The card index.
     */
    int selectBestLead();
    
    /**
     * Selects the index of the lowest trump card.
     *
     * @return The card index.
     */
    int selectLowestTrump();
    
    /**
     * Counts the number of bowers in this AIPlayer's hand.
     *
     * @param trump The trump suit.
     * @param bower The bower.
     *
     * @return The count.
     */
    int countBower(enum Suit trump, enum Bower bower = EUCHRE_ANY_BOWER);
    
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

#endif

