/////////////////////////////////////////////////////////////////////////////
// Name:        addspatialdata_dlg.cpp
// Purpose:     
// Author:      Lucien Schreiber
// Modified by: 
// Created:     Thu 21 Feb 16:41:20 2008
// RCS-ID:      
// Copyright:   (c) 2007 CREALP
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "addspatialdata_dlg.h"

////@begin XPM images
////@end XPM images


/*!
 * ADDSPATIALDATA_DLG type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ADDSPATIALDATA_DLG, wxDialog )


/*!
 * ADDSPATIALDATA_DLG event table definition
 */

BEGIN_EVENT_TABLE( ADDSPATIALDATA_DLG, wxDialog )

////@begin ADDSPATIALDATA_DLG event table entries
////@end ADDSPATIALDATA_DLG event table entries

END_EVENT_TABLE()


/*!
 * ADDSPATIALDATA_DLG constructors
 */

ADDSPATIALDATA_DLG::ADDSPATIALDATA_DLG()
{
    Init();
}

ADDSPATIALDATA_DLG::ADDSPATIALDATA_DLG( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * ADDSPATIALDATA_DLG creator
 */

bool ADDSPATIALDATA_DLG::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin ADDSPATIALDATA_DLG creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end ADDSPATIALDATA_DLG creation
    return true;
}


/*!
 * ADDSPATIALDATA_DLG destructor
 */

ADDSPATIALDATA_DLG::~ADDSPATIALDATA_DLG()
{
////@begin ADDSPATIALDATA_DLG destruction
////@end ADDSPATIALDATA_DLG destruction
}


/*!
 * Member initialisation
 */

void ADDSPATIALDATA_DLG::Init()
{
////@begin ADDSPATIALDATA_DLG member initialisation
    m_DLGAS_FileSelector = NULL;
    m_DLGAS_ListTables = NULL;
    m_DLGAS_Chk_Index = NULL;
////@end ADDSPATIALDATA_DLG member initialisation
}


/*!
 * Control creation for ADDSPATIALDATA_DLG
 */

void ADDSPATIALDATA_DLG::CreateControls()
{    
////@begin ADDSPATIALDATA_DLG content construction
    ADDSPATIALDATA_DLG* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(1);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Spatial data source :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGAS_FileSelector = new wxTextCtrl( itemDialog1, ID_FILESELECTOR, _T(""), wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer3->Add(m_DLGAS_FileSelector, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Destination table :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString m_DLGAS_ListTablesStrings;
    m_DLGAS_ListTables = new wxChoice( itemDialog1, ID_LISTTABLES, wxDefaultPosition, wxDefaultSize, m_DLGAS_ListTablesStrings, 0 );
    itemFlexGridSizer3->Add(m_DLGAS_ListTables, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer2->Add(5, 5, 1, wxGROW|wxALL, 5);

    m_DLGAS_Chk_Index = new wxCheckBox( itemDialog1, ID_CHECKBOX, _("Compute spatial index"), wxDefaultPosition, wxDefaultSize, 0 );
    m_DLGAS_Chk_Index->SetValue(true);
    itemBoxSizer2->Add(m_DLGAS_Chk_Index, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine10 = new wxStaticLine( itemDialog1, ID_STATICLINE, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine10, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer11 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer11, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton12->SetDefault();
    itemStdDialogButtonSizer11->AddButton(itemButton12);

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer11->AddButton(itemButton13);

    itemStdDialogButtonSizer11->Realize();

////@end ADDSPATIALDATA_DLG content construction
}


/*!
 * Should we show tooltips?
 */

bool ADDSPATIALDATA_DLG::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap ADDSPATIALDATA_DLG::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin ADDSPATIALDATA_DLG bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end ADDSPATIALDATA_DLG bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon ADDSPATIALDATA_DLG::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin ADDSPATIALDATA_DLG icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end ADDSPATIALDATA_DLG icon retrieval
}
