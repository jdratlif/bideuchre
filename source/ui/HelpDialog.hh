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
 
// $Id: HelpDialog.hh,v 1.1 2005/07/30 07:09:53 technoplaza Exp $

#ifndef _HELPDIALOG_HH_
#define _HELPDIALOG_HH_

#include <wx/html/htmlwin.h>

/**
 * A simple dialog with an HTML window for displaying help files.
 */
class HelpDialog : public wxDialog {
private:
    DECLARE_DYNAMIC_CLASS(HelpDialog)
    
    wxHtmlWindow *html;
    
    /**
     * Creates the controls for this dialog.
     */
    void CreateControls();

public:
    /**
     * Creates a new HelpDialog.
     */
    HelpDialog();
    
    /**
     * Creates a new HelpDialog.
     *
     * @param parent The parent window.
     */
    HelpDialog(wxWindow *parent);
    
    /**
     * Loads a new help page in the HTML window.
     *
     * @param page The page file.
     */
    void loadPage(const wxString &page);
};

inline HelpDialog::HelpDialog() {}
inline void HelpDialog::loadPage(const wxString &page) { html->LoadFile(page); }

#endif

