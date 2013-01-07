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
	wxPanel * top_panel = new wxPanel (this, -1,wxDefaultPosition,wxDefaultSize );
	INTERFACE(top_panel, FALSE);
	
	// create the menu
	SetMenuBar(MENU());
	
	
	// define as log window
	wxLog::SetActiveTarget (new wxLogTextCtrl ((wxTextCtrl *) FindWindowById(ID_LOG,this)));
	
	// programm started
	wxLogMessage(_("Program started"));
	
	// get the client version
	wxString myVersion = _("Database embedded version : ") +  DataBase::DataBaseGetVersion();
	SetStatusText(myVersion ,1);
	
	// loading GDAL 
	OGRRegisterAll();
	wxLogMessage(_T("All GDAL driver registered..."));
	
	// getting the tree ctrl
	pTreeCtrl = (wxTreeCtrl *) FindWindowById(ID_LISTTABLE,this);
	
	// Creating the gridoperation object
	pGridOp = new GridOperation((wxGrid *) FindWindowById(ID_GRID,this));
    
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
		pTreeCtrl->AddRoot (tname); 
	}
	else 
		pTreeCtrl->AppendItem(pTreeCtrl->GetRootItem(),tname);	
}


void TBVFrame::ClearCtrls ()
{
	pTreeCtrl->DeleteAllItems();
	
	pGridOp->GridClear();
}


void TBVFrame::_LoadTablesIntoToc(){

    pGridOp->GridClear();
    wxWindowUpdateLocker noUpdates(pTreeCtrl);
    pTreeCtrl->DeleteAllItems();
    
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
    pTreeCtrl->ExpandAll();
}




void TBVFrame::OnDoubleClickListe (wxTreeEvent & event)
{
	wxArrayString myFieldArray;
	unsigned int i; // loop
	
	wxTreeItemId myItemID = event.GetItem();
	// get the table name
	wxString myTempString = pTreeCtrl->GetItemText(myItemID);
	m_Database.DataBaseQuery(_T("SHOW COLUMNS FROM ") + myTempString);
	m_Database.DataBaseGetResults(myFieldArray);
	
	// check for field numbers (may be not a table)
	if (myFieldArray.Count() > 0)
	{
		// debug message...
		wxLogMessage(_("%ld fields readed from the table '%s'"),
					 myFieldArray.Count(),myTempString.c_str());
		
		// change the number of cols
		pGridOp->GridOpSetNumberOfColumn(myFieldArray.Count());
		
		for (i = 0; i<myFieldArray.Count(); i++) 
		{
			pGridOp->GridOpChangeColumnText(myFieldArray.Item(i),i,TRUE);
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
				pGridOp->GridOpAddDataRow(iArrayCount,
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
    wxLogMessage(_("Exporting structure to clipboard..."));
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
    wxString myClipboardTxt = wxEmptyString;
    
    for (unsigned int i = 0; i< myTables.GetCount(); i++) {
        myQuery = wxString::Format(_T("SHOW CREATE TABLE %s"), myTables.Item(i));
        if (m_Database.DataBaseQuery(myQuery)==false) {
            wxLogError(_("Getting table structure for '%s' failed!"), myTables.Item(i));
            continue;
        }
        DataBaseResult myResult;
        m_Database.DataBaseGetResults(&myResult);
        myResult.NextRow();
        wxString myText;
        myResult.GetValue(1, myText);
        myClipboardTxt.Append(wxString::Format(_T("-- %s --\n"), myTables.Item(i)));
        myClipboardTxt.Append(myText);
        myClipboardTxt.Append(_T("\n\n"));
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

