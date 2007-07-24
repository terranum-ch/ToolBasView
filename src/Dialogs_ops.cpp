/*!
    @file dialogs_ops.cpp
    @brief definition of ressources dialogs operations
*/


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "Dialogs_ops.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "../include/Dialogs_ops.h"

//----------------------------------------------------------------------------
// SQLPROCESS_DLG_OP
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(SQLPROCESS_DLG_OP,wxDialog)
    EVT_BUTTON( wxID_CANCEL, SQLPROCESS_DLG_OP::OnCancel )
    EVT_BUTTON( ID_PROCESS, SQLPROCESS_DLG_OP::OnProcess )
END_EVENT_TABLE()


SQLPROCESS_DLG_OP::SQLPROCESS_DLG_OP( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    // WDR: dialog function SQLPROCESS for SQLPROCESS_DLG_OP
    SQLPROCESS( this, TRUE ); 
}

SQLPROCESS_DLG_OP::~SQLPROCESS_DLG_OP()
{

}

void SQLPROCESS_DLG_OP::SetDataBase(DataBase * pDatabase)
{
	m_DataBase = pDatabase;
}

// WDR: handler implementations for SQLPROCESS_DLG_OP

void SQLPROCESS_DLG_OP::OnProcess( wxCommandEvent &event )
{
	// get the text to process.
	wxString myRequest = ((wxTextCtrl*) FindWindow(ID_TEXTCTRL))->GetValue();
	
	if (!myRequest.IsEmpty()) 
	{
		wxLogMessage(_("Processing Request..."));
		if (m_DataBase->DataBaseQuery(myRequest)==0)
		{
			((wxStaticText *) FindWindow(ID_REQUEST_RESULT))->
				SetLabel(_("Results : OK Request passed."));
		}
		else 
		{
			((wxStaticText *) FindWindow(ID_REQUEST_RESULT))->
				SetLabel(_("Results : Request Failed."));
		}
	}
	
}

void SQLPROCESS_DLG_OP::OnCancel(wxCommandEvent &event)
{
	this->Destroy();
    event.Skip();
}


//----------------------------------------------------------------------------
// NEWDBASE_OP
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(NEWDBASE_OP,wxDialog)
    EVT_BUTTON( wxID_OK, NEWDBASE_OP::OnOk )
    EVT_BUTTON( wxID_CANCEL, NEWDBASE_OP::OnCancel )
	EVT_BUTTON( ID_BTN_CHOOSE_PATH, NEWDBASE_OP::OnDisplayDirectory)
END_EVENT_TABLE()

NEWDBASE_OP::NEWDBASE_OP( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    NEWDBASE( this, TRUE ); 
}

NEWDBASE_OP::~NEWDBASE_OP()
{
}

bool NEWDBASE_OP::TransferDataFromWindow()
{
    // function called automatically if user click ok...
	wxTextCtrl * myPathCtrl = (wxTextCtrl*) FindWindow(ID_TXT_DB_PATH);
	wxTextCtrl * myNameCtrl = (wxTextCtrl *) FindWindow(ID_TXT_DB_NAME);
	
	m_DLG_DB_PATH = myPathCtrl->GetValue();
	m_DLG_DB_NAME = myNameCtrl->GetValue();
	return TRUE;

}


void NEWDBASE_OP::OnOk(wxCommandEvent &event)
{
 	if (TransferDataFromWindow())
	{
		wxFileName myFileName (m_DLG_DB_PATH,wxEmptyString);
		if (myFileName.DirExists() && !m_DLG_DB_NAME.IsEmpty())
		{
			event.Skip();
		}
		else 
			wxMessageBox(_("Please fill the database Path and Name\n"
						   "N.B. The database path must exist"),
						 _("Error"),wxICON_ERROR | wxOK);
		
	}
}

void NEWDBASE_OP::OnCancel(wxCommandEvent &event)
{
    event.Skip();
}

void NEWDBASE_OP::OnDisplayDirectory (wxCommandEvent & event)
{
	const wxString dir = wxDirSelector(_("Select a path for the new database"));
	if (!dir.IsEmpty())
	{
		((wxTextCtrl*)FindWindow(ID_TXT_DB_PATH))->SetValue(dir);	
	}
	//wxLogMessage(dir);
}


