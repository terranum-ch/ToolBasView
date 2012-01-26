/***************************************************************************
 exportcsv_dlg.cpp
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

#include "exportcsv_dlg.h"
#include "database.h"


BEGIN_EVENT_TABLE( ExportCSV_DLG, wxDialog )
    EVT_BUTTON( ID_SELECT_ALL, ExportCSV_DLG::OnListSelect )
    EVT_BUTTON( ID_SELECT_CLEAR, ExportCSV_DLG::OnListClear )
    EVT_BUTTON( wxID_OK, ExportCSV_DLG::OnOk )
END_EVENT_TABLE()


ExportCSV_DLG::ExportCSV_DLG(wxWindow * window, wxWindowID id, const wxString & title, DataBase * database) : 
wxDialog(window, id, title) {
    m_Database = database;
    wxASSERT(m_Database);
    _CreateControls();
    
    
    // load tables
    if (m_Database->DataBaseQuery(_T("SHOW TABLES"))==false){
        wxLogError(_("Loading tables failed!"));
        return;
    }
    
	wxArrayString myTables;
	m_Database->DataBaseGetResults(myTables);
	m_Database->DataBaseClearResults();	
    m_ListTablesCtrl->Append(myTables);
}


ExportCSV_DLG::~ExportCSV_DLG() {
}



void ExportCSV_DLG::_CreateControls() {
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_ListTablesCtrlChoices;
	m_ListTablesCtrl = new wxCheckListBox( this, ID_M_LISTTABLESCTRL, wxDefaultPosition, wxSize( 250,250 ), m_ListTablesCtrlChoices, 0 );
	bSizer2->Add( m_ListTablesCtrl, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxButton* m_button1;
	m_button1 = new wxButton( this, ID_SELECT_ALL, _("Select all"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL, 5 );
	
	wxButton* m_button2;
	m_button2 = new wxButton( this, ID_SELECT_CLEAR, _("Clear selection"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button2, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Limit") ), wxVERTICAL );
	
	wxCheckBox* m_checkBox1;
	m_checkBox1 = new wxCheckBox( this, ID_LIMIT_ENABLE, _("Limit records"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_checkBox1, 0, wxALL, 5 );
	
	m_LimitRecordValueCtrl = new wxSpinCtrl( this, wxID_ANY, wxT("500"), wxDefaultPosition, wxSize( 150,-1 ), wxSP_ARROW_KEYS, 1, 100000, 500 );
	sbSizer1->Add( m_LimitRecordValueCtrl, 0, wxALL|wxEXPAND, 5 );
	
	bSizer3->Add( sbSizer1, 0, wxEXPAND|wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxStdDialogButtonSizer* m_sdbSizer1;
	wxButton* m_sdbSizer1OK;
	wxButton* m_sdbSizer1Cancel;
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer1->Add( m_sdbSizer1, 0, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}



void ExportCSV_DLG::OnListSelect(wxCommandEvent & event) {
    wxWindowUpdateLocker myLocker(m_ListTablesCtrl);
    for (unsigned int i = 0; i<m_ListTablesCtrl->GetCount(); i++) {
        m_ListTablesCtrl->Check(i,true);
    }
}



void ExportCSV_DLG::OnListClear(wxCommandEvent & event) {
    wxWindowUpdateLocker myLocker(m_ListTablesCtrl);
    for (unsigned int i = 0; i<m_ListTablesCtrl->GetCount(); i++) {
        m_ListTablesCtrl->Check(i,false);
    }
}



void ExportCSV_DLG::OnOk(wxCommandEvent & event) {
    Close();
}

