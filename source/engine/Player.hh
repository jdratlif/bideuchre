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
 
// $Id: Player.hh,v 1.20 2005/07/31 23:31:07 technoplaza Exp $

#ifndef _PLAYER_HH_
#define _PLAYER_HH_

#include <wx/string.h>

#include "model/Hand.hh"

class Bid;
class BidHistory;
class Card;
class Deck;
class Trick;

/**
 * Class to represent a Bid Euchre player.
 */
class Player {
private:
    static const wxString NAMES[];
    
protected:
    wxString name;
    Hand hand;
    int id;
    
    /**
     * Gives a Card to another Player.
     *
     * @param player The Player to give the Card to.
     * @param card The Card index.
     */
    void giveCard(Player *player, int card);

public:
    /**
     * Creates a new Player.
     *
     * @param id The player ID.
     */
    Player::Player(int id);
    
    /**
     * Creates a new Player.
     *
     * @param id The player ID.
     * @param name The Player's name.
     */
    Player(int id, const wxString &name);
    
    /**
     * Virtual destructor for a Player.
     */
    virtual ~Player();
    
    /**
     * Gets the ID number of this Player.
     *
     * @return The ID number.
     */
    int getID() const;
    
    /**
     * Gets the name of this Player.
     *
     * @return The name.
     */
    const wxString &getName() const;
    
    /**
     * Sets the name of this Player.
     *
     * @param name The new name.
     */
    void setName(const wxString &name);
    
    /**
     * Gets this Player's Hand.
     *
     * @return The Hand.
     */
    const Hand &getHand() const;
    
    /**
     * Gets the team this Player is on.
     *
     * @return 0 for the 'us' team, 1 for the 'them' team.
     */
    int getTeam() const;
    
    /**
     * Checks if a Card is a valid play.
     *
     * @param card The Card to check.
     * @param trick The Trick to check for.
     *
     * @return true if the Card is a valid play; false otherwise.
     */
    bool isValidPlay(const Card &card, const Trick &trick);
    
    /**
     * Deals the cards.
     *
     * @param deck The Deck.
     * @param player The Players.
     */
    void deal(Deck &deck, Player **player);
    
    /**
     * Sorts this Player's hand according to trump.
     *
     * @param trump The trump suit value.
     */
    void sortHand(enum Suit trump);
    
    /**
     * Plays a Card on the Trick.
     *
     * @param trick The Trick to play on.
     */
    virtual void playCard(Trick &trick) = 0;
    
    /**
     * Makes a Bid for the next round.
     *
     * @param bids The BidHistory.
     *
     * @return The Bid.
     */
    virtual void bid(BidHistory &bids) = 0;
    
    /**
     * Gives a Card to the bidder going alone.
     *
     * @param bid The Bid.
     */
    virtual void giveLonerCard(const Bid &bid) = 0;
    
    /**
     * Discards extra cards when going alone.
     *
     * @param bid The Bid.
     */
    virtual void discard(const Bid &bid) = 0;
};

inline Player::Player(int id) : name(NAMES[id]), id(id) {}
inline Player::Player(int id, const wxString &name) : name(name), id(id) {}
inline Player::~Player() {}
inline int Player::getID() const { return id; }
inline const wxString &Player::getName() const { return name; }
inline void Player::setName(const wxString &name) { this->name = name; }
inline const Hand &Player::getHand() const { return hand; }
inline int Player::getTeam() const { return (id % 2); }
inline void Player::sortHand(enum Suit trump) { hand.sort(trump); }

#endif

