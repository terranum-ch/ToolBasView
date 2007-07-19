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




