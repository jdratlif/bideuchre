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
 
// $Id: UIConstants.hh,v 1.15 2005/08/01 09:17:37 technoplaza Exp $

#ifndef _UICONSTANTS_HH_
#define _UICONSTANTS_HH_

#define FRAME_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
#define FRAME_TITLE wxT("Bid Euchre")
#define FRAME_SIZE wxSize(706, 552)
#define PANEL_STYLE wxSUNKEN_BORDER | wxTAB_TRAVERSAL
#define SCORE_DIALOG_STYLE wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX
#define SCORE_DIALOG_TITLE wxT("Score")
#define SCORE_DIALOG_SIZE wxSize(400, 400)
#define BID_DIALOG_STYLE wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX
#define BID_DIALOG_TITLE wxT("Bid")
#define HELP_DIALOG_STYLE wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(EVT_SCORE_DIALOG, 1)
    DECLARE_LOCAL_EVENT_TYPE(EVT_BID_DIALOG, 2)
END_DECLARE_EVENT_TYPES()

enum {
    ID_FRAME = 10000,
    ID_PANEL,
    ID_SD_DIALOG,
    ID_SD_HTMLWINDOW,
    ID_SD_BUTTON,
    ID_BD_DIALOG,
    ID_BD_1_RADIO,
    ID_BD_2_RADIO,
    ID_BD_3_RADIO,
    ID_BD_4_RADIO,
    ID_BD_5_RADIO,
    ID_BD_6_RADIO,
    ID_BD_7_RADIO,
    ID_BD_8_RADIO,
    ID_BD_BEST_RADIO,
    ID_BD_SPADES_RADIO,
    ID_BD_DIAMONDS_RADIO,
    ID_BD_CLUBS_RADIO,
    ID_BD_HEARTS_RADIO,
    ID_BD_LOW_RADIO,
    ID_BD_HIGH_RADIO,
    ID_BD_BID_BUTTON,
    ID_BD_PASS_BUTTON,
    ID_HD_DIALOG,
    ID_HD_HTMLWINDOW,
    IDM_FILE_NEWGAME,
    IDM_OPTIONS_CHEATMODE,
    IDM_HELP_PLAY,
    IDM_HELP_RULES
};

enum Table {
    TABLE_BIDS,
    TABLE_CARDS
};

#endif

