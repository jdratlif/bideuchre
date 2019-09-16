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
 
// $Id: Bridge.cc,v 1.1.1.1 2005/08/06 09:52:49 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "bridge/Bridge.hh"

void Bridge::startRound(const Round *round) {
    this->round = round;
    ui->startRound();
}

void Bridge::endRound() {
    ui->endRound();
    round = NULL;
}

void Bridge::startTrick(const Trick *trick) {
    this->trick = trick;
    ui->startRound();
}

void Bridge::endTrick() {
    ui->endTrick();
    trick = NULL;
}

