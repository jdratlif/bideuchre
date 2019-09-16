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
 
// $Id: GUI.cc,v 1.19 2005/08/01 09:17:37 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/event.h>

#include "engine/Game.hh"
#include "ui/UIConstants.hh"
#include "ui/GamePanel.hh"
#include "ui/GUI.hh"

void GUI::endGame() {
    panel->Refresh(false);
    panel->Update();
}

void GUI::startBidding() {
    panel->setTable(TABLE_BIDS);
    panel->Refresh(false);
    panel->Update();
}

void GUI::bid() {
    panel->Refresh(false);
    panel->Update();
    
    wxMilliSleep(1000);
}

void GUI::endBidding() {
    panel->Refresh(false);
    panel->Update();
    
    wxMilliSleep(4000);
    panel->setTable(TABLE_CARDS);
}

void GUI::startRound() {
    panel->Refresh(false);
    panel->Update();
}

void GUI::endRound() {
    panel->Refresh(false);
    panel->Update();
    
    wxCommandEvent event(EVT_SCORE_DIALOG, panel->GetId());
    event.SetEventObject(panel);
    panel->AddPendingEvent(event);
    
    Game::getInstance().setPause();
}

void GUI::endTrick() {
    panel->Refresh(false);
    panel->Update();
    
    wxMilliSleep(4000);
}

void GUI::play() {
    panel->setMessage();
    panel->Refresh(false);
    panel->Update();
    
    wxMilliSleep(500);
}
