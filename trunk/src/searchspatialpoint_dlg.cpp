/***************************************************************************
 searchspatialpoint.cpp
 Dialog functions for searching spatial data. Mainly used for benchmarks 
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "../include/searchspatialpoint_dlg.h"

IMPLEMENT_DYNAMIC_CLASS( SEARCHSPATIALPOINT_DLG, wxDialog )


BEGIN_EVENT_TABLE( SEARCHSPATIALPOINT_DLG, wxDialog )
	EVT_BUTTON (wxID_CLOSE, SEARCHSPATIALPOINT_DLG::OnButtonClose)
	EVT_IDLE (SEARCHSPATIALPOINT_DLG::OnIdleActivateButton)
	EVT_BUTTON (wxID_FIND, SEARCHSPATIALPOINT_DLG::OnButtonFind) 
END_EVENT_TABLE()


/***************************** EVENT FUNCTIONS ***************************/
void SEARCHSPATIALPOINT_DLG::OnButtonClose(wxCommandEvent & event)
{
	// Quit the dialog...
	Close();
	
}


void SEARCHSPATIALPOINT_DLG::OnIdleActivateButton (wxIdleEvent & event)
{
	// enable button if controls are filled
	m_DLGSS_FindButton->Enable(IsControlFilled());
}


void SEARCHSPATIALPOINT_DLG::OnButtonFind (wxCommandEvent & event)
{
	// get value from control
	m_xvalue = m_DLGSS_coord_x->GetValue();
	m_yvalue = m_DLGSS_coord_y->GetValue();
	double dx = 0, dy = 0;
	m_xvalue.ToDouble(&dx);
	m_yvalue.ToDouble(&dy);
	
	// get buffer value
	int iBuffer = m_DLGSS_buffer->GetValue();
	
	// extract lines
	int iFidFoundLine = 0;
	wxString sStatusString = _("NOT FOUND");
	
	wxStopWatch sw;
	
	if(m_GISDB.GISGetFeatureByBuffer(dx, dy, iBuffer, iFidFoundLine) != NULL)
		sStatusString = wxString::Format(_("FOUND, Line ID is %d"), iFidFoundLine);
	
	sw.Pause();
	
	m_DLGSS_result_status->SetLabel(_("Line is : ") + sStatusString);
	m_DLGSS_result_status_tm->SetLabel(wxString::Format(_T("%d [ms]"), sw.Time()));
	
}




/***************************** PRIVATE FUNCTIONS ***************************/
bool SEARCHSPATIALPOINT_DLG::IsControlFilled ()
{
	if (!m_DLGSS_coord_x->IsEmpty() && !m_DLGSS_coord_y->IsEmpty())
		return TRUE;
	
	return FALSE;
}





/*****************************  FUNCTIONS ***************************/
SEARCHSPATIALPOINT_DLG::SEARCHSPATIALPOINT_DLG()
{
    Init();
}


SEARCHSPATIALPOINT_DLG::SEARCHSPATIALPOINT_DLG( wxWindow* parent, DataBase * database,
											   wxWindowID id, const wxString& caption,
											   const wxPoint& pos, const wxSize& size, long style )
{
    Init();
	
	m_pDatabase = database;
    Create(parent, id, caption, pos, size, style);
}




bool SEARCHSPATIALPOINT_DLG::Create( wxWindow* parent, wxWindowID id, 
									const wxString& caption, const wxPoint& pos, 
									const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}




SEARCHSPATIALPOINT_DLG::~SEARCHSPATIALPOINT_DLG()
{
	if (m_GISDB.GISIsOpened())
		m_GISDB.GISClose();
}

void SEARCHSPATIALPOINT_DLG::Init()
{
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
	
	m_pDatabase = NULL;
		m_DLGSS_FindButton = NULL;
	
	m_xvalue = _T("");
	m_yvalue = _T("");
}


bool SEARCHSPATIALPOINT_DLG::OpenDBGISData (const wxString & dbname, const wxString & table)
{
	// store the OGRenveloppe, must be deleted after use
	// but only if not null
	OGREnvelope * myDBEnveloppe;
	
	// return true if opening database and setting table works
	if (m_GISDB.GISOpen(dbname))
	{
			if (m_GISDB.GISSetLayer(table))
			{
				m_GISDB.GISSetActiveDatabase(m_pDatabase);
				
				// get the extend
				wxStopWatch sw;
				myDBEnveloppe = m_GISDB.GISGetExtend();
				
				sw.Pause();
				
				
				if (myDBEnveloppe != NULL)
				{
					wxLogMessage(_T("Time for computing extend is : %d [ms]"), sw.Time());
					
					sw.Start();
					int iNbFeature = m_GISDB.GISGetFeatureCount();
					wxLogMessage(_T("Time for computing nb of features : %d [ms]"), sw.Time());
					
					// put the extend in the dialog
					m_DLGSS_Map_Xmin->SetLabel(wxString::Format(_T("%.*f"), 4,myDBEnveloppe->MinX));
					m_DLGSS_Map_Xmax->SetLabel(wxString::Format(_T("%.*f"), 4,myDBEnveloppe->MaxX));
					m_DLGSS_Map_Ymin->SetLabel(wxString::Format(_T("%.*f"), 4,myDBEnveloppe->MinY));
					m_DLGSS_Map_Ymax->SetLabel(wxString::Format(_T("%.*f"), 4,myDBEnveloppe->MaxY));
					
					
					
					delete myDBEnveloppe;
				}
				return TRUE;
			}
		
	}
	wxLogDebug(_T("Error opening the Database"));
	return FALSE;
}






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

    m_DLGSS_coord_x = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxDefaultSize, 0,
									  wxTextValidator(wxFILTER_NUMERIC, &m_xvalue));
    itemFlexGridSizer17->Add(m_DLGSS_coord_x, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( itemDialog1, wxID_STATIC, _("y :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(itemStaticText20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DLGSS_coord_y = new wxTextCtrl( itemDialog1, ID_TEXTCTRL2, _T(""), wxDefaultPosition, wxDefaultSize, 0,
									 wxTextValidator(wxFILTER_NUMERIC, &m_yvalue));
    itemFlexGridSizer17->Add(m_DLGSS_coord_y, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

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

    m_DLGSS_FindButton = new wxButton( itemDialog1, wxID_FIND, _("&Find"), wxDefaultPosition, wxSize(150, -1), 0 );
    itemBoxSizer35->Add(m_DLGSS_FindButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton37 = new wxButton( itemDialog1, wxID_CLOSE, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton37->SetDefault();
    itemBoxSizer35->Add(itemButton37, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

}

