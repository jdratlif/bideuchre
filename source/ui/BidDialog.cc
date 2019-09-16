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
 
// $Id: BidDialog.cc,v 1.8 2005/07/29 03:35:43 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "AppConstants.hh"
#include "model/Bid.hh"
#include "ui/UIConstants.hh"
#include "ui/BidDialog.hh"

IMPLEMENT_DYNAMIC_CLASS(BidDialog, wxDialog)

BEGIN_EVENT_TABLE(BidDialog, wxDialog)
    EVT_CLOSE(BidDialog::onClose)

    EVT_RADIOBUTTON(ID_BD_1_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_2_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_3_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_4_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_5_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_6_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_7_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_8_RADIO, BidDialog::onChangeTricks)
    EVT_RADIOBUTTON(ID_BD_BEST_RADIO, BidDialog::onChangeTricks)
    
    EVT_RADIOBUTTON(ID_BD_SPADES_RADIO, BidDialog::onChangeTrump)
    EVT_RADIOBUTTON(ID_BD_DIAMONDS_RADIO, BidDialog::onChangeTrump)
    EVT_RADIOBUTTON(ID_BD_CLUBS_RADIO, BidDialog::onChangeTrump)
    EVT_RADIOBUTTON(ID_BD_HEARTS_RADIO, BidDialog::onChangeTrump)
    EVT_RADIOBUTTON(ID_BD_LOW_RADIO, BidDialog::onChangeTrump)
    EVT_RADIOBUTTON(ID_BD_HIGH_RADIO, BidDialog::onChangeTrump)
    
    EVT_BUTTON(ID_BD_BID_BUTTON, BidDialog::onBidButton)
    EVT_BUTTON(ID_BD_PASS_BUTTON, BidDialog::onPassButton)
END_EVENT_TABLE()

BidDialog::BidDialog(wxWindow* parent) : bid(NULL), trump(SPADES), tricks(1),
                                         bidding(false), alone(false) {
    Create(parent, ID_BD_DIALOG, BID_DIALOG_TITLE, wxDefaultPosition, 
           wxDefaultSize, BID_DIALOG_STYLE);
    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
}

void BidDialog::CreateControls() {
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(topSizer, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    wxStaticBox *trickBox = new wxStaticBox(this, wxID_ANY, wxT("Tricks"));
    wxStaticBoxSizer *trickSizer = new wxStaticBoxSizer(trickBox, wxHORIZONTAL);
    topSizer->Add(trickSizer, 0, wxALIGN_TOP | wxLEFT | wxRIGHT, 5);

    wxFlexGridSizer *trickFlexSizer = new wxFlexGridSizer(3);
    trickSizer->Add(trickFlexSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);

    trickRadio[0] = new wxRadioButton(this, ID_BD_1_RADIO, wxT("1"),
                                      wxDefaultPosition, wxDefaultSize,
                                      wxRB_GROUP);
    trickRadio[0]->SetValue(true);
    trickFlexSizer->Add(trickRadio[0], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    trickRadio[1] = new wxRadioButton(this, ID_BD_2_RADIO, wxT("2"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[1], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    trickRadio[2] = new wxRadioButton(this, ID_BD_3_RADIO, wxT("3"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[2], 0, wxALIGN_LEFT | 
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    trickRadio[3] = new wxRadioButton(this, ID_BD_4_RADIO, wxT("4"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[3], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    trickRadio[4] = new wxRadioButton(this, ID_BD_5_RADIO, wxT("5"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[4], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    trickRadio[5] = new wxRadioButton(this, ID_BD_6_RADIO, wxT("6"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[5], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    trickRadio[6] = new wxRadioButton(this, ID_BD_7_RADIO, wxT("7"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[6], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    trickRadio[7] = new wxRadioButton(this, ID_BD_8_RADIO, wxT("8"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[7], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);
                                        
    trickRadio[8] = new wxRadioButton(this, ID_BD_BEST_RADIO, wxT("Best"),
                                      wxDefaultPosition, wxDefaultSize, 0);
    trickFlexSizer->Add(trickRadio[8], 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxStaticBox *trumpBox = new wxStaticBox(this, wxID_ANY, wxT("Trump"));
    wxStaticBoxSizer *trumpSizer = new wxStaticBoxSizer(trumpBox, wxHORIZONTAL);
    topSizer->Add(trumpSizer, 0, wxALIGN_TOP | wxLEFT | wxRIGHT, 5);

    wxFlexGridSizer *trumpFlexSizer = new wxFlexGridSizer(2);
    trumpSizer->Add(trumpFlexSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);

    wxRadioButton *trumpRadioSpades = new wxRadioButton(this,
                                                        ID_BD_SPADES_RADIO,
                                                        wxT("Spades"),
                                                        wxDefaultPosition,
                                                        wxDefaultSize,
                                                        wxRB_GROUP);
    trumpRadioSpades->SetValue(true);
    trumpFlexSizer->Add(trumpRadioSpades, 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxRadioButton *trumpRadioDiamonds = new wxRadioButton(this,
                                                          ID_BD_DIAMONDS_RADIO,
                                                          wxT("Diamonds"),
                                                          wxDefaultPosition,
                                                          wxDefaultSize, 0);
    trumpFlexSizer->Add(trumpRadioDiamonds, 0, wxALIGN_LEFT | 
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxRadioButton *trumpRadioClubs = new wxRadioButton(this, ID_BD_CLUBS_RADIO,
                                                       wxT("Clubs"),
                                                       wxDefaultPosition,
                                                       wxDefaultSize, 0);
    trumpFlexSizer->Add(trumpRadioClubs, 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxRadioButton *trumpRadioHearts = new wxRadioButton(this,
                                                        ID_BD_HEARTS_RADIO,
                                                        wxT("Hearts"),
                                                        wxDefaultPosition,
                                                        wxDefaultSize, 0);
    trumpFlexSizer->Add(trumpRadioHearts, 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);
                                        
    wxRadioButton *trumpRadioLow = new wxRadioButton(this, ID_BD_LOW_RADIO,
                                                     wxT("Low"),
                                                     wxDefaultPosition,
                                                     wxDefaultSize, 0);
    trumpFlexSizer->Add(trumpRadioLow, 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxRadioButton *trumpRadioHigh = new wxRadioButton(this, ID_BD_HIGH_RADIO,
                                                      wxT("High"),
                                                      wxDefaultPosition,
                                                      wxDefaultSize, 0);
    trumpFlexSizer->Add(trumpRadioHigh, 0, wxALIGN_LEFT |
                                        wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(bottomSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    wxButton *bidButton = new wxButton(this, ID_BD_BID_BUTTON, wxT("&Bid"),
                                       wxDefaultPosition, wxDefaultSize, 0);
    bottomSizer->Add(bidButton, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

    wxButton *passButton = new wxButton(this, ID_BD_PASS_BUTTON, wxT("&Pass"),
                                        wxDefaultPosition, wxDefaultSize, 0);
    bottomSizer->Add(passButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
}

void BidDialog::close() {
    if (bid != NULL) {
        bid->setTricks(tricks);
        bid->setTrump(trump);
        bid->setAlone(alone);
        
        bid = NULL;
    }
    
    bidding = false;
    
    Show(false);
    cond->Signal();
}

void BidDialog::onChangeTricks(wxCommandEvent &event) {
    int id = event.GetId();
    
    alone = false;
    
    if (id == ID_BD_1_RADIO) {
        tricks = 1;
    } else if (id == ID_BD_2_RADIO) {
        tricks = 2;
    } else if (id == ID_BD_3_RADIO) {
        tricks = 3;
    } else if (id == ID_BD_4_RADIO) {
        tricks = 4;
    } else if (id == ID_BD_5_RADIO) {
        tricks = 5;
    } else if (id == ID_BD_6_RADIO) {
        tricks = 6;
    } else if (id == ID_BD_7_RADIO) {
        tricks = 7;
    } else if (id == ID_BD_8_RADIO) {
        tricks = 8;
    } else {
        tricks = 8;
        alone = true;
    }
}

void BidDialog::onChangeTrump(wxCommandEvent &event) {
    int id = event.GetId();
    
    if (id == ID_BD_SPADES_RADIO) {
        trump = SPADES;
    } else if (id == ID_BD_DIAMONDS_RADIO) {
        trump = DIAMONDS;
    } else if (id == ID_BD_CLUBS_RADIO) {
        trump = CLUBS;
    } else if (id == ID_BD_HEARTS_RADIO) {
        trump = HEARTS;
    } else if (id == ID_BD_LOW_RADIO) {
        trump = LOW;
    } else if (id == ID_BD_HIGH_RADIO) {
        trump = HIGH;
    }
}

void BidDialog::pass() {
    tricks = 0;
    
    close();
}

void BidDialog::setBid(Bid *bid) {
    this->bid = bid;
    bidding = true;
}

void BidDialog::setMinimum(int tricks) {
    this->tricks = tricks;
    alone = false;
    
    trickRadio[--tricks]->SetValue(true);
    
    for (int i = (tricks - 1); i >= 0; i--) {
        trickRadio[i]->Enable(false);
    }
    
    for (int i = tricks; i < 9; i++) {
        trickRadio[i]->Enable();
    }
}

