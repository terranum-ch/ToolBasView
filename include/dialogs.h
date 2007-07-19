/*!
    @file dialogs.h
    @brief definition of ressources dialogs
*/


#ifndef __dialogs_H__
#define __dialogs_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "dialogs_wdr.h"
#endif


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


const int ID_TEXTCTRL = 10000;
const int ID_REQUEST_RESULT = 10001;
const int ID_LINE = 10002;
const int ID_PROCESS = 10003;
wxSizer *SQLPROCESS( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_ABOUT_TEXT = 10004;
const int ID_SQL_BMP = 10005;
wxSizer *ABOUT( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );



#endif

