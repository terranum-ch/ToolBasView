/*!
@file dlg_operation.cpp
@brief   code of all dialogs class
@author Lucien Schreiber (c) CREALP 2007
*/


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "dlg_operation.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "../include/dlg_operation.h"

#include <wx/intl.h>

// Euro sign hack of the year
#if wxUSE_UNICODE
    #define __WDR_EURO__ wxT("\u20ac")
#else
    #if defined(__WXMAC__)
        #define __WDR_EURO__ wxT("\xdb")
    #elif defined(__WXMSW__)
        #define __WDR_EURO__ wxT("\x80")
    #else
        #define __WDR_EURO__ wxT("\xa4")
    #endif
#endif

#include <wx/clipbrd.h>



//----------------------------------------------------------------------------
// SQLPROCESS_DLG_OP2
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(SQLPROCESS_DLG_OP2,wxDialog)
    EVT_BUTTON( wxID_CANCEL, SQLPROCESS_DLG_OP2::OnCancel)
    EVT_BUTTON( ID_PROCESS, SQLPROCESS_DLG_OP2::OnProcess)
    EVT_BUTTON(ID_BTN_SHOWRESULTS, SQLPROCESS_DLG_OP2::OnShowResult)
END_EVENT_TABLE()


SQLPROCESS_DLG_OP2::SQLPROCESS_DLG_OP2( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    // WDR: dialog function SQLPROCESS for SQLPROCESS_DLG_OP2
    SQLPROCESS( this, TRUE ); 
	m_hasRequest = FALSE;
}

SQLPROCESS_DLG_OP2::~SQLPROCESS_DLG_OP2()
{
	Destroy();
}

bool SQLPROCESS_DLG_OP2::GetSuccess()
{
	return m_hasRequest;
}

void SQLPROCESS_DLG_OP2::SetDataBase(DataBase * pDatabase)
{
	m_DataBase = pDatabase;
}

// WDR: handler implementations for SQLPROCESS_DLG_OP2

void SQLPROCESS_DLG_OP2::OnProcess( wxCommandEvent &event )
{
	wxASSERT(m_DataBase);
	wxArrayString myRequestArray; // contain multiple request if needed
	wxArrayInt myErrorsArray;
	wxString myTempRequest;
	
	wxBeginBusyCursor();
	
	// if results, destroy them
	if (m_DataBase->DataBaseHasResults()==true)
	{
		m_DataBase->DataBaseClearResults();
		wxLogDebug(_T("Results of last query where automatically cleared"));
	}
	
	
	// get the text to process.
	wxString myRequest = ((wxTextCtrl*) FindWindow(ID_TEXTCTRL))->GetValue();
	int myNumberOfRequest = m_DataBase->DataBaseQueriesNumber(myRequest);
	wxLogMessage(_("Processing Request... %d Request Found"),myNumberOfRequest);
	
	wxString myComment = _("Query error, please check syntax");
	if (m_DataBase->DataBaseQuery(myRequest)==true)
	{
		myComment = _("Query passed OK, no results");
		
		if (m_DataBase->DataBaseHasResults()==true)
		{
			myComment = _("Query passed OK");
			wxButton * myShowResultButton = (wxButton*)FindWindow(ID_BTN_SHOWRESULTS);
			wxASSERT(myShowResultButton);
			myShowResultButton->Enable(true);
		}
		
	}

	// display results
	((wxStaticText *) FindWindow(ID_REQUEST_RESULT))->SetLabel(myComment);	
	
	// end busy...
	wxEndBusyCursor();
	
}

void SQLPROCESS_DLG_OP2::OnShowResult (wxCommandEvent & event)
{
		
	// new dialog 
	SHOWRESULT_OP2 * myDlg = new SHOWRESULT_OP2(this,
											  -1, _("SQL Results"),
											  wxDefaultPosition,wxSize(500,500),
											  wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
	
	
	// transfert data to the window
	myDlg->TransferDataToWindow(m_DataBase);
	
	// gray the button
	wxButton * myShowResultButton = (wxButton*)FindWindow(ID_BTN_SHOWRESULTS);
	wxASSERT(myShowResultButton);
	myShowResultButton->Enable(false);
	
	
	// show the window
	//myDlg->SetExtraStyle(wxDIALOG_EX_METAL);
	myDlg->SetMinSize(wxSize(300,300));
	myDlg->SetSize(wxSize(500,400));
	myDlg->Show(TRUE);
	
}


void SQLPROCESS_DLG_OP2::OnCancel(wxCommandEvent &event)
{
	if (m_hasRequest) 
	{
		SetReturnCode(ID_PROCESS);
	}
	this->Destroy();
    event.Skip();
}




//----------------------------------------------------------------------------
// SHOWRESULT_OP2
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(SHOWRESULT_OP2,wxDialog)
    EVT_BUTTON( wxID_CANCEL, SHOWRESULT_OP2::OnCancel )
	EVT_BUTTON(wxID_COPY, SHOWRESULT_OP2::OnCopyResults)
END_EVENT_TABLE()

SHOWRESULT_OP2::SHOWRESULT_OP2( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    SHOWRESULT( this, TRUE );
}

//SHOWRESULT_OP2::~SHOWRESULT_OP2()
//{
//	Destroy();
//}

bool SHOWRESULT_OP2::TransferDataToWindow(DataBase * pmDataBase)
{    
	// storing query results
	wxArrayString myResults;
	int myResultsNumber = 0;
   
	//find the grid Ctrl 
	wxGrid * myGridCtrl = (wxGrid *)FindWindow(ID_GRID_PROCESS);
	GridOperation * myGridOP = new GridOperation(myGridCtrl);
	
	if (pmDataBase->DataBaseGetNextResult(myResults)==false)
	{
		pmDataBase->DataBaseClearResults();
		wxLogError(_T("No results, this is an error"));
		return false;
	}
	myResultsNumber = myResults.Count();
	if (myResultsNumber > 0) 
	{
		// changing number of cols
		myGridOP->GridOpSetNumberOfColumn(myResultsNumber);
		
		// add the first line
		myGridOP->GridOpAddDataRow(myResultsNumber,&myResults);
		
		while (pmDataBase->DataBaseGetNextResult(myResults)) 
		{
			myGridOP->GridOpAddDataRow(myResultsNumber,
									  &myResults);
		}
		pmDataBase->DataBaseClearResults();
	}
	
	else 
	{
		wxLogMessage(_("No results returned by your request"));
	}

	return true;
}

void SHOWRESULT_OP2::OnCancel(wxCommandEvent &event)
{
    event.Skip();
}


void SHOWRESULT_OP2::OnCopyResults(wxCommandEvent & event){
	
	//find the grid Ctrl 
	wxGrid * myGridCtrl = (wxGrid *)FindWindow(ID_GRID_PROCESS);
	wxASSERT(myGridCtrl);
	
	wxString myValues = wxEmptyString;
	for (int irow = 0; irow < myGridCtrl->GetNumberRows(); irow++){
		for (int icol = 0; icol < myGridCtrl->GetNumberCols(); icol++) {			
			myValues.Append(myGridCtrl->GetCellValue(irow, icol));
			if (icol < myGridCtrl->GetNumberCols() -1) {
				myValues.Append(_T("\t"));
			}
		}
		myValues.Append(_T("\n"));
	}
	
	if (wxTheClipboard->Open())
    {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData(new wxTextDataObject(myValues));
        wxTheClipboard->Close();
    }
}
			   

//----------------------------------------------------------------------------
// NEWDBASE_OP2
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(NEWDBASE_OP2,wxDialog)
    EVT_BUTTON( wxID_OK, NEWDBASE_OP2::OnOk )
    EVT_BUTTON( wxID_CANCEL, NEWDBASE_OP2::OnCancel )
	EVT_BUTTON( ID_BTN_CHOOSE_PATH, NEWDBASE_OP2::OnDisplayDirectory)
END_EVENT_TABLE()

NEWDBASE_OP2::NEWDBASE_OP2( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    NEWDBASE( this, TRUE ); 
}

//NEWDBASE_OP2::~NEWDBASE_OP2()
//{
//}

bool NEWDBASE_OP2::TransferDataFromWindow()
{
    // function called automatically if user click ok...
	wxTextCtrl * myPathCtrl = (wxTextCtrl*) FindWindow(ID_TXT_DB_PATH);
	wxTextCtrl * myNameCtrl = (wxTextCtrl *) FindWindow(ID_TXT_DB_NAME);
	
	m_DLG_DB_PATH = myPathCtrl->GetValue();
	m_DLG_DB_NAME = myNameCtrl->GetValue();
	return TRUE;

}


void NEWDBASE_OP2::OnOk(wxCommandEvent &event)
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

void NEWDBASE_OP2::OnCancel(wxCommandEvent &event)
{
    event.Skip();
}

void NEWDBASE_OP2::OnDisplayDirectory (wxCommandEvent & event)
{
	const wxString dir = wxDirSelector(_("Select a path for the new database"));
	if (!dir.IsEmpty())
	{
		((wxTextCtrl*)FindWindow(ID_TXT_DB_PATH))->SetValue(dir);	
	}
}



