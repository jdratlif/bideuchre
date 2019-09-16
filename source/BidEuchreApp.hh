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
 
// $Id: BidEuchreApp.hh,v 1.1.1.1 2005/08/06 09:52:49 technoplaza Exp $

#ifndef _BIDEUCHREAPP_HH_
#define _BIDEUCHREAPP_HH_

/**
 * The main application class and launching point.
 */
class BidEuchreApp : public wxApp {
private:    
    DECLARE_CLASS(BidEuchreApp)
    
public:
    /**
     * Creates a new BidEuchreApp object.
     */
    BidEuchreApp();
    
    /**
     * Destructor for a BidEuchreApp.
     */
    ~BidEuchreApp();
    
    /**
     * Callback for application initializtion.
     *
     * @return true if the application was initialized; false otherwise.
     */
    bool OnInit();
};

DECLARE_APP(BidEuchreApp)

#endif

