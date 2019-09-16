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
 
// $Id: RoundHistory.cc,v 1.1 2005/08/08 12:00:37 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "model/RoundHistory.hh"

RoundHistory *RoundHistory::singleton = new RoundHistory();

void RoundHistory::reset() {
    played.clear(); 
}

void RoundHistory::add(const Play &play) {
    played.push_back(play.getCard());
}

