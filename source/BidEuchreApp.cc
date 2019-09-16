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
 
// $Id: BidEuchreApp.cc,v 1.4 2005/08/23 15:53:38 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <iostream>

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "BidEuchreApp.hh"
#include "engine/AIPlayer.hh"
#include "engine/Game.hh"
#include "bridge/Bridge.hh"
#include "ui/EuchreFrame.hh"
#include "ui/TextPlayer.hh"
#include "ui/TextUI.hh"

IMPLEMENT_APP(BidEuchreApp)
IMPLEMENT_CLASS(BidEuchreApp, wxApp)

wxMutex *mutex;
wxCondition *cond;

const wxString *APP_NAME;
const wxString *APP_VERSION;
const wxString *APP_COPYRIGHT;
const wxString *APP_URL;

BidEuchreApp::BidEuchreApp() {
    mutex = new wxMutex();
    cond = new wxCondition(*mutex);
    
    APP_NAME = new wxString(wxT("bideuchre"));
    APP_VERSION = new wxString(wxT("0.73a"));
    APP_COPYRIGHT = new wxString(wxT("Copyright (C) 2005 John David Ratliff"));
    APP_URL = new wxString(wxT("http://bideuchre.sourceforge.net/"));
}

BidEuchreApp::~BidEuchreApp() {
    delete cond;
    delete mutex;
    
    delete APP_NAME;
    delete APP_VERSION;
    delete APP_COPYRIGHT;
    delete APP_URL;
}

bool BidEuchreApp::OnInit() {
    if (argc == 2) {
        if (strcmp(argv[1].c_str(), "--text") == 0) {
            Game &game = Game::instance();
            TextUI tui;
            Bridge bridge;
            Player *player[6];
            
            for (int i = 0; i < 6; i++) {
                if (i == 0) {
                    player[i] = new TextPlayer(i);
                } else {
                    player[i] = new AIPlayer(i);
                }
                
                game.addPlayer(player[i]);
            }
            
            char s[21];
            
            std::cout << "Enter player name [" << 
                         player[0]->getName().c_str() <<
                         "] (enter to accept default) ? ";
            std::cin.getline(s, 20);
            std::cin.seekg(0, std::ios_base::end);
            
            if (s[0] != 0) {
                player[0]->setName(s);
            }
        
            bridge.setUI(&tui);
            tui.setBridge(&bridge);
            game.start(&bridge);
            
            while (game.isPlaying()) {
                wxMilliSleep(5000);
            }
            
            for (int i = 0; i < 6; i++) {
                delete player[i];
            }
        } else {
            std::cerr << "Syntax: bideuchre [ --text ]\n";
            std::cerr << "\t--text\tStart game in Text Mode\n";
        }
        
        return false;
    }
    
    EuchreFrame *frame = new EuchreFrame;
    frame->SetClientSize(700, 500);
    frame->Centre();
    frame->Show(true);
    
    SetTopWindow(frame);
    
    return true;
}

