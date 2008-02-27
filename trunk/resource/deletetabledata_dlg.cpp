/////////////////////////////////////////////////////////////////////////////
// Name:        deletetabledata_dlg.cpp
// Purpose:     
// Author:      Lucien Schreiber
// Modified by: 
// Created:     Tue 26 Feb 18:07:40 2008
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

#include "deletetabledata_dlg.h"

////@begin XPM images
////@end XPM images


/*!
 * DELETETABLEDATA_DLG type definition
 */

IMPLEMENT_DYNAMIC_CLASS( DELETETABLEDATA_DLG, wxDialog )


/*!
 * DELETETABLEDATA_DLG event table definition
 */

BEGIN_EVENT_TABLE( DELETETABLEDATA_DLG, wxDialog )

////@begin DELETETABLEDATA_DLG event table entries
////@end DELETETABLEDATA_DLG event table entries

END_EVENT_TABLE()


/*!
 * DELETETABLEDATA_DLG constructors
 */

DELETETABLEDATA_DLG::DELETETABLEDATA_DLG()
{
    Init();
}

DELETETABLEDATA_DLG::DELETETABLEDATA_DLG( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * deletetabledata_dlg creator
 */

bool DELETETABLEDATA_DLG::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin DELETETABLEDATA_DLG creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end DELETETABLEDATA_DLG creation
    return true;
}


/*!
 * DELETETABLEDATA_DLG destructor
 */

DELETETABLEDATA_DLG::~DELETETABLEDATA_DLG()
{
////@begin DELETETABLEDATA_DLG destruction
////@end DELETETABLEDATA_DLG destruction
}


/*!
 * Member initialisation
 */

void DELETETABLEDATA_DLG::Init()
{
////@begin DELETETABLEDATA_DLG member initialisation
    m_DlgDel_Chk_Data = NULL;
    m_DlgDel_Chk_table = NULL;
    m_DlgDel_Chk_Vacuum = NULL;
////@end DELETETABLEDATA_DLG member initialisation
}


/*!
 * Control creation for deletetabledata_dlg
 */

void DELETETABLEDATA_DLG::CreateControls()
{    
////@begin DELETETABLEDATA_DLG content construction
    DELETETABLEDATA_DLG* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Tables in database"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 1, wxGROW|wxALL, 5);

    wxArrayString itemCheckListBox4Strings;
    wxCheckListBox* itemCheckListBox4 = new wxCheckListBox( itemDialog1, ID_DLGDEL_TABLES, wxDefaultPosition, wxSize(250, 200), itemCheckListBox4Strings, wxLB_SINGLE );
    itemStaticBoxSizer3->Add(itemCheckListBox4, 1, wxGROW, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer5, 0, wxGROW|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer6Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Operations"));
    wxStaticBoxSizer* itemStaticBoxSizer6 = new wxStaticBoxSizer(itemStaticBoxSizer6Static, wxVERTICAL);
    itemBoxSizer5->Add(itemStaticBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_DlgDel_Chk_Data = new wxCheckBox( itemDialog1, ID_DLGDEL_CHK_DATA, _("Deleting data"), wxDefaultPosition, wxDefaultSize, 0 );
    m_DlgDel_Chk_Data->SetValue(true);
    itemStaticBoxSizer6->Add(m_DlgDel_Chk_Data, 0, wxALIGN_LEFT|wxALL, 5);

    m_DlgDel_Chk_table = new wxCheckBox( itemDialog1, ID_DLGDEL_CHK_TABLE, _("Deleting table"), wxDefaultPosition, wxDefaultSize, 0 );
    m_DlgDel_Chk_table->SetValue(false);
    itemStaticBoxSizer6->Add(m_DlgDel_Chk_table, 0, wxALIGN_LEFT|wxALL, 5);

    m_DlgDel_Chk_Vacuum = new wxCheckBox( itemDialog1, ID_DLGDEL_VACUUM, _("Cleaning dataspace (VACUUM)"), wxDefaultPosition, wxDefaultSize, 0 );
    m_DlgDel_Chk_Vacuum->SetValue(false);
    itemStaticBoxSizer6->Add(m_DlgDel_Chk_Vacuum, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer5->Add(5, 5, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticLine* itemStaticLine11 = new wxStaticLine( itemDialog1, ID_STATICLINE2, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer5->Add(itemStaticLine11, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer12 = new wxStdDialogButtonSizer;

    itemBoxSizer5->Add(itemStdDialogButtonSizer12, 0, wxGROW|wxALL, 5);
    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer12->AddButton(itemButton13);

    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton14->SetDefault();
    itemStdDialogButtonSizer12->AddButton(itemButton14);

    itemStdDialogButtonSizer12->Realize();

////@end DELETETABLEDATA_DLG content construction
}


/*!
 * Should we show tooltips?
 */

bool DELETETABLEDATA_DLG::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap DELETETABLEDATA_DLG::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin DELETETABLEDATA_DLG bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end DELETETABLEDATA_DLG bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon DELETETABLEDATA_DLG::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin DELETETABLEDATA_DLG icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end DELETETABLEDATA_DLG icon retrieval
}
