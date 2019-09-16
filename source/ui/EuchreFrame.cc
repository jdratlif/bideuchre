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

// $Id: EuchreFrame.cc,v 1.1.1.1 2005/08/06 09:52:51 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "AppConstants.hh"
#include "ui/EuchreFrame.hh"
#include "ui/GamePanel.hh"
#include "ui/HelpDialog.hh"

IMPLEMENT_CLASS(EuchreFrame, wxFrame)

BEGIN_EVENT_TABLE(EuchreFrame, wxFrame)
    EVT_MENU(IDM_FILE_NEWGAME, EuchreFrame::onFileNewGame)
    EVT_MENU(wxID_EXIT, EuchreFrame::onFileExit)
    EVT_MENU(IDM_OPTIONS_CHEATMODE, EuchreFrame::onOptionsCheatMode)
    EVT_MENU(IDM_HELP_PLAY, EuchreFrame::onHelpDoc)
    EVT_MENU(IDM_HELP_RULES, EuchreFrame::onHelpDoc)
    EVT_MENU(wxID_ABOUT, EuchreFrame::onHelpAbout)
END_EVENT_TABLE()

EuchreFrame::EuchreFrame() {
    Create(NULL, ID_FRAME, FRAME_TITLE, wxDefaultPosition,
           FRAME_SIZE, FRAME_STYLE);
    CreateControls();
    Centre();
}

void EuchreFrame::CreateControls() {
    wxMenuBar *menuBar = new wxMenuBar;
    
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(IDM_FILE_NEWGAME, wxT("&New Game\tCtrl-N"));
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, wxT("E&xit"));
    menuBar->Append(fileMenu, wxT("&File"));
    
    wxMenu *optionsMenu = new wxMenu;
    optionsMenu->AppendCheckItem(IDM_OPTIONS_CHEATMODE, wxT("Cheat Mode"));
    menuBar->Append(optionsMenu, wxT("&Options"));
    
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(IDM_HELP_PLAY, wxT("How to Play"));
    helpMenu->Append(IDM_HELP_RULES, wxT("Bid Euchre Rules"));
    helpMenu->AppendSeparator();
    helpMenu->Append(wxID_ABOUT, wxT("&About"));
    menuBar->Append(helpMenu, wxT("&Help"));
    
    SetMenuBar(menuBar);

    panel = new GamePanel(this);
    helpDialog = new HelpDialog(this);
}

void EuchreFrame::onOptionsCheatMode(wxCommandEvent &) {
    panel->toggleCheatMode();
    panel->Refresh();
    panel->Update();
}

void EuchreFrame::onHelpDoc(wxCommandEvent &event) {
    if (event.GetId() == IDM_HELP_PLAY) {
        helpDialog->loadPage("docs/bideuchre.html");
    } else {
        helpDialog->loadPage("docs/rules.html");
    }
    
    helpDialog->Show();
}

void EuchreFrame::onHelpAbout(wxCommandEvent &) {
    wxString message = *APP_NAME + wxT(' ') + *APP_VERSION + wxT('\n') +
                       *APP_COPYRIGHT + wxT('\n') + *APP_URL;
    wxString title = wxT("About ") + *APP_NAME + wxT("...");
    
    wxMessageBox(message, title, wxOK | wxICON_INFORMATION, this);
}

