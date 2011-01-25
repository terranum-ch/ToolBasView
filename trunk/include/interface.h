/*!
@file interface.h
@brief  definition of sizer function for the interface.
@author Lucien Schreiber (c) CREALP 2007
*/


#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "main_pane_wdr.h"
#endif

// Include wxWidgets' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/toolbar.h>
#include <wx/tglbtn.h>
#include <wx/headerctrl.h>

// Declare window functions

const int ID_LEFT_SPLIT = 10100;
wxSizer *INTERFACE( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LISTTABLE = 10101;
wxSizer *LEFT( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RIGHT_SPLIT = 10102;
wxSizer *RIGHT( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_GRID = 10103;
wxSizer *RIGHT_TOP( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT = 10104;
const int ID_LOG = 10105;
wxSizer *RIGHT_BTM( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FILE_MENU = 10106;
const int ID_OPEN_DB = 10107;
const int ID_MENU = 10108;
const int ID_OP_MENU = 10109;
const int ID_PROCESS_MENU = 10110;
const int ID_NEW_DBASE = 10111;
const int ID_MENU_STATISTICS = 10112;
const int ID_MENU_SPATIAL_ADD = 10113;
const int ID_MENU_DELETE = 10114;
const int ID_MENU_SPATIAL_SEARCH = 10115;
wxMenuBar *MENU();

#endif
