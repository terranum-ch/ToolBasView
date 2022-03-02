/***************************************************************************
 databaseoperation.h
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
#ifndef _DATABASEOPERATION_H_
#define _DATABASEOPERATION_H_

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// Include wxWidgets' headers
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class DatabaseOp_DLG : public wxDialog {
 private:
  bool m_Check;
  bool m_Repair;
  bool m_Optimize;
  wxCheckBox* m_CheckCtrl;
  wxCheckBox* m_OptimizeCtrl;
  wxCheckBox* m_RepairCtrl;

  void _CreateControls();

  virtual bool TransferDataFromWindow();
  void OnOk(wxCommandEvent& event);

 public:
  DatabaseOp_DLG(wxWindow* window, wxWindowID id, const wxString& title = _("Database operations"));
  virtual ~DatabaseOp_DLG();

  inline const bool GetCheck() const;
  inline const bool GetRepair() const;
  inline const bool GetOptimize() const;
};

inline const bool DatabaseOp_DLG::GetCheck() const {
  return m_Check;
}

inline const bool DatabaseOp_DLG::GetRepair() const {
  return m_Repair;
}

inline const bool DatabaseOp_DLG::GetOptimize() const {
  return m_Optimize;
}

#endif
