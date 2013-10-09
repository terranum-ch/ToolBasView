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

#include "changecolumn_dlg.h"
#include "database.h"
#include "databaseresult.h"

ChangeColumn_DLG::ChangeColumn_DLG( wxWindow* parent, DataBase * database, const wxString & tablename, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){
    wxASSERT(database);
    m_Database = database;
    
    wxASSERT(tablename != wxEmptyString);
    m_TableName = tablename;
    _CreateControls();
    
    
    m_BtnCtrlApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeColumn_DLG::OnApplyButton ), NULL, this );
	m_BtnCtrlOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeColumn_DLG::OnOkButton ), NULL, this );
}



ChangeColumn_DLG::~ChangeColumn_DLG(){
    m_BtnCtrlApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeColumn_DLG::OnApplyButton ), NULL, this );
	m_BtnCtrlOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeColumn_DLG::OnOkButton ), NULL, this );
}



void ChangeColumn_DLG::_LoadColumnsIntoArray (wxArrayString & array){
    array.Clear();
    wxString myQuery = wxString::Format(_T("SHOW COLUMNS FROM `%s`"), m_TableName);
    if (m_Database->DataBaseQuery(myQuery) != false) {
        DataBaseResult myResult;
        m_Database->DataBaseGetResults(&myResult);
        if (myResult.GetRowCount() > 0) {
            while (myResult.NextRow()) {
                wxString myColName;
                //wxString myColType;
                myResult.GetValue(0, myColName);
                //myResult.GetValue(1, myColType);
                
                array.Add(wxString::Format(_T("%s"), myColName));
            }
        }
    }
}


void ChangeColumn_DLG::OnApplyButton( wxCommandEvent& event ){
    _DoApplyChange();
}



void ChangeColumn_DLG::OnOkButton( wxCommandEvent& event ){
    _DoApplyChange();
    EndModal(wxID_OK);
}


void ChangeColumn_DLG::_DoApplyChange(){
    wxString myColName = m_ColumnCtrl->GetStringSelection();
    
    wxString myTypeName = m_TypeCtrl->GetStringSelection();
    myTypeName.Replace(_T("*"), _T(""));
    
    wxString myChangeTxt = myTypeName + m_OptionCtrl->GetValue() + _T(" NULL DEFAULT NULL");
    wxString myQuery = wxString::Format(_T("ALTER TABLE `%s` MODIFY COLUMN `%s` %s;"), m_TableName, myColName, myChangeTxt );
    
    if (m_Database->DataBaseQueryNoResults(myQuery) == false) {
        wxLogError(_("Changing columns type failed!"));
        wxLogError(myQuery);
        
        m_ResultCtrl->SetBackgroundColour(*wxRED);
        m_ResultCtrl->SetLabel(_("Failed to change type for column: ") + myColName);
    }
    else {
        m_ResultCtrl->wxWindowBase::SetBackgroundColour((*wxGREEN));
        m_ResultCtrl->SetLabel( _("OK type changed for column: ") + myColName);
    }
}


void ChangeColumn_DLG::_CreateControls (){
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Column") ), wxVERTICAL );
    
    wxArrayString myColumns;
    _LoadColumnsIntoArray(myColumns);
    
	m_ColumnCtrl = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, myColumns, 0 );
	m_ColumnCtrl->SetSelection( 0 );
	sbSizer1->Add( m_ColumnCtrl, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer1, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_TypeCtrl = new wxRadioBox( this, wxID_ANY, _("New Type"), wxDefaultPosition, wxDefaultSize, sizeof(m_FieldTypes) / sizeof(wxString), m_FieldTypes, 1, wxRA_SPECIFY_COLS );
	m_TypeCtrl->SetSelection( 0 );
	bSizer2->Add( m_TypeCtrl, 1, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Option") ), wxHORIZONTAL );
	
	m_OptionCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_OptionCtrl, 1, wxALL, 5 );
	
	
	bSizer2->Add( sbSizer3, 1, wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( 0, 0, 0, wxEXPAND, 5 );

    m_ResultCtrl = new wxStaticText( this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT );
	m_ResultCtrl->Wrap( -1 );
	bSizer1->Add( m_ResultCtrl, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
    
	wxStdDialogButtonSizer* m_BtnCtrl;
	wxButton* m_BtnCtrlCancel;
	m_BtnCtrl = new wxStdDialogButtonSizer();
	m_BtnCtrlOK = new wxButton( this, wxID_OK );
	m_BtnCtrl->AddButton( m_BtnCtrlOK );
	m_BtnCtrlApply = new wxButton( this, wxID_APPLY );
	m_BtnCtrl->AddButton( m_BtnCtrlApply );
	m_BtnCtrlCancel = new wxButton( this, wxID_CANCEL );
	m_BtnCtrl->AddButton( m_BtnCtrlCancel );
	m_BtnCtrl->Realize();
	
	bSizer1->Add( m_BtnCtrl, 0, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( bSizer1 );
    this->Layout();
	bSizer1->Fit( this );
	this->Centre( wxBOTH );
	
}

