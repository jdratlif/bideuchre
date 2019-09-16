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
 
// $Id: HelpDialog.cc,v 1.1.1.1 2005/08/06 09:52:52 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "ui/UIConstants.hh"
#include "ui/HelpDialog.hh"

IMPLEMENT_DYNAMIC_CLASS(HelpDialog, wxDialog)

HelpDialog::HelpDialog(wxWindow *parent) {
    Create(parent, ID_HD_DIALOG, "", wxDefaultPosition, 
           wxDefaultSize, HELP_DIALOG_STYLE);
    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
}

void HelpDialog::CreateControls() {
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    html = new wxHtmlWindow(this, ID_HD_HTMLWINDOW, wxDefaultPosition, 
                            wxSize(640, 480), wxHW_SCROLLBAR_AUTO | 
                            wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL);
    sizer->Add(html, 1, wxGROW | wxALL, 0);
}

