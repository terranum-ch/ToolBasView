/*!
@file dlg_operation.cpp
@brief   code of all dialogs class
@author Lucien Schreiber (c) CREALP 2007
*/

#include "dlg_operation.h"

//----------------------------------------------------------------------------
// SQLPROCESS_DLG_OP2
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(SQLPROCESS_DLG_OP2,wxDialog)
EVT_BUTTON( wxID_CANCEL, SQLPROCESS_DLG_OP2::OnCancel)
EVT_BUTTON( ID_PROCESS, SQLPROCESS_DLG_OP2::OnProcess)
EVT_BUTTON(ID_BTN_SHOWRESULTS, SQLPROCESS_DLG_OP2::OnShowResult)
EVT_BUTTON(ID_HISTORY, SQLPROCESS_DLG_OP2::OnHistory)
EVT_UPDATE_UI(ID_HISTORY, SQLPROCESS_DLG_OP2::OnUpdateUIHistory)
END_EVENT_TABLE()


SQLPROCESS_DLG_OP2::SQLPROCESS_DLG_OP2( wxWindow *parent, DataBase * database, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    m_DataBase = database;
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
        // add to history
        TBVFrame * myParentFrame = (TBVFrame *) GetParent();
        wxASSERT(myParentFrame);
        wxArrayString * myHistory = myParentFrame->GetHistory();
        if (myHistory != NULL && myHistory->GetCount() != 0) {
            if (myHistory->Item(0) != myRequest) {
                myParentFrame->GetHistory()->Insert(myRequest, 0);
            }
        }
        
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
	SHOWRESULT_OP2 * myDlg = new SHOWRESULT_OP2(this, m_DataBase);
		
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



void SQLPROCESS_DLG_OP2::OnHistory (wxCommandEvent & event){
    TBVFrame * myParentFrame = (TBVFrame *) GetParent();
    wxASSERT(myParentFrame);
    wxString myHistoryValue = wxGetSingleChoice(_("SQL command history"), _("History"), *(myParentFrame->GetHistory()), this, wxDefaultCoord, wxDefaultCoord, false, 500, 500);
    if (myHistoryValue == wxEmptyString) {
        return;
    }
    ((wxTextCtrl*) FindWindow(ID_TEXTCTRL))->SetValue(myHistoryValue);
}



void SQLPROCESS_DLG_OP2::OnUpdateUIHistory (wxUpdateUIEvent & event){
    TBVFrame * myParentFrame = (TBVFrame *) GetParent();
    if (myParentFrame && myParentFrame->GetHistory()->GetCount() == 0) {
        event.Enable(false);
        return;
    }
    event.Enable(true);
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

SHOWRESULT_OP2::SHOWRESULT_OP2( wxWindow *parent, DataBase * database, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    m_DB = database;
    wxASSERT(m_DB);
    SHOWRESULT( this, TRUE );
}

//SHOWRESULT_OP2::~SHOWRESULT_OP2()
//{
//	Destroy();
//}

bool SHOWRESULT_OP2::TransferDataToWindow()
{    
	// storing query results
	wxArrayString myResults;
	int myResultsNumber = 0;
    wxASSERT(m_DB);
   
	//find the grid Ctrl 
	wxGrid * myGridCtrl = (wxGrid *)FindWindow(ID_GRID_PROCESS);
	GridOperation * myGridOP = new GridOperation(myGridCtrl);
	
	if (m_DB->DataBaseGetNextResult(myResults)==false)
	{
		m_DB->DataBaseClearResults();
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
		
		while (m_DB->DataBaseGetNextResult(myResults))
		{
			myGridOP->GridOpAddDataRow(myResultsNumber,
									  &myResults);
		}
		m_DB->DataBaseClearResults();
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



