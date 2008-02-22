/***************************************************************************
 addspatialdata_dlg
 Functions for adding spatial data into a database
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

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif



#include "../include/addspatialdata_dlg.h"


IMPLEMENT_DYNAMIC_CLASS( ADDSPATIALDATA_DLG, wxDialog )



BEGIN_EVENT_TABLE( ADDSPATIALDATA_DLG, wxDialog )

////@begin ADDSPATIALDATA_DLG event table entries
////@end ADDSPATIALDATA_DLG event table entries

END_EVENT_TABLE()



ADDSPATIALDATA_DLG::ADDSPATIALDATA_DLG()
{
    Init();
}



ADDSPATIALDATA_DLG::ADDSPATIALDATA_DLG( wxWindow* parent,   DataBase * pDatabase,
									   wxWindowID id, const wxString& caption, 
									   const wxPoint& pos, const wxSize& size, long style )
{
    Init();
	SetDataBase(pDatabase);
	Create(parent, pDatabase, id, caption, pos, size, style);
	
	// add list of tables into the wxChoice
	AddListOfTable();
	
}




bool ADDSPATIALDATA_DLG::Create( wxWindow* parent,   DataBase * pDatabase,
								wxWindowID id, const wxString& caption, const wxPoint& pos, 
								const wxSize& size, long style )
{
	SetDataBase(pDatabase);
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



ADDSPATIALDATA_DLG::~ADDSPATIALDATA_DLG()
{

}




void ADDSPATIALDATA_DLG::Init()
{
    m_DLGAS_FileSelector = NULL;
    m_DLGAS_ListTables = NULL;
	m_pDatabase = NULL;
}



bool ADDSPATIALDATA_DLG::AddListOfTable ()
{
	wxArrayString myListTables;
	
	wxASSERT (m_pDatabase != NULL);
	if (m_pDatabase != NULL)
	{
		// get list of tables from database
		myListTables = m_pDatabase->DataBaseListTables();
		
		// put the list in the wxChoice
		m_DLGAS_ListTables->Append(myListTables);
		
		// select the first item
		m_DLGAS_ListTables->SetSelection(0);
		return TRUE;
	}
	return FALSE;
}





/*!
 * Control creation for ADDSPATIALDATA_DLG
 */

void ADDSPATIALDATA_DLG::CreateControls()
{    
	ADDSPATIALDATA_DLG* itemDialog1 = this;
	
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);
	
    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(1);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxGROW|wxALL, 5);
	
    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Spatial data source :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	m_DLGAS_FileSelector = new wxFilePickerCtrl(itemDialog1, ID_FILESELECTOR, wxEmptyString,
												_("Select a shapefile"), 
												_("ESRI's shapefile (*.shp)|*.shp"), wxDefaultPosition,
												wxDefaultSize);
   itemFlexGridSizer3->Add(m_DLGAS_FileSelector, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Destination table :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
    wxArrayString m_DLGAS_ListTablesStrings;
    m_DLGAS_ListTables = new wxChoice( itemDialog1, ID_LISTTABLES, wxDefaultPosition, wxSize(400,-1), m_DLGAS_ListTablesStrings, 0 );
    itemFlexGridSizer3->Add(m_DLGAS_ListTables, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
    itemBoxSizer2->Add(5, 5, 1, wxGROW|wxALL, 5);
	
    wxStaticLine* itemStaticLine9 = new wxStaticLine( itemDialog1, ID_STATICLINE, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine9, 0, wxGROW|wxALL, 5);
	
    wxStdDialogButtonSizer* itemStdDialogButtonSizer10 = new wxStdDialogButtonSizer;
	
    itemBoxSizer2->Add(itemStdDialogButtonSizer10, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton11->SetDefault();
    itemStdDialogButtonSizer10->AddButton(itemButton11);
	
    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer10->AddButton(itemButton12);
	
    itemStdDialogButtonSizer10->Realize();

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
