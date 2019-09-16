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

// $Id: Card.hh,v 1.15 2005/08/01 09:17:37 technoplaza Exp $

#ifndef _CARD_HH_
#define _CARD_HH_

#include <wx/string.h>

#include "model/ModelConstants.hh"

class wxImage;

/**
 * Class used to represent a playing card.
 */
class Card {
private:
    enum Face face;
    enum Suit suit;
    
    static wxImage backside;

public:
    /**
     * Creates a new Card object.
     *
     * @param suit The Card suit.
     * @param face The Card face.
     */
    Card(enum Suit suit = LOW, enum Face face = NINE);
    
    /**
     * Gets this Card's suit
     *
     * @return The suit.
     */
    enum Suit getSuit() const;
    
    /**
     * Gets this Card's effective suit considering trump.
     *
     * @param trump The trump suit value.
     *
     * @return The effective suit (i.e. left bowers are suited w/ their trump).
     */
    enum Suit getSuit(enum Suit trump) const;
    
    /**
     * Gets the name of this Card's suit.
     *
     * @param suit The suit.
     *
     * @return The suit name.
     */
    wxString getSuitName(enum Suit suit) const;
    
    /**
     * Gets the name of this Card's suit.
     *
     * @return The suit name.
     */
    wxString getSuitName() const;
    
    /**
     * Gets this Card's face.
     *
     * @return The face.
     */
    enum Face getFace() const;
    
    /**
     * Gets the name of this Card's face.
     *
     * @return The face name.
     */
    wxString getFaceName() const;
    
    /**
     * Checks if this Card is a bower.
     *
     * @param trump The trump suit value.
     * @param bower The bower to check for (EUCHRE_ANY_BOWER, EUCHRE_LEFT_BOWER,
     *              or EUCHRE_RIGHT_BOWER)
     *
     * @return true if this Card is a bower; false otherwise.
     */
    bool isBower(enum Suit trump, enum Bower bower = EUCHRE_ANY_BOWER) const;
    
    /**
     * Returns a wxImage representation of this Card.
     *
     * @return A wxImage representation.
     */
    wxImage toImage() const;
    
    /**
     * Gets the backside of the card image.
     *
     * @return The wxImage card backside.
     */
    static const wxImage &getBackImage();
    
    /**
     * Returns a wxString representation of this Card.
     *
     * @return A wxString representation.
     */
    wxString toString() const;
};

inline Card::Card(enum Suit suit, enum Face face) : face(face), suit(suit) {}
inline enum Suit Card::getSuit() const { return suit; }
inline wxString Card::getSuitName() const { return getSuitName(suit); }
inline enum Face Card::getFace() const { return face; }

#endif

