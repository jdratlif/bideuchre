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
 
// $Id: EuchreFrame.hh,v 1.1.1.1 2005/08/06 09:52:51 technoplaza Exp $

#ifndef _EUCHREFRAME_HH_
#define _EUCHREFRAME_HH_

#include "ui/UIConstants.hh"
#include "ui/GamePanel.hh"

class HelpDialog;

/**
 * The main frame for the application.
 */
class EuchreFrame : public wxFrame {
private:
    DECLARE_CLASS(EuchreFrame)
    DECLARE_EVENT_TABLE()
    
    GamePanel *panel;
    HelpDialog *helpDialog;
    
    /**
     * Called when new game is selected from the file menu.
     *
     * @param event The associated command event.
     */
    void onFileNewGame(wxCommandEvent &event);
    
    /**
     * Called when exit is selected from the file menu.
     *
     * @param event The associated command event.
     */
    void onFileExit(wxCommandEvent &event);
    
    /**
     * Called then cheat mode is selected from the options menu.
     *
     * @param event The associated command event.
     */
    void onOptionsCheatMode(wxCommandEvent &event);
    
    /**
     * Called when a doc page is selected from the help menu.
     *
     * @param event The associated command event.
     */
    void onHelpDoc(wxCommandEvent &event);
    
    /**
     * Called when about is selected from the help menu.
     *
     * @param event The associated command event.
     */
    void onHelpAbout(wxCommandEvent &event);
    
    /**
     * Creates the controls for this EuchreFrame.
     */
    void CreateControls();
    
public:
    /**
     * Creates a new EuchreFrame object.
     */
    EuchreFrame();
};

inline void EuchreFrame::onFileNewGame(wxCommandEvent &) { panel->startGame(); }
inline void EuchreFrame::onFileExit(wxCommandEvent &) { Close(); }

#endif

