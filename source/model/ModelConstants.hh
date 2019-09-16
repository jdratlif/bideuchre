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

// $Id: ModelConstants.hh,v 1.1.1.1 2005/08/06 09:52:51 technoplaza Exp $

#ifndef _MODELCONSTANTS_HH_
#define _MODELCONSTANTS_HH_

/// The card suit and trump values (do not change values -- used internally)
enum Suit {
    LOW, SPADES, DIAMONDS, CLUBS, HEARTS, HIGH
};

/// The six possible Euchre card faces (do not change values -- used internally)
enum Face {
    NINE = 9, TEN, JACK, QUEEN, KING, ACE
};

/// The bower constants
enum Bower {
    EUCHRE_ANY_BOWER, EUCHRE_LEFT_BOWER, EUCHRE_RIGHT_BOWER
};

#endif
