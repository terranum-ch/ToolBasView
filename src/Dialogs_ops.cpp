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
    EVT_BUTTON( wxID_CANCEL, SQLPROCESS_DLG_OP::OnCancel)
    EVT_BUTTON( ID_PROCESS, SQLPROCESS_DLG_OP::OnProcess)
	EVT_BUTTON(ID_BTN_SHOWRESULTS, SQLPROCESS_DLG_OP::OnShowResult)
END_EVENT_TABLE()


SQLPROCESS_DLG_OP::SQLPROCESS_DLG_OP( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    // WDR: dialog function SQLPROCESS for SQLPROCESS_DLG_OP
    SQLPROCESS( this, TRUE ); 
	m_hasRequest = FALSE;
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
	wxArrayString myRequestArray; // contain multiple request if needed
	wxString myComment;
	wxArrayInt myErrorsArray;
	wxString myTempRequest;
	
	// get the text to process.
	wxString myRequest = ((wxTextCtrl*) FindWindow(ID_TEXTCTRL))->GetValue();
	
	if (!myRequest.IsEmpty()) 
	{
		// busy cursor
		wxBeginBusyCursor();
		
		myRequestArray = m_DataBase->DataBaseCutRequest(myRequest);
		
		wxLogMessage(_("Processing Request... %d Request Found"),myRequestArray.Count());
			
		// check the number of Request for passing to multiple or single query
		// needed if we wont the results back
		
		// SINGLE REQUEST
		if (myRequestArray.Count() == 1) 
		{
			if (m_DataBase->DataBaseQuery(myRequestArray.Item(0))==0) 
			{
				// the button show result is valid now...
				(wxButton*)FindWindow(ID_BTN_SHOWRESULTS)->Enable(TRUE);
				
				myComment = wxString(_("Result : One request passed OK"));
			}
			else {
				myComment = wxString(_("Result : Request Error, please check syntax"));
			}

			
			
		}
		
		// MULTIPLE REQUEST
		else
		{
			for (int i=0; i< myRequestArray.Count(); i++) 
			{
				myTempRequest = myRequestArray.Item(i);
				if (myTempRequest.IsEmpty())
					break;
				if (m_DataBase->DataBaseQueryMultiple(myTempRequest)!=0)
				{
					myErrorsArray.Add(i+1);
				}
				else
				{
					m_hasRequest = TRUE;
				}
			}
			
			// if errors found
			if (myErrorsArray.Count() > 0) 
			{
				myComment.Printf(_("Results : Request failed on request n : "));
				for (int j=0; j < myErrorsArray.Count(); j++) 
				{
					myComment.Append(wxString::Format(_T("%d, "),myErrorsArray.Item(j)));
				}
			}
			// no errors found
			else 
			{
				myComment.Printf(_("Results : %d request passed OK"),myRequestArray.Count());
				m_hasRequest = TRUE;
			}
		}

		// display results
		((wxStaticText *) FindWindow(ID_REQUEST_RESULT))->SetLabel(myComment);	

		// end busy...
		wxEndBusyCursor();
	}
	
}

void SQLPROCESS_DLG_OP::OnShowResult (wxCommandEvent & event)
{
		
	// new dialog 
	SHOWRESULT_OP * myDlg = new SHOWRESULT_OP(this,
											  -1, _("SQL Results"),
											  wxDefaultPosition,wxSize(500,500),
											  wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
	
	
	// transfert data to the window
	myDlg->TransferDataToWindow(m_DataBase);
	
	// gray the button
	(wxButton*)FindWindow(ID_BTN_SHOWRESULTS)->Enable(FALSE);
	
	
	// show the window
	myDlg->SetExtraStyle(wxDIALOG_EX_METAL);
	myDlg->SetMinSize(wxSize(300,300));
	myDlg->SetSize(wxSize(500,400));
	myDlg->Show(TRUE);
	
}


void SQLPROCESS_DLG_OP::OnCancel(wxCommandEvent &event)
{
	if (m_hasRequest) 
	{
		SetReturnCode(ID_PROCESS);
	}
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
			wxMessageBox(_("Please fill the database Path and Name\nN.B. The database path must exist"),
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
}



//----------------------------------------------------------------------------
// ABOUTDLG_OP
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ABOUTDLG_OP,wxDialog)
    EVT_BUTTON( wxID_OK, ABOUTDLG_OP::OnOk )
END_EVENT_TABLE()

ABOUTDLG_OP::ABOUTDLG_OP( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    ABOUT( this, TRUE );
	
}

ABOUTDLG_OP::~ABOUTDLG_OP()
{
}



void ABOUTDLG_OP::OnOk(wxCommandEvent &event)
{
	Destroy();
	event.Skip();
}


//----------------------------------------------------------------------------
// SHOWRESULT_OP
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(SHOWRESULT_OP,wxDialog)
    EVT_BUTTON( wxID_CANCEL, SHOWRESULT_OP::OnCancel )
END_EVENT_TABLE()

SHOWRESULT_OP::SHOWRESULT_OP( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    SHOWRESULT( this, TRUE ); 
}

SHOWRESULT_OP::~SHOWRESULT_OP()
{
}

bool SHOWRESULT_OP::TransferDataToWindow(DataBase * pmDataBase)
{    
	// storing query results
	wxArrayString myResults;
	int myResultsNumber = 0;
   
	//find the grid Ctrl 
	wxGrid * myGridCtrl = (wxGrid *)FindWindow(ID_GRID_PROCESS);
	GridOperation * myGridOP = new GridOperation(myGridCtrl);
	
	myResults = pmDataBase->DataBaseGetNextResult();		
	myResultsNumber = myResults.Count();
	
	if (myResultsNumber > 0) 
	{
		// changing number of cols
		myGridOP->GridOpSetNumberOfColumn(myResultsNumber);
		
		// add the first line
		myGridOP->GridOpAddDataRow(myResultsNumber,&myResults);
		
		while (1) 
		{
			myResults = pmDataBase->DataBaseGetNextResult();
			myResultsNumber = myResults.Count();
			if (myResultsNumber == 0) 
			{
				break;
			}
			// add a new line
			myGridOP->GridOpAddDataRow(myResultsNumber,
									  &myResults);
		}
	}
	else 
	{
		wxLogMessage(_("No results returned by your request"));
	}

	return TRUE;
}

void SHOWRESULT_OP::OnCancel(wxCommandEvent &event)
{
    event.Skip();
}

