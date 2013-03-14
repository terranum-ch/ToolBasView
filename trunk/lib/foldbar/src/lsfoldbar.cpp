/***************************************************************************
 lsfoldbar.cpp
 -------------------
 copyright            : (C) 2013 CREALP Lucien Schreiber 
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

#include "lsfoldbar.h"

lsFoldBarCtrl::lsFoldBarCtrl(wxWindow * parent, wxWindowID id) : wxControl(parent, id) {
    wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_TitleBarPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_TitleBarPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_TitleText = new wxStaticText( m_TitleBarPanel, wxID_ANY, _("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	m_TitleText->Wrap( -1 );
	bSizer2->Add( m_TitleText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_TitleButtonCtrl = new wxBitmapButton( m_TitleBarPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer2->Add( m_TitleButtonCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_TitleBarPanel->SetSizer( bSizer2 );
	m_TitleBarPanel->Layout();
	bSizer2->Fit( m_TitleBarPanel );
	bSizer1->Add( m_TitleBarPanel, 0, wxEXPAND, 5 );
	
	m_ClientSizer = new wxBoxSizer( wxVERTICAL );
	
	/*wxTextCtrl* m_textCtrl1;
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_ClientSizer->Add( m_textCtrl1, 1, wxEXPAND, 5 );*/
	
	
	bSizer1->Add( m_ClientSizer, 1, wxEXPAND, 0 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}



lsFoldBarCtrl::~lsFoldBarCtrl() {
}



void lsFoldBarCtrl::SetTitle(const wxString & title) {
}



void lsFoldBarCtrl::ShowBar() {
}



void lsFoldBarCtrl::HideBar() {
}

