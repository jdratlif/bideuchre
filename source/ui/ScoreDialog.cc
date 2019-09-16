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

// $Id: ScoreDialog.cc,v 1.11 2005/07/30 07:09:53 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/html/htmlwin.h>

#include "model/Bid.hh"
#include "model/Score.hh"
#include "engine/Game.hh"
#include "engine/Player.hh"
#include "ui/UIConstants.hh"
#include "ui/ScoreDialog.hh"

IMPLEMENT_DYNAMIC_CLASS(ScoreDialog, wxDialog)

BEGIN_EVENT_TABLE(ScoreDialog, wxDialog)
    EVT_BUTTON(ID_SD_BUTTON, ScoreDialog::onCloseButton)
END_EVENT_TABLE()

ScoreDialog::ScoreDialog(wxWindow *parent) {
    Create(parent, ID_SD_DIALOG, SCORE_DIALOG_TITLE, wxDefaultPosition, 
           SCORE_DIALOG_SIZE, SCORE_DIALOG_STYLE);
    CreateControls();
}

void ScoreDialog::CreateControls() {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    html = new wxHtmlWindow(this, ID_SD_HTMLWINDOW, wxDefaultPosition, 
                            wxDefaultSize, wxHW_SCROLLBAR_AUTO | 
                            wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL);
    sizer->Add(html, 1, wxGROW | wxALL, 0);

    wxButton *button = new wxButton(this, ID_SD_BUTTON, wxT("&Close"), 
                                    wxDefaultPosition, wxDefaultSize, 0);
    sizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
}

void ScoreDialog::regenerate(const std::vector<Score> &scores) {
    wxString str;
    
    str += "<table width=100% border=1><tr>";
    str += "<td width=25% align=center><b>Dealer</b></td>";
    str += "<td width=15% align=center><b>Us</b></td>";
    str += "<td width=15% align=center><b>Them</b></td>";
    str += "<td width=45% align=center><b>Bid</b></td></tr>";
    
    for (unsigned int i = 0; i < scores.size(); i++) {
        const Score &score = scores[i];
        Bid bid = score.getBid();
        
        str += "<tr><td width=25% align=center>";
        str += score.getDealer()->getName();
        str += "</td>";
        str += "<td width=15% align=center>";
        
        int temp = score.getScore(0);
        
        if (temp < 0) {
            str += "<font color=#FF0000>";
            str << (0 - temp);
            str += "</font>";
        } else {
            str << temp;
        }
        
        str += "</td>";
        str += "<td width=15% align=center>";
        
        temp = score.getScore(1);
        
        if (temp < 0) {
            str += "<font color=#FF0000>";
            str << (0 - temp);
            str += "</font>";
        } else {
            str << temp;
        }
        
        str += "</td>";
        str += "<td width=45% align=center>";
        str += bid.getTeamString();
        str += ": ";
        str += bid.getBidString();
        str += "</td></tr>";
    }
    
    str += "</table>";
    
    html->SetPage(str);
}

void ScoreDialog::onCloseButton(wxCommandEvent &) {
    Show(false);
    Game::getInstance().setPause(false);
}

