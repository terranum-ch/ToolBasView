/*!
    @header interface.h
    @abstract   definition of interface	
    @discussion this file is mainly used for interface definition
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

// Declare window functions

extern const int ID_LEFT_SPLIT;
wxSizer *INTERFACE( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern const int ID_LISTTABLE;
wxSizer *LEFT( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern const int ID_RIGHT_SPLIT;
wxSizer *RIGHT( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern const int ID_GRID;
wxSizer *RIGHT_TOP( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern const int ID_TEXT;
extern const int ID_LOG;
wxSizer *RIGHT_BTM( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern const int ID_FILE_MENU;
extern const int ID_OPEN_DB;
extern const int ID_MENU;
extern const int ID_OP_MENU;
extern const int ID_PROCESS_MENU;
extern const int ID_NEW_DBASE;
extern const int ID_MENU_STATISTICS;
wxMenuBar *MENU();

#endif
