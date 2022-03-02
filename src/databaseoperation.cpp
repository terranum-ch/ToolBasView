/***************************************************************************
 databaseoperation.cpp
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

#include "databaseoperation.h"

void DatabaseOp_DLG::_CreateControls() {
  this->SetSizeHints(wxDefaultSize, wxDefaultSize);

  wxBoxSizer* bSizer1;
  bSizer1 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizer2;
  bSizer2 = new wxBoxSizer(wxVERTICAL);

  wxStaticText* m_staticText1;
  m_staticText1 =
      new wxStaticText(this, wxID_ANY, _("Check operations to perform"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText1->Wrap(-1);
  bSizer2->Add(m_staticText1, 0, wxALL, 5);

  m_CheckCtrl = new wxCheckBox(this, wxID_ANY, _("CHECK"), wxDefaultPosition, wxDefaultSize, 0);
  bSizer2->Add(m_CheckCtrl, 0, wxALL, 5);

  m_OptimizeCtrl = new wxCheckBox(this, wxID_ANY, _("OPTIMIZE"), wxDefaultPosition, wxDefaultSize, 0);
  m_OptimizeCtrl->SetValue(true);
  bSizer2->Add(m_OptimizeCtrl, 0, wxALL, 5);

  m_RepairCtrl = new wxCheckBox(this, wxID_ANY, _("REPAIR"), wxDefaultPosition, wxDefaultSize, 0);
  bSizer2->Add(m_RepairCtrl, 0, wxALL, 5);

  bSizer1->Add(bSizer2, 1, wxEXPAND | wxALL, 5);

  wxStdDialogButtonSizer* m_sdbSizer1;
  wxButton* m_sdbSizer1OK;
  wxButton* m_sdbSizer1Cancel;
  m_sdbSizer1 = new wxStdDialogButtonSizer();
  m_sdbSizer1OK = new wxButton(this, wxID_OK);
  m_sdbSizer1->AddButton(m_sdbSizer1OK);
  m_sdbSizer1Cancel = new wxButton(this, wxID_CANCEL);
  m_sdbSizer1->AddButton(m_sdbSizer1Cancel);
  m_sdbSizer1->Realize();
  bSizer1->Add(m_sdbSizer1, 0, wxALL | wxEXPAND, 5);

  this->SetSizer(bSizer1);
  this->Layout();

  this->Centre(wxBOTH);
}

bool DatabaseOp_DLG::TransferDataFromWindow() {
  m_Check = m_CheckCtrl->GetValue();
  m_Repair = m_RepairCtrl->GetValue();
  m_Optimize = m_OptimizeCtrl->GetValue();
  return true;
}

void DatabaseOp_DLG::OnOk(wxCommandEvent& event) {
  Close(wxID_OK);
}

DatabaseOp_DLG::DatabaseOp_DLG(wxWindow* window, wxWindowID id, const wxString& title)
    : wxDialog(window, id, title, wxDefaultPosition, wxDefaultSize) {
  m_Check = false;
  m_Repair = false;
  m_Optimize = false;
  m_CheckCtrl = NULL;
  m_OptimizeCtrl = NULL;
  m_RepairCtrl = NULL;

  _CreateControls();
}

DatabaseOp_DLG::~DatabaseOp_DLG() {}
