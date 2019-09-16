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
 
// $Id: Card.cc,v 1.13 2005/08/01 09:17:37 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/image.h>

#include "model/Card.hh"

wxImage Card::backside = wxNullImage;

enum Suit Card::getSuit(enum Suit trump) const {
    if (face == JACK) {
        if ((trump == SPADES) && (suit == CLUBS)) {
            return SPADES;
        } else if ((trump == CLUBS) && (suit == SPADES)) {
            return CLUBS;
        } else if ((trump == DIAMONDS) && (suit == HEARTS)) {
            return DIAMONDS;
        } else if ((trump == HEARTS) && (suit == DIAMONDS)) {
            return HEARTS;
        }
    }
    
    return suit;
}

wxString Card::getSuitName(enum Suit suit) const {
    wxString str = wxT("Hearts");
    
    if (suit == SPADES) {
        str = wxT("Spades");
    } else if (suit == DIAMONDS) {
        str = wxT("Diamonds");
    } else if (suit == CLUBS) {
        str = wxT("Clubs");
    }
    
    return str;
}

wxString Card::getFaceName() const {
    wxString str = wxT("Ace");
    
    if (face == NINE) {
        str = wxT("Nine");
    } else if (face == TEN) {
        str = wxT("Ten");
    } else if (face == JACK) {
        str = wxT("Jack");
    } else if (face == QUEEN) {
        str = wxT("Queen");
    } else if (face == KING) {
        str = wxT("King");
    }
    
    return str;
}

bool Card::isBower(enum Suit trump, enum Bower bower) const {
    if (getSuit(trump) != suit) {
        return ((bower == EUCHRE_LEFT_BOWER) || (bower == EUCHRE_ANY_BOWER));
    }
    
    if ((suit == trump) && (face == JACK)) {
        return ((bower == EUCHRE_RIGHT_BOWER) || (bower == EUCHRE_ANY_BOWER));
    }
    
    return false;
}

wxImage Card::toImage() const {
    wxString str = wxT("images/");
    str << face << wxT('-') << suit << wxT(".bmp");
    
    return wxImage(str, wxBITMAP_TYPE_BMP);
}

const wxImage &Card::getBackImage() {
    if (backside == wxNullImage) {
        backside = wxImage("images/card.bmp", wxBITMAP_TYPE_BMP);
    }
    
    return backside;
}

wxString Card::toString() const {
    wxString str = getFaceName() + wxT(" of ") + getSuitName();
    
    return str;
}

