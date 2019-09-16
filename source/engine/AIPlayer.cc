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
 
// $Id: AIPlayer.cc,v 1.5 2005/08/09 04:03:52 technoplaza Exp $

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

void AIPlayer::findBower(enum Bower bower) {
    enum Suit trump = trick->getBid().getTrump();
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (hand[i].isBower(trump, bower)) {
            plays.push_back(i);
        }
    }
}

void AIPlayer::findHigh() {
    enum Suit trump = trick->getBid().getTrump();
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (hand[i].getSuit(trump) != trump) {
            if (hand[i].getFace() == ((trump == LOW) ? NINE : ACE)) {
                plays.push_back(i);
            }
        }
    }
}

void AIPlayer::findLead() {
    findBower(EUCHRE_RIGHT_BOWER);
    findHigh();
}

bool AIPlayer::isTrickTaker() {
    const Card &card = trick->getWinner().getPlay().getCard();
    enum Suit trump = trick->getBid().getTrump();
    
    if (card.isBower(trump, EUCHRE_RIGHT_BOWER)) {
        return true;
    }
    
    if (card.getSuit(trump) == trump) {
        if (trick->getLead().getSuit(trump) != trump) {
            return true;
        }
    } else {
        if (card.getFace() == ((trump == LOW) ? NINE : ACE)) {
            return true;
        }
    }
    
    return false;
}

bool AIPlayer::shouldTake() {
    const Winner &winner = trick->getWinner();
    
    if (getTeam() != winner.getPlay().getPlayer()->getTeam()) {
        return true;
    }
    
    if (!isTrickTaker()) {
        return true;
    }
    
    return false;
}

bool AIPlayer::findTake() {
    bool found = false;
    int score = trick->getWinner().getScore();
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        if ((trick->score(hand[i]) > score) && isValidPlay(hand[i], *trick)) {
            plays.push_back(i);
            found = true;
        }
    }
    
    return found;
}

void AIPlayer::findLoser() {
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (isValidPlay(hand[i], *trick)) {
            plays.push_back(i);
        }
    }
}

int AIPlayer::selectLowest() {
    int index = 0, lowest = 9999;
    
    for (unsigned int i = 0; i < plays.size(); i++) {
        int score = this->score(hand[plays[i]], trick->getBid().getTrump());
        
        if (score < lowest) {
            lowest = score;
            index = plays[i];
        }
    }
    
    return index;
}

int AIPlayer::selectHighest() {
    int index = 0, highest = 0;
    
    for (unsigned int i = 0; i < plays.size(); i++) {
        int score = this->score(hand[plays[i]], trick->getBid().getTrump());
        
        if (score > highest) {
            highest = score;
            index = plays[i];
        }
    }
    
    return index;
}

int AIPlayer::selectBestLead() {
    enum Suit trump = trick->getBid().getTrump();
    
    // look for right bowers first
    for (unsigned int i = 0; i < plays.size(); i++) {
        if (hand[plays[i]].isBower(trump, EUCHRE_RIGHT_BOWER)) {
            return plays[i];
        }
    }
    
    // then high cards (aces or nines if no-trump low)
    for (unsigned int i = 0; i < plays.size(); i++) {
        if (hand[plays[i]].getFace() == ((trump == LOW) ? NINE : ACE)) {
            return plays[i];
        }
    }
    
    return -1;
}

void AIPlayer::playCard(Trick &trick) {
    int card = -1;
    
    this->trick = &trick;
    plays.clear();
    
    if (trick.isFirstPlayer()) {
        findLead();
        card = selectBestLead();
    } else {
        if (shouldTake()) {
            if (findTake()) {
                if (trick.isLastPlayer()) {
                    card = selectLowest();
                } else {
                    card = selectHighest();
                }
            }
        }
    }
    
    if (card == -1) {
        findLoser();
        card = selectLowest();
    }
    
    Card copy = hand[card];
    hand.remove(card);
    
    trick.play(Play(this, copy));
}

int AIPlayer::countBower(enum Suit trump, enum Bower bower) {
    int count = 0;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (hand[i].isBower(trump, bower)) {
            ++count;
        }
    }
    
    return count;
}

int AIPlayer::countTrump(enum Suit trump) {
    int count = 0;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (trump == hand[i].getSuit(trump)) {
            ++count;
        }
    }
    
    return count;
}

int AIPlayer::countHigh(enum Suit trump) {
    int count = 0;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (hand[i].getSuit(trump) != trump) {
            if (hand[i].getFace() == ((trump == LOW) ? NINE : ACE)) {
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
    bool alone = false;
    
    for (int i = LOW; i <= HIGH; i++) {
        enum Suit suit = static_cast<enum Suit>(i);
        
        trump[i].first = countTrump(suit);
        trump[i].second = countHigh(suit);
        
        if (countBower(suit) == 0) {
            // no bowers; time to back off
            trump[i].first -= 2;
        } else {
            if (countBower(suit, EUCHRE_RIGHT_BOWER) == 0) {
                // no right bowers; back off a little
                --trump[i].first;
            }
        }
        
        int a = count.first + count.second;
        int b = trump[i].first + trump[i].second;
        
        if (b >= a) {
            if (trump[i].first > count.first) {
                // favor trump over high cards
                best = suit;
                count = trump[i];
            }
        }
    }

    const Bid &winning = bids.getWinning();
    Bid bid(this);
    int tricks = count.first + count.second;

    if (tricks == 6) {
        // don't bid 6 w/o a right
        if (countBower(best, EUCHRE_RIGHT_BOWER) == 0) {
            tricks--;
        }
    } else if (tricks > 6) {
        int right = countBower(best, EUCHRE_RIGHT_BOWER);
        int left = countBower(best, EUCHRE_LEFT_BOWER);
        
        if ((right == 2) || ((right == 1) && (left > 0))) {
            // both rights, or right + left
            // time to go alone
            
            tricks = 8;
            alone = true;
        }
        
        if (right == 0) {
            // no rights; time to back off
            tricks -= 2;
        } else if ((right == 1) && (left == 0)) {
            // one right, no lefts; back off a little
            --tricks;
        }
    }
    
    if (tricks > winning.getTricks()) {
        bid.setTrump(best);
        bid.setTricks(tricks);
        bid.setAlone(alone);
    }
    
    bids.add(bid);
}

void AIPlayer::giveLonerCard(const Bid &bid) {
    int card = 0, highest = 0;
    
    for (unsigned int i = 0; i < hand.size(); i++) {
        int score = this->score(hand[i], bid.getTrump());
        
        if (score > highest) {
            highest = score;
            card = i;
        }
    }
    
    Player *bidder = const_cast<Player *>(bid.getPlayer());
    giveCard(bidder, card);
    hand.clear();
}

void AIPlayer::discard(const Bid &bid) {
    for (int j = 0; j < 2; j++) {
        int card = 0, lowest = 9999;
        
        for (unsigned int i = 0; i < hand.size(); i++) {
            int score = this->score(hand[i], bid.getTrump());
            
            if (score < lowest) {
                card = i;
                lowest = score;
            }
        }
        
        hand.remove(card);
    }
}

