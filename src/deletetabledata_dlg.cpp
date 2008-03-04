/***************************************************************************
 deletetabledata_dlg.cpp
 dialog for deleting data from database 
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


#include "../include/deletetabledata_dlg.h"



IMPLEMENT_DYNAMIC_CLASS( DELETETABLEDATA_DLG, wxDialog )

BEGIN_EVENT_TABLE( DELETETABLEDATA_DLG, wxDialog )
	EVT_BUTTON(wxID_OK, DELETETABLEDATA_DLG::OnPressOK)
END_EVENT_TABLE()


DELETETABLEDATA_DLG::DELETETABLEDATA_DLG()
{
    Init();
}

DELETETABLEDATA_DLG::DELETETABLEDATA_DLG( wxWindow* parent, wxWindowID id,
										 DataBase * database,
										 const wxString& caption, const wxPoint& pos, 
										 const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
	m_pDatabase = database;
	
	// init the table if database not empty
	if (m_pDatabase != NULL && m_pDatabase->DataBaseIsOpen())
	{
		// get list of tables
		m_DlgDel_ListTables->Append(m_pDatabase->DataBaseListTables());
	}
	
}


bool DELETETABLEDATA_DLG::Create( wxWindow* parent, wxWindowID id, 
								 const wxString& caption, 
								 const wxPoint& pos, const wxSize& size, long style )
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



DELETETABLEDATA_DLG::~DELETETABLEDATA_DLG()
{
}


void DELETETABLEDATA_DLG::Init()
{
    m_DlgDel_Chk_Data = NULL;
    m_DlgDel_Chk_table = NULL;
    m_DlgDel_Chk_Vacuum = NULL;
	m_pDatabase = NULL;
	m_DlgDel_ListTables = NULL;
	m_DlgFlags = DEL_FLAGS_ALL;
}



bool DELETETABLEDATA_DLG::TransferDataToWindow()
{
	if((m_DlgFlags & DEL_FLAGS_DATA) != DEL_FLAGS_DATA)
	{
		m_DlgDel_Chk_Data->SetValue(FALSE);
		m_DlgDel_Chk_Data->Enable(FALSE);
	}
	
	if((m_DlgFlags & DEL_FLAGS_TABLE) != DEL_FLAGS_TABLE)
	{
		m_DlgDel_Chk_table->SetValue(FALSE);
		m_DlgDel_Chk_table->Enable(FALSE);
	}
	
	if((m_DlgFlags & DEL_FLAGS_VACUUM) != DEL_FLAGS_VACUUM)
	{
		m_DlgDel_Chk_Vacuum->SetValue(FALSE);
		m_DlgDel_Chk_Vacuum->Enable(FALSE);
	}
	
	return TRUE;
}

bool DELETETABLEDATA_DLG::TransferDataFromWindow()
{
	// put selected operations into the flags object
	m_DlgFlags = 0;
	
	if (m_DlgDel_Chk_Data->IsChecked())
	{
		m_DlgFlags = m_DlgFlags | DEL_FLAGS_DATA;
	}
	
	if (m_DlgDel_Chk_table->IsChecked())
	{
		m_DlgFlags = m_DlgFlags | DEL_FLAGS_TABLE;
	}
	
	if (m_DlgDel_Chk_Vacuum->IsChecked())
	{
		m_DlgFlags = m_DlgFlags | DEL_FLAGS_VACUUM;
	}
	
	
	// get selected tables 
	wxArrayInt mySelectedItems;
	m_DlgDel_ListTables->GetSelections(mySelectedItems);
	
	for (unsigned int i = 0; i<mySelectedItems.GetCount(); i++)
	{
		m_SelectedTables.Add(m_DlgDel_ListTables->GetString(mySelectedItems.Item(i)));
	}

	
	return TRUE;	
}


void DELETETABLEDATA_DLG::OnPressOK (wxCommandEvent & event)
{
	wxString sSentence = _T("");
	
	for (unsigned int i = 0; i<m_DlgDel_ListTables->GetCount(); i++)
	{
		if (m_DlgDel_ListTables->IsChecked(i))
			m_SelectedTables.Add(m_DlgDel_ListTables->GetString(i));
	}
	
	// loop for each tables
	for (unsigned j = 0; j < m_SelectedTables.GetCount(); j++)
	{
		// do we have to delete the data
		if (m_DlgDel_Chk_Data->IsChecked())
		{
			sSentence.Append(wxString::Format(_T("DELETE FROM %s; "), 
											  (m_SelectedTables.Item(j)).c_str()));
		}
		
		// do we have to drop the tables
		if (m_DlgDel_Chk_table->IsChecked())
		{
			sSentence.Append(wxString::Format(_T("DROP TABLE %s; "),
											  (m_SelectedTables.Item(j)).c_str()));
			
		}
	}
	
	
	sSentence.Append(_T(""));
	
	// do we have to vacum (vacuum is global and no in transaction)
	if (m_DlgDel_Chk_Vacuum->IsChecked())
	{
		sSentence.Append(_T("VACUUM; "));
	}
	
	// finaly process the request
	if (m_pDatabase->DataBaseQueryMultiple(sSentence) != 0)
	{
		wxLogDebug(_T("Error processing delete query..."));
		
	}
	wxLogDebug(sSentence);
	
	Close();
}



void DELETETABLEDATA_DLG::CreateControls()
{    
    DELETETABLEDATA_DLG* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Tables in database"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 1, wxGROW|wxALL, 5);

    wxArrayString itemCheckListBox4Strings;
    m_DlgDel_ListTables = new wxCheckListBox( itemDialog1, ID_DLGDEL_TABLES, wxDefaultPosition, wxSize(250, 200), itemCheckListBox4Strings, wxLB_SINGLE );
    itemStaticBoxSizer3->Add(m_DlgDel_ListTables, 1, wxGROW, 5);

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

}

