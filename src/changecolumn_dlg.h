/***************************************************************************
 changecolumn_dlg
 -------------------
 copyright            : (C) 2013 Lucien Schreiber
 email                : lucien.schreiber at gmail dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef _CHANGE_COLUMN_DLG_H_
#define _CHANGE_COLUMN_DLG_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class DataBase;
const wxString m_FieldTypes[] = {_T("INTEGER*"), _T("FLOAT*"), _T("DATE"), _T("TIME"), _T("DATETIME"), _T("VARCHAR*")};
class ChangeColumn_DLG : public wxDialog {
 private:
  wxChoice* m_ColumnCtrl;
  wxRadioBox* m_TypeCtrl;
  wxTextCtrl* m_OptionCtrl;
  wxStaticText* m_ResultCtrl;
  wxButton* m_BtnCtrlOK;
  wxButton* m_BtnCtrlApply;

  DataBase* m_Database;
  wxString m_TableName;

  void _CreateControls();
  void _LoadColumnsIntoArray(wxArrayString& array);
  void _DoApplyChange();

  void OnApplyButton(wxCommandEvent& event);
  void OnOkButton(wxCommandEvent& event);

 public:
  ChangeColumn_DLG(wxWindow* parent, DataBase* database, const wxString& tablename, wxWindowID id = wxID_ANY,
                   const wxString& title = _("Change Column Type"), const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_DIALOG_STYLE);
  ~ChangeColumn_DLG();
};

#endif
