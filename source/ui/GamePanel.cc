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
 
// $Id: GamePanel.cc,v 1.1.1.1 2005/08/06 09:52:52 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/dcbuffer.h>
#include <wx/image.h>

#include "AppConstants.hh"
#include "model/Play.hh"
#include "engine/AIPlayer.hh"
#include "engine/Game.hh"
#include "engine/Round.hh"
#include "engine/Trick.hh"
#include "bridge/Bridge.hh"
#include "ui/GamePanel.hh"
#include "ui/GUI.hh"
#include "ui/GUIPlayer.hh"
#include "ui/ScoreDialog.hh"
#include "ui/BidDialog.hh"

const wxFont GamePanel::TITLE_FONT = 
    wxFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
const wxFont GamePanel::TEXT_FONT = 
    wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
const wxFont GamePanel::NAME_FONT = 
    wxFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
const wxFont GamePanel::TRICK_FONT = 
    wxFont(28, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
const wxPoint GamePanel::HAND_POS[] =
    {
        wxPoint(136, 379), wxPoint(30, 150), wxPoint(136, 25),
        wxPoint(386, 25), wxPoint(570, 150), wxPoint(386, 379)
    };
    
const wxPoint GamePanel::CARD_POS[] =
    {
        wxPoint(250, 275), wxPoint(150, 200), wxPoint(250, 125),
        wxPoint(375, 125), wxPoint(475, 200), wxPoint(375, 275)
    };
    
const wxPoint GamePanel::BIDDING_POS[] =
    {
        wxPoint(136, 345), wxPoint(130, 203), wxPoint(136, 125),
        wxPoint(386, 125), wxPoint(565, 203), wxPoint(386, 345)
    };

IMPLEMENT_DYNAMIC_CLASS(GamePanel, wxPanel)

BEGIN_EVENT_TABLE(GamePanel, wxPanel)
    EVT_PAINT(GamePanel::onPaint)
    EVT_ERASE_BACKGROUND(GamePanel::onEraseBackground)
    EVT_LEFT_DOWN(GamePanel::onLeftMouseDown)
    EVT_COMMAND(ID_PANEL, EVT_SCORE_DIALOG, GamePanel::onShowScoreDialog)
    EVT_COMMAND(ID_PANEL, EVT_BID_DIALOG, GamePanel::onShowBidDialog)
END_EVENT_TABLE()

DEFINE_LOCAL_EVENT_TYPE(EVT_SCORE_DIALOG)
DEFINE_LOCAL_EVENT_TYPE(EVT_BID_DIALOG)

GamePanel::GamePanel(wxWindow* parent) : clicks(NULL), 
                                         message(wxT("Bid Euchre")), 
                                         table(TABLE_BIDS),
                                         cheating(false) {
    wxPanel::Create(parent, ID_PANEL, wxDefaultPosition, 
                    wxDefaultSize, PANEL_STYLE);
    SetBackgroundColour(wxColour(0, 0xA0, 0));
    
    scoreDialog = new ScoreDialog(parent);
    bidDialog = new BidDialog(parent);
    gui = new GUI(this);
    bridge = new Bridge;
    player = new Player*[6];
    
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            player[i] = new GUIPlayer(this, i);
        } else {
            player[i] = new AIPlayer(i);
        }
        
        Game::getInstance().addPlayer(player[i]);
    }
    
    bridge->setUI(gui);
    gui->setBridge(bridge);
}

GamePanel::~GamePanel() {
    delete gui;
    delete bridge;
    
    for (int i = 0; i < 6; i++) {
        delete player[i];
    }
    
    delete [] player;
}

void GamePanel::startGame() {
    Game &game = Game::getInstance();
    
    if (game.isPlaying()) {
        int result = wxMessageBox(wxT("Quit current game?"), 
                                  wxT("Game already in progress"),
                                  wxYES_NO | wxICON_QUESTION, this);
                                  
        if (result != wxYES) {
            return;
        }
        
        game.stop();
    }
    
    wxString name = wxGetTextFromUser(wxT("What is your name?"),
                                      wxT("Enter player name"),
                                      player[0]->getName(),
                                      this);
    player[0]->setName(name);
    
    game.start(bridge);
    Refresh();
    Update();
}

void GamePanel::onPaint(wxPaintEvent &) {
    wxBufferedPaintDC dc(this);
    Game &game = Game::getInstance();
    
    dc.SetBackground(wxBrush(GetBackgroundColour()));
    dc.Clear();
    
    drawNames(dc);
    drawBid(dc);
    drawTrickCount(dc);
    drawScore(dc);
    drawMessage(dc);
    drawHands(dc);
    
    if (table == TABLE_BIDS) {
        drawBidding(dc);
    } else {
        drawCards(dc);
    }
    
    if (game.hasWinner()) {
        drawWinner(dc);
    }
}

void GamePanel::drawNames(wxBufferedPaintDC &dc) {
    dc.SetFont(NAME_FONT);
    dc.SetTextForeground(*wxWHITE);
    dc.DrawText(player[0]->getName(), 200, 475);
    dc.DrawRotatedText(player[1]->getName(), 0, 250, 90);
    dc.DrawText(player[2]->getName(), 200, 2);
    dc.DrawText(player[3]->getName(), 450, 2);
    dc.DrawRotatedText(player[4]->getName(), 695, 210, 270);
    dc.DrawText(player[5]->getName(), 450, 475);
}

void GamePanel::drawBid(wxBufferedPaintDC &dc) {
    wxBrush brush(wxColour(255, 255, 238));
    dc.SetBrush(brush);
    dc.DrawRectangle(618, 433, 75, 60);
    
    dc.SetTextForeground(*wxBLACK);
    dc.SetFont(TITLE_FONT);
    dc.DrawText("Bid", 643, 435);
    
    const Round *round = bridge->getRound();
    
    if (round != NULL) {
        const Bid &bid = round->getBidHistory().getWinning();
        
        if (bid.getTricks() == 0) {
            return;
        }
        
        wxString str;
        str << bid.getTricks();
        
        int x = 640;
        enum Suit trump = bid.getTrump();
        
        if (trump == LOW) {
            x -= 5;
            str += wxT(" Low");
        } else if (trump == HIGH) {
            x -= 10;
            str += wxT(" High");
        }
        
        dc.SetFont(TEXT_FONT);
        dc.DrawText(str, x, 455);
        
        if ((trump != LOW) && (trump != HIGH)) {
            if (trump == SPADES) {
                str = wxT("images/spade.bmp");
            } else if (trump == DIAMONDS) {
                str = wxT("images/diamond.bmp");
            } else if (trump == CLUBS) {
                str = wxT("images/club.bmp");
            } else if (trump == HEARTS) {
                str = wxT("images/heart.bmp");
            }
            
            wxImage image(str, wxBITMAP_TYPE_BMP);
            wxBitmap bmp(image);
            dc.DrawBitmap(bmp, 650, 455, false);
        }
        
        dc.DrawText(bid.getTeamString(), 643, 470);
    }
}

void GamePanel::drawTrickCount(wxBufferedPaintDC &dc) {
    wxBrush brush(wxColour(255, 255, 238));
    dc.SetBrush(brush);
    dc.DrawRectangle(618, 2, 75, 60);
    dc.DrawRectangle(2, 433, 75, 60);
    
    int us = 0, them = 0;
    
    if (bridge->getRound() != NULL) {
        us = bridge->getRound()->getTricks(0);
        them = bridge->getRound()->getTricks(1);
    }
    
    dc.SetTextForeground(*wxBLACK);
    dc.SetFont(TITLE_FONT);
    dc.DrawText("Us", 30, 435);
    dc.DrawText("Them", 635, 5);
    
    wxString str;
    dc.SetFont(TRICK_FONT);
    
    str.Printf("%d", us);
    dc.DrawText(str, 30, 450);
    
    str.Printf("%d", them);
    dc.DrawText(str, 645, 20);
}

void GamePanel::drawScore(wxBufferedPaintDC &dc) {
    wxBrush brush(wxColour(255, 255, 238));
    dc.SetBrush(brush);
    dc.DrawRectangle(2, 2, 75, 60);
    
    dc.SetTextForeground(*wxBLACK);
    dc.SetFont(TITLE_FONT);
    dc.DrawText(wxT("Score"), 20, 2);
    
    dc.SetFont(TEXT_FONT);
    wxString str;
    
    str.Printf("Us:");
    dc.DrawText(str, 5, 25);
    
    str.Printf("Them:");
    dc.DrawText(str, 5, 40);
    
    for (int i = 0; i < 2; i++) {
        int score = Game::getInstance().getScore(i);
        
        if (score < 0) {
            score = 0 - score;
            dc.SetTextForeground(*wxRED);
        } else {
            dc.SetTextForeground(*wxBLACK);
        }
        
        str = "";
        str << score;
        
        dc.DrawText(str, 50, (25 + (i * 15)));
    }
}

void GamePanel::drawMessage(wxBufferedPaintDC &dc) {
    dc.SetPen(wxPen(*wxBLACK));
    dc.SetBrush(wxBrush(wxColour(255, 255, 238)));
    dc.DrawRectangle(230, 235, 235, 30);
    
    dc.SetFont(NAME_FONT);
    dc.SetTextForeground(*wxBLACK);
    
    // this could be a problem is message is longer than box!
    int x = 240 + ((215 - (message.Length() * 8)) / 2);
    dc.DrawText(message, x, 240);
}

void GamePanel::drawHands(wxBufferedPaintDC &dc) {
    for (int i = 0; i < 6; i++) {
        const Hand &hand = player[i]->getHand();
        int id = player[i]->getID();
        
        for (unsigned int i = 0; i < hand.size(); i++) {
            int x = HAND_POS[id].x, y = HAND_POS[id].y;
            wxImage image;
            
            if ((id == 0) || cheating) {
                image = hand.get(i).toImage();
            } else {
                image = Card::getBackImage();
            }
            
            if ((id == 1) || (id == 4)) {
                y += (15 * i);
                image = image.Rotate90();
            } else {
                x += (15 * i);
            }
            
            wxBitmap bmp(image);
            dc.DrawBitmap(bmp, x, y, false);
        }
    }
}

void GamePanel::drawBidding(wxBufferedPaintDC &dc) {
    const Round *round = bridge->getRound();
    
    if (round != NULL) {
        const BidHistory &bids = round->getBidHistory();
        int x, y;
        
        dc.SetFont(NAME_FONT);
        dc.SetPen(wxPen(*wxBLACK));
        dc.SetBrush(wxBrush(*wxWHITE));
        dc.SetTextForeground(*wxBLACK);
        
        for (unsigned int i = 0; i < bids.size(); i++) {
            const Bid &bid = bids.get(i);
            enum Suit trump = bid.getTrump();
            int id = bid.getPlayer()->getID();
            int width = 10;
            
            x = BIDDING_POS[id].x;
            y = BIDDING_POS[id].y;
            
            if (trump == LOW) {
                width += 35;
            } else if (trump == SPADES) {
                width += 55;
            } else if (trump == DIAMONDS) {
                width += 75;
            } else if (trump == CLUBS) {
                width += 45;
            } else if (trump == HEARTS) {
                width += 50;
            } else {
                width += 35;
            }
        
            if (bid.isAlone()) {
                width += 35;
            } else {
                width += 15;
            }
            
            if (bid.getTricks() == 0) {
                width = 45;
            }
        
            if (id == 4) {
                x -= width;
            } else if (id != 1) {
                x = x + ((176 - width) / 2);
            }
            
            dc.DrawRectangle(x, y, width, 30);
            dc.DrawText(bid.getBidString(), (x + 5), (y + 5));
        }
    }
}

void GamePanel::drawCards(wxBufferedPaintDC &dc) {
    const Trick *trick = bridge->getTrick();
    
    if (trick != NULL) {
        const std::vector<Play> &plays = trick->getPlayHistory();
        
        for (unsigned int i = 0; i < plays.size(); i++) {
            const Play &play = plays[i];
            int id = play.getPlayer()->getID();
            
            wxImage image = play.getCard().toImage();
            
            if (play.isSignal()) {
                image.SetMaskColour(0, 0xA0, 0);
                image = image.Rotate(-0.0872, wxPoint(0, 0));
            }
            
            wxBitmap bmp(image);
            dc.DrawBitmap(bmp, CARD_POS[id].x, CARD_POS[id].y, false);
        }
    }
}

void GamePanel::drawWinner(wxBufferedPaintDC &dc) {
    wxString winner = wxT("Winner: ");
    
    if (Game::getInstance().isWinner(0)) {
        winner += wxT("Us");
    } else {
        winner += wxT("Them");
    }
    
    setMessage(winner);
    drawMessage(dc);
}

void GamePanel::onLeftMouseDown(wxMouseEvent &event) {
    if (clicks != NULL) {
        std::pair<wxPoint, bool> pair(event.GetPosition(), event.ShiftDown());
        clicks->push(pair);
        cond->Signal();
    }
    
    event.Skip();
}

void GamePanel::onShowScoreDialog(wxCommandEvent &) {
    scoreDialog->regenerate(Game::getInstance().getScoreHistory());
    scoreDialog->CentreOnParent();
    scoreDialog->Show();
}

void GamePanel::onShowBidDialog(wxCommandEvent &) {
    bidDialog->CentreOnParent();
    bidDialog->Show();
}

