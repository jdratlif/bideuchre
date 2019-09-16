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
 
// $Id: AppConstants.hh,v 1.1.1.1 2005/08/06 09:52:49 technoplaza Exp $

#ifndef _APPCONSTANTS_HH_
#define _APPCONSTANTS_HH_

class wxCondition;
class wxMutex;
class wxString;

/// The application name
extern const wxString *APP_NAME;
    
/// The version string
extern const wxString *APP_VERSION;
    
/// The copyright string
extern const wxString *APP_COPYRIGHT;
    
/// The project URL
extern const wxString *APP_URL;

/// The global thread condition
extern wxCondition *cond;

/// The global mutex
extern wxMutex *mutex;

#endif

