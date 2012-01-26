/***************************************************************************
 exportcsv_dlg.h
 -------------------
 copyright            : (C) 2012 CREALP Lucien Schreiber 
 email                : lucien.schreiber at crealp dot vs dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef _EXPORTCSV_DLG_H
#define _EXPORTCSV_DLG_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// Include wxWidgets' headers
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include <wx/wupdlock.h>
#include <wx/busyinfo.h>




class DataBase;

const int ID_EXPORTCSV_DLG = wxID_HIGHEST + 1;
const int  ID_M_LISTTABLESCTRL = wxID_HIGHEST + 2;
const int  ID_SELECT_ALL = wxID_HIGHEST + 3;
const int  ID_SELECT_CLEAR = wxID_HIGHEST + 4;
const int  ID_LIMIT_ENABLE = wxID_HIGHEST + 5;


class ExportCSV_DLG : public wxDialog {
private:
    wxCheckListBox* m_ListTablesCtrl;
    wxSpinCtrl* m_LimitRecordValueCtrl;
    wxCheckBox* m_LimitRecordUse;
    wxCheckBox* m_UnicodeExportCtrl;
    DataBase * m_Database;

    void _CreateControls();
    
    void OnListSelect(wxCommandEvent & event);
    void OnListClear(wxCommandEvent & event);    
    void OnOk(wxCommandEvent & event);
    DECLARE_EVENT_TABLE();
    
public:
    ExportCSV_DLG(wxWindow * window, wxWindowID id, const wxString & title, DataBase * database);
    virtual ~ExportCSV_DLG();
};
#endif
