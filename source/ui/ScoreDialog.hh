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

// $Id: ScoreDialog.hh,v 1.8 2005/07/30 07:09:53 technoplaza Exp $

#ifndef _SCOREDIALOG_HH_
#define _SCOREDIALOG_HH_

#include <vector>

class wxHtmlWindow;

/**
 * A dialog for displaying the Scorepad.
 */
class ScoreDialog : public wxDialog {
private:    
    DECLARE_DYNAMIC_CLASS(ScoreDialog)
    DECLARE_EVENT_TABLE()
    
    wxHtmlWindow *html;
    
    /**
     * Called when the close button is pressed.
     *
     * @param event The associated event.
     */
    void onCloseButton(wxCommandEvent &event);
    
    /**
     * Creates the controls for this ScoreDialog.
     */
    void CreateControls();

public:
    /**
     * Creates a new ScoreDialog.
     */
    ScoreDialog();
    
    /**
     * Creates a new ScoreDialog.
     *
     * @param parent The parent window.
     */
    ScoreDialog(wxWindow *parent);
    
    /**
     * Regenerates the contents of this ScoreDialog.
     *
     * @param scores The score vector.
     */
    void regenerate(const std::vector<Score> &scores);
};

inline ScoreDialog::ScoreDialog() {}

#endif

