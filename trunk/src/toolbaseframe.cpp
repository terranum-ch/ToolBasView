/*!
@file main.cpp
@brief   definition of TBVApp and TBVFrame Class
@author Lucien Schreiber (c) CREALP 2007
*/

#include "toolbaseframe.h"
#include "interface.h"
#include "lsversion_dlg.h"
#include "exportcsv_dlg.h"
#include "databaseoperation.h"
#include "../art/toolbasview_bmp.cpp"
#include "dlg_operation.h" // for dialogs operations.
#include "lsfoldbar.h"




BEGIN_EVENT_TABLE (TBVFrame, wxFrame)
EVT_MENU (wxID_ABOUT, TBVFrame::OnAboutDlg)
EVT_MENU (wxID_EXIT, TBVFrame::OnMenuExit)
EVT_MENU (ID_OPEN_DB,TBVFrame::OnOpenDatabase)
EVT_CLOSE(TBVFrame::OnQuit)
EVT_TREE_ITEM_ACTIVATED (ID_LISTTABLE,TBVFrame::OnDoubleClickListe)
EVT_MENU (ID_PROCESS_MENU,TBVFrame::OnProcessRequest)
EVT_MENU (ID_NEW_DBASE,TBVFrame::OnNewDataBase)
EVT_MENU (ID_MENU_STATISTICS,TBVFrame::OnDisplayStatistics)
EVT_MENU (ID_MENU_SPATIAL_ADD,TBVFrame::OnSpatialDataAdd)
EVT_MENU (ID_MENU_DELETE, TBVFrame::OnDeleteData)
EVT_MENU (ID_MENU_SPATIAL_SEARCH, TBVFrame::OnSpatialDataSearch )
EVT_MENU(wxID_SAVEAS, TBVFrame::OnExportData)
EVT_MENU(ID_MENU_DB_OPERATION, TBVFrame::OnDatabaseOperation)
EVT_MENU(ID_MENU_EXPORT_STRUCTURE, TBVFrame::OnExportStructureToClipboard)
EVT_IDLE (TBVFrame::OnMenuIdle)
END_EVENT_TABLE()


/* Frame initialisation */
TBVFrame::TBVFrame(wxFrame *frame, const wxString& title,wxPoint pos, wxSize size)
			: wxFrame(frame, -1, title,pos,size)
{
    wxInitAllImageHandlers();
    initialize_images();
    
    // Loading icon
	wxIcon myIcon;
    myIcon.CopyFromBitmap(*_img_toolbasview);
    SetIcon(myIcon);
	
    // adding status bar
	CreateStatusBar(2,0,ID_STATUS);
	
	// dessin de l'interface
	//wxPanel * top_panel = new wxPanel (this, -1,wxDefaultPosition,wxDefaultSize );
	//INTERFACE(top_panel, FALSE);
	
	// create the menu
	SetMenuBar(MENU());
    
    _CreateControls();
    	
	
	// define as log window
	//wxLog::SetActiveTarget (new wxLogTextCtrl ((wxTextCtrl *) FindWindowById(ID_LOG,this)));
	wxLog::SetActiveTarget (new wxLogTextCtrl (m_LogTxt));
    
	// programm started
	wxLogMessage(_("Program started"));
	
	// get the client version
	wxString myVersion = _("Database embedded version : ") +  DataBase::DataBaseGetVersion();
	SetStatusText(myVersion ,1);
	
	// loading GDAL 
	OGRRegisterAll();
	wxLogMessage(_T("All GDAL driver registered..."));
	
	// getting the tree ctrl
	//pTreeCtrl = (wxTreeCtrl *) FindWindowById(ID_LISTTABLE,this);
	
	// Creating the gridoperation object
	//pGridOp = new GridOperation((wxGrid *) FindWindowById(ID_GRID,this));
    
    // loading history
    m_HistoryFileName = wxFileName(wxStandardPaths::Get().GetAppDocumentsDir(), _T("toolbasview_history.txt"));
  	wxTextFile myHistoryFile (m_HistoryFileName.GetFullPath());
    if(m_HistoryFileName.Exists() == false){
        myHistoryFile.Create();
    }
    else{
        myHistoryFile.Open();
    }
    m_History.Clear();
    for (wxString str = myHistoryFile.GetFirstLine(); !myHistoryFile.Eof(); str = myHistoryFile.GetNextLine() ){
        m_History.Add(str);
    }
}



void TBVFrame::_CreateControls(){
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxSplitterWindow* m_splitter1;
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE );
	
	wxPanel* m_panel1;
	m_panel1 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_TreeCtrl = new wxTreeCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer2->Add( m_TreeCtrl, 1, wxEXPAND, 5 );
	
	wxPanel* m_panel5;
	m_panel5 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel5->SetMinSize( wxSize( -1,50 ) );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBitmap* m_bitmap2;
	m_bitmap2 = new wxStaticBitmap( m_panel5, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_bitmap2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panel5->SetSizer( bSizer6 );
	m_panel5->Layout();
	bSizer6->Fit( m_panel5 );
	bSizer2->Add( m_panel5, 0, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	wxPanel* m_panel2;
	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_GridCtrl = new wxGrid( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_GridCtrl->CreateGrid( 5, 5 );
	m_GridCtrl->EnableEditing( true );
	m_GridCtrl->EnableGridLines( true );
	m_GridCtrl->EnableDragGridSize( false );
	m_GridCtrl->SetMargins( 0, 0 );
	
	// Columns
	m_GridCtrl->EnableDragColMove( false );
	m_GridCtrl->EnableDragColSize( true );
	m_GridCtrl->SetColLabelSize( 30 );
	m_GridCtrl->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_GridCtrl->EnableDragRowSize( true );
	m_GridCtrl->SetRowLabelSize( 80 );
	m_GridCtrl->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_GridCtrl->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer3->Add( m_GridCtrl, 1, wxEXPAND, 5 );
	
	wxPanel* m_panel6;
	m_panel6 = new wxPanel( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_QueryCtrl = new wxTextCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer7->Add( m_QueryCtrl, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	wxButton* m_button3;
	m_button3 = new wxButton( m_panel6, wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button3, 0, wxALL, 5 );
	
	wxButton* m_button5;
	m_button5 = new wxButton( m_panel6, wxID_ANY, wxT("Show Results"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button5, 0, wxALL, 5 );
	
	wxButton* m_button6;
	m_button6 = new wxButton( m_panel6, wxID_ANY, wxT("History..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button6, 0, wxALL, 5 );
	
	
	bSizer7->Add( bSizer9, 0, wxEXPAND, 5 );
	
	
	m_panel6->SetSizer( bSizer7 );
	m_panel6->Layout();
	bSizer7->Fit( m_panel6 );
	bSizer3->Add( m_panel6, 1, wxEXPAND, 5 );
	   
    
    // FOLDING CONTROL 
    lsFoldBarCtrl * myFoldCtrl = new lsFoldBarCtrl(m_panel2, wxID_ANY);
    wxSizerItem * mySizerItem = bSizer3->Add(myFoldCtrl, 1, wxALL | wxEXPAND, 0);
    
    m_LogTxt = new wxTextCtrl( myFoldCtrl, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    myFoldCtrl->GetClientSizer()->Add(m_LogTxt, 1, wxEXPAND | wxALL, 5);
    myFoldCtrl->SetSizerItem(mySizerItem);
    myFoldCtrl->SetTitle(_("Log"));
    myFoldCtrl->HideBar();
    
	
	m_panel2->SetSizer( bSizer3 );
	m_panel2->Layout();
	bSizer3->Fit( m_panel2 );
	m_splitter1->SplitVertically( m_panel1, m_panel2, 0 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
}



/* Frame destruction */
TBVFrame::~TBVFrame()
{
    // write history (limit to 1000 records)
    wxASSERT(m_HistoryFileName.Exists());
    wxTextFile myHistoryFile (m_HistoryFileName.GetFullPath());
    myHistoryFile.Open();
    myHistoryFile.Clear();
    
    for (unsigned int i = 0; i< m_History.GetCount(); i++) {
        myHistoryFile.AddLine(m_History[i]);
        if (i >= 1000) {
            break;
        }
    }
    myHistoryFile.Write();
    uninitialize_images();
}


void TBVFrame::OnOpenDatabase(wxCommandEvent & event)
{
	const wxString & dir = wxDirSelector (_("Choose the database folder"));
	if (dir.empty())
		return;
	
	// clear all the controls.
	ClearCtrls();
	
	
	
	wxFileName myDirPath (dir, _T(""));
	if (myDirPath.IsOk()==false)
	{
		wxLogError(_T("Incorrect path"));
		return;
	}
	
	wxArrayString myDirsString = myDirPath.GetDirs();
	myDirPath.RemoveLastDir();
	
	if(m_Database.DataBaseOpen(myDirPath.GetFullPath(wxPATH_NATIVE),
							   myDirsString.Item(myDirsString.GetCount()-1))==false){
		return;
    }
	
	wxLogMessage(_("Path : %s, Name : %s"),
				 m_Database.DataBaseGetPath().c_str(),
				 m_Database.DataBaseGetName().c_str());
	_LoadTablesIntoToc();
		
	// get the database size
	wxLogMessage( m_Database.DataBaseGetSize());
}

void TBVFrame::OnDeleteData (wxCommandEvent & event)
{	
	DELETETABLEDATA_DLG myDelDlg (this, wxID_ANY, &m_Database);
	// set the active possibilities for the database
	// deleting
	myDelDlg.SetActiveFlags(DEL_FLAGS_DATA | DEL_FLAGS_TABLE);
	
	// if we choose to delete some tables
	// processing is done into the dialog itself.
	myDelDlg.ShowModal();
}


void TBVFrame::OnMenuExit(wxCommandEvent & event)
{
	Close();
}


void TBVFrame::OnQuit(wxCloseEvent & event)
{
	this->Destroy();
}


void TBVFrame::OnProcessRequest (wxCommandEvent & event)
{
    SQLPROCESS_DLG_OP2 * myDlg = new SQLPROCESS_DLG_OP2(this, &m_Database);
    myDlg->Show();
    if ( myDlg->GetSuccess()){
        _LoadTablesIntoToc();
    }
}


void TBVFrame::OnSpatialDataAdd (wxCommandEvent & event)
{
	GISOgrProvider myOgrData;
	GISDBProvider myDBData;
	wxString myWkbString;
	wxArrayString myReadData;
	int i=1;
	long lFeatureCount = 0;
	
	ADDSPATIALDATA_DLG * myDlg = new ADDSPATIALDATA_DLG(this, &m_Database, -1);
	// show the dialog
	if (myDlg->ShowModal() != wxID_OK)
	{
		delete myDlg;
		return;
	}
	

	// try to open spatial data
	myOgrData.GISOpen(myDlg->m_VectorFileName);
	lFeatureCount = myOgrData.GISGetFeatureCount();
	wxLogDebug(_T("Number of feature read : %d"), lFeatureCount);
	
	// try to open database data
	myDBData.GISOpen(&m_Database);
	myDBData.GISSetActiveLayer(myDlg->m_DBTableName);
	
	// create a progress dialog for showing
	// import progress
	int iMax = lFeatureCount / 1000;
	wxProgressDialog myPrgDlg (_("Importing data into the Database"),
							   _("Importing in progress, please wait..."),
							   iMax);
	
	
	// count elapsed time
	wxStopWatch sw;
	
	while (myOgrData.GISGetNextFeatureAsWktBuffer(&myReadData, 1000))
	{
		myDBData.GISSetFeatureAsWkTBuffer(myReadData, TRUE);
		
		if (i <= iMax)
		{
			myPrgDlg.Update(i);
			i++;	
		}
		
		// clear the buffer
		myReadData.Clear();
	}
	
	// show elapsed time
	wxLogMessage(_("Elapsed time for adding %d spatial data is : %u [ms]"), 
				 lFeatureCount,  sw.Time());
	
	
	// creating index if asked
	if (myDlg->m_bComputeIndex == TRUE)
	{
		sw.Start();
		wxArrayString myFields;
		
		if(myDBData.GISComputeIndex(myFields, myDlg->m_DBTableName))
		{
			wxLogMessage(_("Creating index take %u [ms]"), sw.Time());
		}
	}
	
	// don't forget to close the spatial data
	myOgrData.GISClose();
	myDBData.GISClose();
	
	delete myDlg;
}



void TBVFrame::OnSpatialDataSearch (wxCommandEvent & event)
{
	SEARCHSPATIALPOINT_DLG myDlg (this, &m_Database);
	if (myDlg.OpenDBGISData(_T(""),_T("GENERIC_LINES")))
	{
		myDlg.ShowModal();
	}
	
}


void TBVFrame::OnExportData (wxCommandEvent & event){
    ExportCSV_DLG myDlg(this, wxID_ANY, _("Export Data"), &m_Database);
    myDlg.ShowModal();
}


void TBVFrame::OnDatabaseOperation (wxCommandEvent & event){
    DatabaseOp_DLG myDlg(this, wxID_ANY);
    if (myDlg.ShowModal() != wxID_OK) {
        return;
    }
    
    // get all tables
    wxString myQuery = _T("SHOW TABLES");
    if (m_Database.DataBaseQuery(myQuery, true)==false) {
        return;
    }
    wxArrayString myTables;
    if (m_Database.DataBaseGetResults(myTables)==false) {
        wxLogError(_("Listing database tables failed!"));
        return;
    }
    m_Database.DataBaseClearResults();
    
    
    wxArrayString myResults;
    if (myDlg.GetCheck() == true) {
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            if(m_Database.DataBaseQuery(_T("CHECK TABLE ") + myTables[i],true)==false){
                return;
            }
            myResults.Clear();
            wxString myResultsAggregated = wxEmptyString;
            m_Database.DataBaseGetNextResult(myResults);
            for (unsigned int m = 0; m < myResults.GetCount(); m++) {
                myResultsAggregated.Append(myResults[m] + _T(" | "));
            }
            myResultsAggregated.RemoveLast(3);
            wxLogMessage(myResultsAggregated);
            m_Database.DataBaseClearResults();
        }
    }
    
    
    if (myDlg.GetOptimize() == true) {
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            if(m_Database.DataBaseQuery(_T("OPTIMIZE TABLE ") + myTables[i],true)==false){
                return;
            }
            myResults.Clear();
            wxString myResultsAggregated = wxEmptyString;
            if(m_Database.DataBaseHasResults() == true){
                m_Database.DataBaseGetNextResult(myResults);
                for (unsigned int m = 0; m < myResults.GetCount(); m++) {
                    myResultsAggregated.Append(myResults[m] + _T(" | "));
                }
                myResultsAggregated.RemoveLast(3);
                wxLogMessage(myResultsAggregated);
                m_Database.DataBaseClearResults();
            }
        }
    }
    
    
    if (myDlg.GetRepair() == true) {
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            if(m_Database.DataBaseQuery(_T("REPAIR TABLE ") + myTables[i],true)==false){
                return;
            }
            myResults.Clear();
            wxString myResultsAggregated = wxEmptyString;
            if(m_Database.DataBaseHasResults() == true){
                m_Database.DataBaseGetNextResult(myResults);
                for (unsigned int m = 0; m < myResults.GetCount(); m++) {
                    myResultsAggregated.Append(myResults[m] + _T(" | "));
                }
                myResultsAggregated.RemoveLast(3);
                wxLogMessage(myResultsAggregated);
                m_Database.DataBaseClearResults();
            }
        }
    }


    
}



void TBVFrame::OnMenuIdle (wxIdleEvent & event)
{
	// function called during idle event for 
	// hiding menu
	bool bStarted = false;
	if (m_Database.DataBaseGetName() != wxEmptyString)
		bStarted = true;
	
	EnableMenuItem(bStarted);

}


void TBVFrame::EnableMenuItem (bool benable)
{
	wxMenuBar * mypMenu = GetMenuBar();
	mypMenu->Enable(ID_MENU_STATISTICS, benable);
	mypMenu->Enable(ID_PROCESS_MENU, benable);
	mypMenu->Enable(ID_MENU_SPATIAL_ADD, benable);
	mypMenu->Enable(ID_MENU_SPATIAL_SEARCH, benable);
	mypMenu->Enable(ID_MENU_DELETE, benable);
    mypMenu->Enable(wxID_SAVEAS,benable);
    mypMenu->Enable(ID_MENU_DB_OPERATION, benable);
    mypMenu->Enable(ID_MENU_EXPORT_STRUCTURE, benable);
}



void TBVFrame::TreeAddItem (wxString tname, int parent)
{
	if (parent == 0) 
	{
		m_TreeCtrl->AddRoot (tname);
	}
	else 
		m_TreeCtrl->AppendItem(m_TreeCtrl->GetRootItem(),tname);
}


void TBVFrame::ClearCtrls ()
{
	m_TreeCtrl->DeleteAllItems();
	
	m_GridOp->GridClear();
}


void TBVFrame::_LoadTablesIntoToc(){

    m_GridOp->GridClear();
    wxWindowUpdateLocker noUpdates(m_TreeCtrl);
    m_TreeCtrl->DeleteAllItems();
    
    if (m_Database.DataBaseQuery(_T("SHOW TABLES"))==false){
        return;
    }

	wxArrayString myStringArray;
	m_Database.DataBaseGetResults(myStringArray);
	m_Database.DataBaseClearResults();
	
	// add database name
	TreeAddItem((m_Database.DataBaseGetName()),0);
	
	// add tables names
	for (unsigned int i=0; i<myStringArray.Count(); i++){
		TreeAddItem(myStringArray.Item(i),1);
	}
    m_TreeCtrl->ExpandAll();
}




void TBVFrame::OnDoubleClickListe (wxTreeEvent & event)
{
	wxArrayString myFieldArray;
	unsigned int i; // loop
	
	wxTreeItemId myItemID = event.GetItem();
	// get the table name
	wxString myTempString = m_TreeCtrl->GetItemText(myItemID);
	m_Database.DataBaseQuery(_T("SHOW COLUMNS FROM ") + myTempString);
	m_Database.DataBaseGetResults(myFieldArray);
	
	// check for field numbers (may be not a table)
	if (myFieldArray.Count() > 0)
	{
		// debug message...
		wxLogMessage(_("%ld fields readed from the table '%s'"),
					 myFieldArray.Count(),myTempString.c_str());
		
		// change the number of cols
		m_GridOp->GridOpSetNumberOfColumn(myFieldArray.Count());
		
		for (i = 0; i<myFieldArray.Count(); i++) 
		{
			m_GridOp->GridOpChangeColumnText(myFieldArray.Item(i),i,TRUE);
		}
		
		// get the data....
		if(m_Database.DataBaseQuery(_T("SELECT * FROM ") + myTempString))
		{
			wxLogMessage(_("Reading table '%s' OK"),myTempString.c_str());
			
			int iArrayCount = 0;
			
			while (m_Database.DataBaseGetNextResult(myFieldArray)) 
			{
				iArrayCount = myFieldArray.Count();
				// add a new line
				m_GridOp->GridOpAddDataRow(iArrayCount,
										  &myFieldArray);
			}
			m_Database.DataBaseClearResults();
		
		}
		else 
		{
			wxLogError(_("Error reading the table '%s'"),myTempString.c_str());
		}

		
		
	}
	
}


void TBVFrame::OnExportStructureToClipboard (wxCommandEvent & event){
    wxString myExportChoices [] = {_("Structure"), _("Data")};
    wxMultiChoiceDialog myDlg(this, _("Choose what to export:"),  _("Dump to clipboard"), 2, &myExportChoices[0]);
    if(myDlg.ShowModal()== wxID_CANCEL){
        return;
    }
    
    wxArrayInt myDlgChoice = myDlg.GetSelections();
    if (myDlgChoice.GetCount() == 0) {
        wxLogWarning(_("Nothing selected! Nothing exported!"));
        return;
    }
    
    wxString myClipboardTxt = wxEmptyString;
    wxString myQuery = _T("SHOW TABLES");
    if (m_Database.DataBaseQuery(myQuery)==false) {
        wxLogError(_("Error loading tables structure to clipboard"));
        return;
    }
    if (m_Database.DataBaseHasResults() == false) {
        wxLogError(_("Database didn't contain any table!"));
        return;
    }
    wxArrayString myTables;
    m_Database.DataBaseGetResults(myTables);
    
    
    // export structure
    if (myDlgChoice.Index(0) != wxNOT_FOUND) {
        myClipboardTxt.Append(_T("-- DATABASE STRUCTURE --\n"));
        wxLogMessage(_("Exporting structure to clipboard..."));
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            myQuery = wxString::Format(_T("SHOW CREATE TABLE %s"), myTables.Item(i));
            if (m_Database.DataBaseQuery(myQuery)==false) {
                wxLogError(_("Getting table structure for '%s' failed!"), myTables.Item(i));
                continue;
            }
            DataBaseResult myResult;
            wxString myText = wxEmptyString;
            m_Database.DataBaseGetResults(&myResult);
            myResult.NextRow();
            myResult.GetValue(1, myText);
            myClipboardTxt.Append(wxString::Format(_T("-- %s --\n"), myTables.Item(i)));
            myClipboardTxt.Append(myText);
            myClipboardTxt.Append(_T("\n\n"));
        }
    }
    
    // export data
    if (myDlgChoice.Index(1) != wxNOT_FOUND) {
        wxLogMessage(_("Exporting data to clipboard..."));
        myClipboardTxt.Append(_T("-- DATABASE DATA --\n\n"));
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            myQuery = wxString::Format(_T("SELECT * FROM %s"), myTables.Item(i));
            if (m_Database.DataBaseQuery(myQuery)==false) {
                wxLogError(_("Getting table data for '%s' failed!"), myTables.Item(i));
                continue;
            }
            
            myClipboardTxt.Append(wxString::Format(_T("-- %s --\n"), myTables.Item(i)));
            
            DataBaseResult myResult;
            m_Database.DataBaseGetResults(&myResult);
            
            for (long r = 0; r < myResult.GetRowCount(); r++) {
                wxString myText = wxEmptyString;
                myResult.NextRow();
                myText = wxString::Format(_("INSERT INTO %s VALUES("), myTables.Item(i));
                for (int c = 0; c < myResult.GetColCount(); c++) {
                    if (myResult.IsTextField(c)==true) {
                        wxString myColValue;
                        myResult.GetValue(c, myColValue);
                        myText.Append(wxString::Format(_T("\"%s\","), myColValue));
                    }
                    
                    if (myResult.IsNumField(c)==true) {
                        wxString myColValue;
                        myResult.GetValue(c, myColValue);
                        myText.Append(wxString::Format(_T("%s,"), myColValue));
                    }
                    
                    if (myResult.IsGeomField(c)==true) {
                        //OGRGeometry * myGeom = NULL;
                        wxString myValue = wxEmptyString;
                        myResult.GetValue(c, myValue);
                        /*
                        char * myExport;
                        myGeom->exportToWkt(&myExport);
                        wxString sExport = wxString::FromAscii(myExport);
                        wxDELETE(myExport);
                        wxDELETE(myGeom);*/
                        if (myValue == wxEmptyString) {
                            myValue = _T("NULL");
                        }
                        myText.Append(wxString::Format(_T("%s,"), myValue));
                    }
                    
                }
                myText.RemoveLast();
                myText.Append(_T(");\n"));
                myClipboardTxt.Append(myText);
            }
            
            myClipboardTxt.Append(_T("\n\n"));
        }

    }
    
    
       
    if (wxTheClipboard->Open()){
        wxTheClipboard->SetData( new wxTextDataObject(myClipboardTxt) );
        wxTheClipboard->Close();
    }
}



void TBVFrame::OnNewDataBase (wxCommandEvent & event)
{
	wxLogMessage (_("New database"));
	NEWDBASE_OP2 * myDlg = new NEWDBASE_OP2(this,-1,_("Create a new database"),
				wxDefaultPosition, wxDefaultSize);
	myDlg->CenterOnParent();
	if (myDlg->ShowModal()==wxID_OK)
	{
	// clean the tree ctrl
		ClearCtrls();
		
		// create realy the database...
		m_Database.DataBaseCreateNew(myDlg->m_DLG_DB_PATH,myDlg->m_DLG_DB_NAME);
		
		wxLogMessage(_("Database '%s' created OK"), myDlg->m_DLG_DB_NAME.c_str());
		
		// add database name
		TreeAddItem((myDlg->m_DLG_DB_NAME),0);
	}
	
}

void TBVFrame::OnDisplayStatistics (wxCommandEvent & event)
{
	// checking if a database is open ?
	// getting the stats...
	long myiNumberTables = 0;
	wxString mysNumberTables = _T("Unkhown");
	m_Database.DataBaseQuery(_T("SELECT COUNT(*) AS number_of_tables ") 
							 _T("FROM information_schema.tables ") 
							 _T("WHERE table_schema = \"") + m_Database.DataBaseGetName() + _T("\""));
	if (m_Database.DataBaseGetNextResult(myiNumberTables)==true)
		mysNumberTables = wxString::Format(_T("%d"), myiNumberTables);
	m_Database.DataBaseClearResults();
	wxString m_DatabaseSize = m_Database.DataBaseGetSize();
		
		wxString myText = wxString::Format(_("Database : '%s' open \n"),m_Database.DataBaseGetName().c_str());
		myText.Append(wxString::Format(_("Number of table(s) : %s \n"),mysNumberTables.c_str()));
		myText.Append(_("Size of the database : ") + m_DatabaseSize);
		wxMessageBox(myText,_("Database statistics"),wxOK | wxICON_INFORMATION,
					 this);
		
}

void TBVFrame::OnAboutDlg(wxCommandEvent & event)
{
	lsVersionDlg myDlg(this, wxID_ANY, _("About"));
    myDlg.SetBitmapLogo(*_img_toolbasview);
    myDlg.ShowModal();
}


wxArrayString * TBVFrame::GetHistory(){
    return & m_History;
}

