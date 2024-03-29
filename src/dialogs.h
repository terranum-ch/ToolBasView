/*!
    @file dialogs.h
    @brief definition of ressources dialogs
    @author Lucien Schreiber (c) CREALP 2007
*/

#ifndef __dialogs_H__
#define __dialogs_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "dialogs.h"
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/grid.h>
#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/statline.h>
#include <wx/tglbtn.h>
#include <wx/toolbar.h>
#include <wx/treectrl.h>

const int ID_TEXTCTRL = 10000;
const int ID_REQUEST_RESULT = 10001;
const int ID_BTN_SHOWRESULTS = 10002;
const int ID_LINE = 10003;
const int ID_PROCESS = 10004;
const int ID_HISTORY = 10012;
wxSizer *SQLPROCESS(wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE);

const int ID_ABOUT_TEXT = 10005;
const int ID_SQL_BMP = 10006;
wxSizer *ABOUT(wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE);

const int ID_TEXT2 = 10007;
const int ID_TXT_DB_PATH = 10008;
const int ID_BTN_CHOOSE_PATH = 10009;
const int ID_TXT_DB_NAME = 10010;
wxSizer *NEWDBASE(wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE);

const int ID_GRID_PROCESS = 10011;
const int ID_COLROW_INFO = 10015;
wxSizer *SHOWRESULT(wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE);

#endif
