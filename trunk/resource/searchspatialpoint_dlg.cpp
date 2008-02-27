/////////////////////////////////////////////////////////////////////////////
// Name:        searchspatialpoint_dlg.cpp
// Purpose:     
// Author:      Lucien Schreiber
// Modified by: 
// Created:     Wed 27 Feb 17:08:27 2008
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

#include "searchspatialpoint_dlg.h"

////@begin XPM images
////@end XPM images


/*!
 * SEARCHSPATIALPOINT_DLG type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SEARCHSPATIALPOINT_DLG, wxDialog )


/*!
 * SEARCHSPATIALPOINT_DLG event table definition
 */

BEGIN_EVENT_TABLE( SEARCHSPATIALPOINT_DLG, wxDialog )

////@begin SEARCHSPATIALPOINT_DLG event table entries
////@end SEARCHSPATIALPOINT_DLG event table entries

END_EVENT_TABLE()


/*!
 * SEARCHSPATIALPOINT_DLG constructors
 */

SEARCHSPATIALPOINT_DLG::SEARCHSPATIALPOINT_DLG()
{
    Init();
}

SEARCHSPATIALPOINT_DLG::SEARCHSPATIALPOINT_DLG( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * searchspatialpoint_dlg creator
 */

bool SEARCHSPATIALPOINT_DLG::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin SEARCHSPATIALPOINT_DLG creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end SEARCHSPATIALPOINT_DLG creation
    return true;
}


/*!
 * SEARCHSPATIALPOINT_DLG destructor
 */

SEARCHSPATIALPOINT_DLG::~SEARCHSPATIALPOINT_DLG()
{
////@begin SEARCHSPATIALPOINT_DLG destruction
////@end SEARCHSPATIALPOINT_DLG destruction
}


/*!
 * Member initialisation
 */

void SEARCHSPATIALPOINT_DLG::Init()
{
////@begin SEARCHSPATIALPOINT_DLG member initialisation
    m_DLGSS_Map_Xmin = NULL;
    m_DLGSS_Map_Xmax = NULL;
    m_DLGSS_Map_Ymin = NULL;
    m_DLGSS_Map_Ymax = NULL;
    m_DLGSS_coord_x = NULL;
    m_DLGSS_coord_x = NULL;
    m_DLGSS_buffer = NULL;
    m_DLGSS_result_index = NULL;
    m_DLGSS_result_index_tm = NULL;
    m_DLGSS_result_status = NULL;
    m_DLGSS_result_status_tm = NULL;
////@end SEARCHSPATIALPOINT_DLG member initialisation
}


/*!
 * Control creation for searchspatialpoint_dlg
 */

void SEARCHSPATIALPOINT_DLG::CreateControls()
{    
////@begin SEARCHSPATIALPOINT_DLG content construction
    SEARCHSPATIALPOINT_DLG* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Map properties"));
    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer4, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer5 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer5->AddGrowableCol(1);
    itemStaticBoxSizer4->Add(itemFlexGridSizer5, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("X min :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_Map_Xmin = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxSize(120, -1), wxALIGN_RIGHT );
    itemFlexGridSizer5->Add(m_DLGSS_Map_Xmin, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("X max :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_Map_Xmax = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemFlexGridSizer5->Add(m_DLGSS_Map_Xmax, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine10 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemStaticBoxSizer4->Add(itemStaticLine10, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxFlexGridSizer* itemFlexGridSizer11 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer11->AddGrowableCol(1);
    itemStaticBoxSizer4->Add(itemFlexGridSizer11, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("Y min :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_Map_Ymin = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemFlexGridSizer11->Add(m_DLGSS_Map_Ymin, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText14 = new wxStaticText( itemDialog1, wxID_STATIC, _("Y max :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(itemStaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_Map_Ymax = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemFlexGridSizer11->Add(m_DLGSS_Map_Ymax, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer16Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Static"));
    wxStaticBoxSizer* itemStaticBoxSizer16 = new wxStaticBoxSizer(itemStaticBoxSizer16Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer16, 1, wxALIGN_TOP|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer17 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer17->AddGrowableCol(1);
    itemStaticBoxSizer16->Add(itemFlexGridSizer17, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText18 = new wxStaticText( itemDialog1, wxID_STATIC, _("x :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(itemStaticText18, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_coord_x = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(m_DLGSS_coord_x, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( itemDialog1, wxID_STATIC, _("y :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(itemStaticText20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_coord_x = new wxTextCtrl( itemDialog1, ID_TEXTCTRL2, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(m_DLGSS_coord_x, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer16->Add(itemBoxSizer22, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText23 = new wxStaticText( itemDialog1, wxID_STATIC, _("Buffer size [m] :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer22->Add(itemStaticText23, 0, wxALIGN_TOP|wxALL, 5);

    m_DLGSS_buffer = new wxSlider( itemDialog1, ID_SLIDER1, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_AUTOTICKS|wxSL_LABELS );
    itemBoxSizer22->Add(m_DLGSS_buffer, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer25Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Results :"));
    wxStaticBoxSizer* itemStaticBoxSizer25 = new wxStaticBoxSizer(itemStaticBoxSizer25Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer25, 0, wxGROW|wxLEFT|wxRIGHT, 10);

    wxFlexGridSizer* itemFlexGridSizer26 = new wxFlexGridSizer(2, 3, 0, 0);
    itemFlexGridSizer26->AddGrowableCol(1);
    itemStaticBoxSizer25->Add(itemFlexGridSizer26, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText27 = new wxStaticText( itemDialog1, wxID_STATIC, _("Number of lines fetched from spatial index :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer26->Add(itemStaticText27, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_result_index = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer26->Add(m_DLGSS_result_index, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_result_index_tm = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxSize(50, -1), 0 );
    itemFlexGridSizer26->Add(m_DLGSS_result_index_tm, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText30 = new wxStaticText( itemDialog1, wxID_STATIC, _("Status :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer26->Add(itemStaticText30, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_result_status = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer26->Add(m_DLGSS_result_status, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_result_status_tm = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer26->Add(m_DLGSS_result_status_tm, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer2->Add(5, 5, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticLine* itemStaticLine34 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine34, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer35 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer35, 0, wxALIGN_RIGHT|wxALL, 5);

    wxButton* itemButton36 = new wxButton( itemDialog1, wxID_FIND, _("&Find"), wxDefaultPosition, wxSize(150, -1), 0 );
    itemBoxSizer35->Add(itemButton36, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton37 = new wxButton( itemDialog1, wxID_CLOSE, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton37->SetDefault();
    itemBoxSizer35->Add(itemButton37, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end SEARCHSPATIALPOINT_DLG content construction
}


/*!
 * Should we show tooltips?
 */

bool SEARCHSPATIALPOINT_DLG::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap SEARCHSPATIALPOINT_DLG::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin SEARCHSPATIALPOINT_DLG bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end SEARCHSPATIALPOINT_DLG bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon SEARCHSPATIALPOINT_DLG::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin SEARCHSPATIALPOINT_DLG icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end SEARCHSPATIALPOINT_DLG icon retrieval
}
