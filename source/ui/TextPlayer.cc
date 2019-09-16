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
 
// $Id: TextPlayer.cc,v 1.22 2005/07/31 23:31:07 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <iostream>
#include <cstdio>

#include "model/Bid.hh"
#include "model/BidHistory.hh"
#include "model/Card.hh"
#include "model/Play.hh"
#include "engine/Trick.hh"
#include "ui/TextPlayer.hh"

using std::cout;
using std::cin;

const wxString TextPlayer::TRICK_CHOICES[] =
    {
        wxT("(1) One"), wxT("(2) Two"), wxT("(3) Three"), wxT("(4) Four"),
        wxT("(5) Five"), wxT("(6) Six"), wxT("(7) Seven"), wxT("(8) Eight")
    };
    
const wxString TextPlayer::TRUMP_CHOICES[] =
    {
        wxT("(L)ow"), wxT("(S)pades"), wxT("(D)iamonds"),
        wxT("(C)lubs"), wxT("(H)earts"), wxT("H(i)gh")
    };
    
void TextPlayer::playCard(Trick &trick) {
    int i = (hand.size() == 1) ? 0 : -1;
    
    while ((i < 0) || (i >= (signed int)hand.size())) {
        char ch;
        const Bid &bid = trick.getBid();
        
        cout << "---------------------------------------------\n";
        cout << "| " << name.c_str() << "'s Turn\n";
        cout << "| Bid [ " << bid.getTeamString().c_str() << ": " << 
            bid.getBidString().c_str() << " ]\n";
        cout << "---------------------------------------------\n\n";
        
        for (unsigned int j = 0; j < hand.size(); j++) {
            cout << (j + 1) << ") " <<
                hand.get(j).toString().c_str() << '\n';
        }
        
        cout << "\nWhich card? ";
        cout.flush();
        
        cin.get(ch);
        cin.seekg(0, std::ios_base::end);
        cout << '\n';
        
        i = (ch - '0' - 1);
        
        if (!isValidPlay(hand.get(i), trick)) {
            i = -1;
            enum Suit suit = trick.getLead().getSuit(trick.getBid().getTrump());
            
            cout << "Must follow suit: " <<
                trick.getLead().getSuitName(suit) << "\n\n";
        }
    }
    
    trick.play(Play(this, hand.get(i)));
    hand.remove(i);
}

void TextPlayer::bid(BidHistory &bids) {
    Bid bid(this);
    const Bid &best = bids.getWinning();
    bool done = false;
    
    while (!done) {
        char ch;
        enum Suit trump;
        int tricks;
        bool alone = false;
        
        cout << "---------------------------------------------\n";        
        cout << "| Bidder: " << name.c_str() << '\n';
        cout << "---------------------------------------------\n";
        
        for (unsigned int i = 0; i < hand.size(); i++) {
            cout << "| " << hand.get(i).toString().c_str() << '\n';
        }
        
        cout << "---------------------------------------------\n";
        cout << "| (P)ass\n|\n";
        
        for (int i = best.getTricks(); i < 8; i++) {
            cout << "| " << TRICK_CHOICES[i].c_str() << '\n';
        }
        
        cout << "|\n| (B)est\n";
        cout << "---------------------------------------------\n\n";
        cout << "How Many? ";
        cout.flush();
        
        cin.get(ch);
        cin.seekg(0, std::ios_base::end);
        cout << '\n';
        
        if ((ch == 'p') || (ch == 'P')) {
            done = true;
            continue;
        }
        
        if ((ch == 'b') || (ch == 'B')) {
            tricks = 8;
            alone = true;
        } else {
            tricks = (int)(ch - '0');
        }
        
        if ((tricks <= best.getTricks()) || (tricks > 8)) {
            continue;
        }
        
        cout << "---------------------------------------------\n";
        cout << "| (P)ass\n|\n";
        
        for (int i = 0; i < 6; i++) {
            cout << "| " << TRUMP_CHOICES[i].c_str() << '\n';
        }
        
        cout << "---------------------------------------------\n\n";
        cout << "Trump? ";
        cout.flush();
        
        cin.get(ch);
        cin.seekg(0, std::ios_base::end);
        cout << '\n';
        
        if ((ch == 'p') || (ch == 'P')) {
            done = true;
            continue;
        } else if ((ch == 'l') || (ch == 'L')) {
            trump = LOW;
        } else if ((ch == 's') || (ch == 'S')) {
            trump = SPADES;
        } else if ((ch == 'd') || (ch == 'D')) {
            trump = DIAMONDS;
        } else if ((ch == 'c') || (ch == 'C')) {
            trump = CLUBS;
        } else if ((ch == 'h') || (ch == 'H')) {
            trump = HEARTS;
        } else if ((ch == 'i') || (ch == 'I')) {
            trump = HIGH;
        } else {
            continue;
        }
        
        Bid temp(this, tricks, trump, alone);
        cout << "Bid: " << temp.toString().c_str() << '\n';
        cout << "Correct? [Y/N] ";
        cout.flush();
        
        cin.get(ch);
        cin.seekg(0, std::ios_base::end);
        
        if ((ch == 'Y') || (ch == 'y')) {
            bid = temp;
            done = true;
        }
        
        cout << '\n';
    }
    
    bids.add(bid);
}

void TextPlayer::giveLonerCard(const Bid &bid) {
    bool done = false;
    int card = 0;
    char ch;
    
    while (!done) {
        cout << "---------------------------------------------\n";
        cout << "| " << name.c_str() << "'s Hand\n";
        cout << "| Bid [ " << bid.toString().c_str() << " ]\n";
        cout << "---------------------------------------------\n\n";
        
        for (unsigned int i = 0; i < hand.size(); i++) {
            cout << (i + 1) << ") " << hand.get(i).toString().c_str() << '\n';
        }
    
        cout << "\nGive which card? ";
        cout.flush();
        
        cin.get(ch);
        cin.seekg(0, std::ios_base::end);
        
        card = (int)((ch - '0') - 1);
        
        if ((card < 0) || (card >= (signed int)hand.size())) {
            continue;
        }
        
        cout << "\nGive " << hand.get(card).toString().c_str() << "? [Y/N] ";
        cout.flush();
        
        cin.get(ch);
        cin.seekg(0, std::ios_base::end);
        
        if ((ch == 'Y') || (ch == 'y')) {
            done = true;
        }
        
        cout << '\n';
    }
    
    Player *bidder = const_cast<Player *>(bid.getPlayer());
    giveCard(bidder, card);
    hand.clear();
}

void TextPlayer::discard(const Bid &bid) {
    int card;
    char s[21];
    char ch;
    
    while (hand.size() > 8) {
        cout << "---------------------------------------------\n";
        cout << "| Bid [ " << bid.toString().c_str() << " ]\n";
        cout << "---------------------------------------------\n\n";

        for (unsigned int i = 0; i < hand.size(); i++) {
            cout << (i + 1) << ") " << hand.get(i).toString().c_str() << '\n';
        }
    
        cout << "\nDiscard which card? ";
        cout.flush();
        
        cin.getline(s, 20);
        cin.seekg(0, std::ios_base::end);
        
        sscanf(s, "%d", &card);
        --card;
        
        if ((card < 0) || (card >= (signed int)hand.size())) {
            continue;
        }
        
        cout << "\nDiscard " << hand.get(card).toString().c_str() << "? [Y/N] ";
        cout.flush();
        
        cin.get(ch);
        cin.seekg(0, std::ios_base::end);
        
        if ((ch == 'Y') || (ch == 'y')) {
            hand.remove(card);
        }
        
        cout << '\n';
    }
}

