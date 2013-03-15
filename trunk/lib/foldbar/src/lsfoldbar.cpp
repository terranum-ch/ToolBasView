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
#include "foldbar_bmp.h"

lsFoldBarCtrl::lsFoldBarCtrl(wxWindow * parent, wxWindowID id) : wxControl(parent, id) {
    m_ParentSizerItem = NULL;
    foldbar_initialize_images();
    
    wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_TitleBarPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_TitleBarPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE ));
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_TitleText = new wxStaticText( m_TitleBarPanel, wxID_ANY, _T("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	m_TitleText->Wrap( -1 );
    //m_TitleText->SetFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
	bSizer2->Add( m_TitleText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_TitleButtonCtrl = new wxBitmapButton( m_TitleBarPanel, wxID_ANY, *_img_plus, wxDefaultPosition, wxSize(20,20), wxBU_AUTODRAW | wxBU_EXACTFIT | wxBU_NOTEXT );
	bSizer2->Add( m_TitleButtonCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_TitleBarPanel->SetSizer( bSizer2 );
	m_TitleBarPanel->Layout();
	bSizer2->Fit( m_TitleBarPanel );
	bSizer1->Add( m_TitleBarPanel, 0, wxEXPAND, 5 );
	
    
   wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND, 5 );

    
	m_ClientSizer = new wxBoxSizer( wxVERTICAL );
	bSizer1->Add( m_ClientSizer, 1, wxEXPAND, 0 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
    
    // connect event
    this->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &lsFoldBarCtrl::OnButtonClick, this, wxID_ANY);
}



lsFoldBarCtrl::~lsFoldBarCtrl() {
    // disconnect event
    this->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &lsFoldBarCtrl::OnButtonClick, this, wxID_ANY);
    foldbar_clean_images();
}



void lsFoldBarCtrl::OnButtonClick(wxCommandEvent & event){
    if (IsBarShown()== true) {
        HideBar();
        return;
    }
    ShowBar();
}

bool lsFoldBarCtrl::IsBarShown(){
    return GetSizer()->IsShown(m_ClientSizer);
}

void lsFoldBarCtrl::SetTitle(const wxString & title) {
    m_TitleText->SetLabel(title);
}


void lsFoldBarCtrl::SetTitleBackground (const wxColour & colour){
    if (colour == *wxBLACK) {
        m_TitleText->SetForegroundColour(*wxWHITE);
    }
    else{
        m_TitleText->SetForegroundColour(*wxBLACK);
    }
    
    m_TitleBarPanel->SetBackgroundColour(colour);
}



void lsFoldBarCtrl::ShowBar() {
    if (m_ParentSizerItem != NULL) {
        m_ParentSizerItem->SetProportion(1);
    }
    m_TitleButtonCtrl->SetBitmap(*_img_minus);
    this->GetSizer()->Show(m_ClientSizer);
    this->Layout();
    GetParent()->PostSizeEvent();
}



void lsFoldBarCtrl::HideBar() {
    if (m_ParentSizerItem != NULL) {
        m_ParentSizerItem->SetProportion(0);
    }
    m_TitleButtonCtrl->SetBitmap(*_img_plus);
    this->GetSizer()->Hide(m_ClientSizer);
    this->Layout();
    GetParent()->PostSizeEvent();
}

