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
 
// $Id: Score.cc,v 1.6 2005/07/29 04:56:34 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/string.h>

#include "model/Bid.hh"
#include "model/Score.hh"
#include "engine/Player.hh"

Score::Score(const Player *dealer, const Bid &bid, int us, int them) : 
             bid(bid), dealer(dealer) {
    score[0] = us;
    score[1] = them;
}

wxString Score::toString() const {
    wxString temp = bid.getTeamString() + wxT(": ") + bid.getBidString();
    
    wxString str;
    str.Printf("%-10s %-2d   %-2d     %s", dealer->getName().c_str(), 
                                           score[0], score[1], temp.c_str());
    
    return str;
}

