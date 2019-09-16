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
 
// $Id: GameThread.hh,v 1.8 2005/07/28 05:36:29 technoplaza Exp $

#ifndef _GAMETHREAD_HH_
#define _GAMETHREAD_HH_

#include <wx/thread.h>

class Game;

/**
 * Class to run a Game in a background thread.
 */
class GameThread : public wxThread {
private:
    Game *game;

public:
    /**
     * Creates a new GameThread.
     *
     * @param game The Game to play in this GameThread.
     */
    GameThread(Game *game);
    
    /**
     * Called when this GameThread is started.
     *
     * @return The exit code.
     */
    void *Entry();
};

#endif

