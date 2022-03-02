/***************************************************************************
 deletetabledata_dlg.h
 dialog for deleting data from database
 -------------------
 copyright            : (C) 2007 CREALP Lucien Schreiber
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

#ifndef _DELETETABLEDATA_DLG_H_
#define _DELETETABLEDATA_DLG_H_

#include "database.h"
#include "wx/statline.h"

#define ID_DELETETABLEDATA_DLG 10004
#define ID_DLGDEL_TABLES 10005
#define ID_DLGDEL_CHK_DATA 10006
#define ID_DLGDEL_CHK_TABLE 10007
#define ID_DLGDEL_VACUUM 10008
#define ID_STATICLINE2 10010
#define SYMBOL_DELETETABLEDATA_DLG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX
#define SYMBOL_DELETETABLEDATA_DLG_TITLE _("Delete data")
#define SYMBOL_DELETETABLEDATA_DLG_IDNAME ID_DELETETABLEDATA_DLG
#define SYMBOL_DELETETABLEDATA_DLG_SIZE wxSize(400, 300)
#define SYMBOL_DELETETABLEDATA_DLG_POSITION wxDefaultPosition

enum DELETE_FLAGS { DEL_FLAGS_DATA = 1, DEL_FLAGS_TABLE = 2, DEL_FLAGS_VACUUM = 4, DEL_FLAGS_ALL = 7 };

class DELETETABLEDATA_DLG : public wxDialog {
  DECLARE_DYNAMIC_CLASS(DELETETABLEDATA_DLG)
  DECLARE_EVENT_TABLE()

  DataBase* m_pDatabase;

  int m_DlgFlags;

  void OnPressOK(wxCommandEvent& event);

 public:
  DELETETABLEDATA_DLG();
  DELETETABLEDATA_DLG(wxWindow* parent, wxWindowID id = SYMBOL_DELETETABLEDATA_DLG_IDNAME, DataBase* database = NULL,
                      const wxString& caption = SYMBOL_DELETETABLEDATA_DLG_TITLE,
                      const wxPoint& pos = SYMBOL_DELETETABLEDATA_DLG_POSITION,
                      const wxSize& size = SYMBOL_DELETETABLEDATA_DLG_SIZE,
                      long style = SYMBOL_DELETETABLEDATA_DLG_STYLE);

  bool Create(wxWindow* parent, wxWindowID id = SYMBOL_DELETETABLEDATA_DLG_IDNAME,
              const wxString& caption = SYMBOL_DELETETABLEDATA_DLG_TITLE,
              const wxPoint& pos = SYMBOL_DELETETABLEDATA_DLG_POSITION,
              const wxSize& size = SYMBOL_DELETETABLEDATA_DLG_SIZE, long style = SYMBOL_DELETETABLEDATA_DLG_STYLE);

  ~DELETETABLEDATA_DLG();

  void Init();

  void SetActiveFlags(int iFlags) {
    m_DlgFlags = iFlags;
  }
  int GetSelectedFlags() {
    return m_DlgFlags;
  }
  wxArrayString m_SelectedTables;

  virtual bool TransferDataToWindow();
  virtual bool TransferDataFromWindow();

  void CreateControls();

  wxCheckBox* m_DlgDel_Chk_Data;
  wxCheckBox* m_DlgDel_Chk_table;
  wxCheckBox* m_DlgDel_Chk_Vacuum;
  wxCheckListBox* m_DlgDel_ListTables;
};

#endif
