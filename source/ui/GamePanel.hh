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
 
// $Id: GamePanel.hh,v 1.1.1.1 2005/08/06 09:52:52 technoplaza Exp $

#ifndef _GAMEPANEL_HH_
#define _GAMEPANEL_HH_

#include <queue>
#include <utility>

#include <wx/panel.h>

#include "ui/UIConstants.hh"

class wxBufferedPaintDC;
class Player;
class Bridge;
class BidDialog;
class GUI;
class ScoreDialog;

/**
 * The GUI drawing pane for a Bid Euchre game.
 */
class GamePanel : public wxPanel {
private:    
    DECLARE_DYNAMIC_CLASS(GamePanel)
    DECLARE_EVENT_TABLE()
    
    std::queue< std::pair<wxPoint, bool> > *clicks;
    wxString message;
    Player **player;
    Bridge *bridge;
    BidDialog *bidDialog;
    GUI *gui;
    ScoreDialog *scoreDialog;
    enum Table table;
    bool cheating;
    
    /**
     * Draws the Player names on the screen.
     *
     * @param dc The device context.
     */
    void drawNames(wxBufferedPaintDC &dc);
    
    /**
     * Draws the bid for this Round.
     *
     * @param dc The device context.
     */
    void drawBid(wxBufferedPaintDC &dc);
    
    /**
     * Draws the trick count.
     *
     * @param dc The device context.
     */
    void drawTrickCount(wxBufferedPaintDC &dc);
    
    /**
     * Draws the score.
     *
     * @param dc The device context.
     */
    void drawScore(wxBufferedPaintDC &dc);
    
    /**
     * Draws the message.
     *
     * @param dc The device context.
     */
    void drawMessage(wxBufferedPaintDC &dc);
    
    /**
     * Draws the Players Hands.
     *
     * @param dc The device context.
     */
    void drawHands(wxBufferedPaintDC &dc);
    
    /**
     * Draws the Players Bids.
     *
     * @param dc The device context.
     */
    void drawBidding(wxBufferedPaintDC &dc);
    
    /**
     * Draws the played cards.
     *
     * @param dc The device context.
     */
    void drawCards(wxBufferedPaintDC &dc);
    
    /**
     * Draws the winner.
     *
     * @param dc The device context.
     */
    void drawWinner(wxBufferedPaintDC &dc);
    
    /**
     * Called when the left mouse button is down.
     *
     * @param event The associated mouse event.
     */
    void onLeftMouseDown(wxMouseEvent &event);
    
    /**
     * Called when the score dialog should be shown.
     *
     * @param event The associated command event.
     */
    void onShowScoreDialog(wxCommandEvent &event);
    
    /**
     * Called when the bid dialog should be shown.
     *
     * @param event The associated command event.
     */
    void onShowBidDialog(wxCommandEvent &event);
    
public:
    static const wxFont TITLE_FONT;
    static const wxFont TEXT_FONT;
    static const wxFont NAME_FONT;
    static const wxFont TRICK_FONT;
    
    static const wxPoint HAND_POS[];
    static const wxPoint CARD_POS[];
    static const wxPoint BIDDING_POS[];

    /**
     * Creates a new GamePanel object.
     */
    GamePanel();
    
    /**
     * Creates a new GamePanel object.
     *
     * @param parent The parent window.
     */
    GamePanel(wxWindow* parent);
    
    /**
     * Destructor for a GamePanel.
     */
    ~GamePanel();
              
    /**
     * Starts the Game.
     */
    void startGame();
              
    /**
     * Called when a paint event is received.
     *
     * @param event The associated paint event.
     */
    void onPaint(wxPaintEvent &event);
    
    /**
     * Called when an erase background event is received.
     *
     * @param event The associated erase event.
     */
    void onEraseBackground(wxEraseEvent &event);
    
    /**
     * Sets the table region (REG_BIDDING or REG_CARDS).
     *
     * @param table The table region.
     */
    void setTable(enum Table table);
    
    /**
     * Asks for mouse clicks to be delivered to a given queue.
     *
     * @param clicks The mouse click queue.
     */
    void requestClicks(std::queue<std::pair<wxPoint, bool> > *clicks = NULL);
    
    /**
     * Gets the BidDialog used by this GamePanel.
     *
     * @return The BidDialog.
     */
    BidDialog *getBidDialog() const;
    
    /**
     * Sets the message string.
     *
     * @param message The new message string.
     */
    void setMessage(const wxString &message = wxT("Bid Euchre"));
    
    /**
     * Toggles cheat mode.
     */
    void toggleCheatMode();
};

inline GamePanel::GamePanel() {}
inline void GamePanel::onEraseBackground(wxEraseEvent &) {}
inline void GamePanel::setTable(enum Table table) { this->table = table; }
inline void GamePanel::requestClicks(std::queue< std::pair<wxPoint, bool> > *clicks) { this->clicks = clicks; }
inline BidDialog *GamePanel::getBidDialog() const { return bidDialog; }
inline void GamePanel::setMessage(const wxString &message) { this->message = message; }
inline void GamePanel::toggleCheatMode() { cheating = !cheating; }

#endif

