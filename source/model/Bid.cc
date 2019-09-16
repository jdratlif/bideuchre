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
 
// $Id: Bid.cc,v 1.1.1.1 2005/08/06 09:52:50 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/string.h>

#include "model/Bid.hh"
#include "engine/Player.hh"

wxString Bid::getTeamString() const {
    wxString str;
    int team = getPlayer()->getID() % 2;
    
    if (team == 0) {
        str += wxT("Us");
    } else {
        str += wxT("Them");
    }
    
    return str;
}

wxString Bid::getBidString() const {
    wxString str;
    
    if (tricks == 0) {
        str += wxT("Pass");
    } else {
        if (alone) {
            str += wxT("Best");
        } else {
            str << tricks;
        }
    
        switch (trump) {
            case LOW: str += wxT(" Low"); break;
            case SPADES: str += wxT(" Spade"); break;
            case DIAMONDS: str += wxT(" Diamond"); break;
            case CLUBS: str += wxT(" Club"); break;
            case HEARTS: str += wxT(" Heart"); break;
            case HIGH: str += wxT(" High"); break;
        }
    
        if ((tricks > 1) && (!alone) && ((trump != LOW) && (trump != HIGH))) {
            str += wxT('s');
        }
    }
    
    return str;
}

wxString Bid::toString() const {
    wxString str = getPlayer()->getName() + wxT(": ") + getBidString();
    
    return str;
}

int Bid::compareTo(const Bid &bid) const {
    int compare = tricks - bid.tricks;
    
    if (alone && bid.alone) {
        compare++;
    }
    
    return compare;
}

