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
 
// $Id: BidDialog.hh,v 1.1.1.1 2005/08/06 09:52:51 technoplaza Exp $

#ifndef _BIDDIALOG_HH_
#define _BIDDIALOG_HH_

#include <wx/dialog.h>

class wxRadioButton;
class Bid;

/**
 * Class used to query the Bid for a GUIPlayer.
 */
class BidDialog : public wxDialog {
private:
    DECLARE_DYNAMIC_CLASS(BidDialog)
    DECLARE_EVENT_TABLE()
    
    Bid *bid;
    enum Suit trump;
    int tricks;
    bool bidding, alone;
    
    wxRadioButton *trickRadio[9];
    
    /**
     * Closes this BidDialog.
     */
    void close();
    
    /**
     * Called when the dialog is being closed.
     *
     * @param event The associated close event.
     */
    void onClose(wxCloseEvent &event);
    
    /**
     * Called when the number of tricks are changed.
     *
     * @param event The associated command event.
     */
    void onChangeTricks(wxCommandEvent &event);
    
    /**
     * Called when the trump suit is changed.
     *
     * @param event The associated command event.
     */
    void onChangeTrump(wxCommandEvent &event);
    
    /**
     * Called when the bid button is pressed.
     *
     * @param event The associated command event.
     */
    void onBidButton(wxCommandEvent &event);
    
    /**
     * Passes on this Bid.
     */
    void pass();
    
    /**
     * Called when the pass button is pressed.
     *
     * @param event The associated command event.
     */
    void onPassButton(wxCommandEvent &event);

public:
    /**
     * Creates a new BidDialog.
     */
    BidDialog();
    
    /**
     * Creates a new BidDialog.
     *
     * @param parent The parent window.
     */
    BidDialog(wxWindow *parent);
    
    /**
     * Creates the controls for this BidDialog.
     */
    void CreateControls();
    
    /**
     * Sets the Bid used by this BidDialog.
     *
     * @param bid The Bid.
     */
    void setBid(Bid *bid);
    
    /**
     * Checks if this BidDialog is working on a Bid.
     *
     * @return true if bidding; false otherwise.
     */
    bool isBidding() const;
    
    /**
     * Sets the minimum number of tricks (or 9 is 'Best') that can be bid.
     *
     * @param tricks The minimum biddable tricks.
     */
    void setMinimum(int tricks);
};

inline void BidDialog::onClose(wxCloseEvent &) { pass(); }
inline void BidDialog::onBidButton(wxCommandEvent &) { close(); }
inline void BidDialog::onPassButton(wxCommandEvent &) { pass(); }
inline BidDialog::BidDialog() {}
inline bool BidDialog::isBidding() const { return bidding; }

#endif

