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
 
// $Id: AIPlayer.cc,v 1.1.1.1 2005/08/06 09:52:49 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <utility>

#include "model/Bid.hh"
#include "model/BidHistory.hh"
#include "engine/AIPlayer.hh"
#include "engine/Trick.hh"

int AIPlayer::score(const Card &card, enum Suit trump) {
    int score = 0;
    enum Suit suit = card.getSuit(trump);
    enum Face face = card.getFace();
    
    if (face == ACE) {
        score += ((trump != LOW) ? 600 : 100);
    } else if (face == KING) {
        score += ((trump != LOW) ? 500 : 200);
    } else if (face == QUEEN) {
        score += ((trump != LOW) ? 400 : 300);
    } else if (face == TEN) {
        score += ((trump != LOW) ? 200 : 500);
    } else if (face == NINE) {
        score += ((trump != LOW) ? 100 : 600);
    } else {
        if (card.isBower(trump, EUCHRE_RIGHT_BOWER)) {
            score += 800;
        } else if (card.isBower(trump, EUCHRE_LEFT_BOWER)) {
            score += 700;
        } else {
            score += ((trump != LOW) ? 300 : 400);
        }
    }
    
    if (suit == trump) {
        score += 1000;
    }
    
    return score;
}

int AIPlayer::getBower(enum Suit trump, enum Bower bower) {
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (hand.get(i).isBower(trump, bower)) {
            return i;
        }
    }
    
    return -1;
}

int AIPlayer::getHigh(enum Suit trump) {
    for (unsigned int i = 0; i < hand.size(); i++) {
        const Card &card = hand.get(i);
        
        if (card.getSuit(trump) != trump) {
            if (card.getFace() == ((trump == LOW) ? NINE : ACE)) {
                return i;
            }
        }
    }
    
    return -1;
}

bool AIPlayer::isTrickTaker(Trick &trick) {
    const Card &card = trick.getWinner().getPlay().getCard();
    enum Suit trump = trick.getBid().getTrump();
    
    if (card.isBower(trump, EUCHRE_RIGHT_BOWER)) {
        return true;
    }
    
    if (card.getSuit(trump) == trump) {
        if (trick.getLead().getSuit(trump) != trump) {
            return true;
        }
    } else {
        if (card.getFace() == ((trump == LOW) ? NINE : ACE)) {
            return true;
        }
    }
    
    return false;
}

bool AIPlayer::shouldTake(Trick &trick) {
    const Winner &winner = trick.getWinner();
    
    if (getTeam() != winner.getPlay().getPlayer()->getTeam()) {
        return true;
    }
    
    if (!isTrickTaker(trick)) {
        return true;
    }
    
    return false;
}

int AIPlayer::getTake(Trick &trick) {
    int score = trick.getWinner().getScore();
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        const Card &card = hand.get(i);
        
        if ((trick.score(card) > score) && isValidPlay(card, trick)) {
            return i;
        }
    }
    
    return -1;
}

int AIPlayer::getLoser(Trick &trick) {
    int card = 0, lowest = 9999;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        int score = this->score(hand.get(i), trick.getBid().getTrump());
        
        if ((score < lowest) && isValidPlay(hand.get(i), trick)) {
            lowest = score;
            card = i;
        }
    }
    
    return card;
}

void AIPlayer::playCard(Trick &trick) {
    enum Suit trump = trick.getBid().getTrump();
    int card = getLoser(trick), temp;
    
    if (trick.getPlayHistory().size() == 0) {
        if ((temp = getBower(trump, EUCHRE_RIGHT_BOWER)) != -1) {
            card = temp;
        } else if ((temp = getHigh(trump)) != -1) {
            card = temp;
        }
    } else {
        if (shouldTake(trick)) {
            if ((temp = getTake(trick)) != -1) {
                card = temp;
            }
        }
    }
    
    Card copy = hand.get(card);
    hand.remove(card);
    
    trick.play(Play(this, copy));
}

int AIPlayer::countTrump(enum Suit trump) {
    int count = 0;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (trump == hand.get(i).getSuit(trump)) {
            ++count;
        }
    }
    
    return count;
}

int AIPlayer::countHigh(enum Suit trump) {
    int count = 0;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        const Card &card = hand.get(i);
        
        if (card.getSuit(trump) != trump) {
            if (card.getFace() == ((trump == LOW) ? NINE : ACE)) {
                ++count;
            }
        }
    }
    
    return count;
}

void AIPlayer::bid(BidHistory &bids) {
    std::pair<int, int> trump[6];
    std::pair<int, int> count(0, 0);
    enum Suit best = LOW;
    
    for (int i = LOW; i <= HIGH; i++) {
        enum Suit suit = static_cast<enum Suit>(i);
        
        trump[i].first = countTrump(suit);
        trump[i].second = countHigh(suit);
        
        if (getBower(suit) == -1) {
            trump[i].first -= 2;
        } else {
            if (getBower(suit, EUCHRE_RIGHT_BOWER) == -1) {
                --trump[i].first;
            }
        }
        
        int a = count.first + count.second;
        int b = trump[i].first + trump[i].second;
        
        if (b >= a) {
            if (trump[i].first > count.first) {
                best = suit;
                count = trump[i];
            }
        }
    }

    const Bid &winning = bids.getWinning();
    Bid bid(this);
    int a = count.first + count.second;    
    
    if (a > winning.getTricks()) {
        bid.setTrump(best);
        bid.setTricks(a);
    }
    
    bids.add(bid);
}

void AIPlayer::giveLonerCard(const Bid &bid) {
    int card = 0, highest = 0;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        int score = this->score(hand.get(i), bid.getTrump());
        
        if (score > highest) {
            highest = score;
            card = i;
        }
    }
    
    Player *bidder = const_cast<Player *>(bid.getPlayer());
    giveCard(bidder, card);
    hand.clear();
}

