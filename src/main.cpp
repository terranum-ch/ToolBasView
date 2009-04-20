/*!
@file main.cpp
@brief   definition of TBVApp and TBVFrame Class
@author Lucien Schreiber (c) CREALP 2007
*/


#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "../include/main.h"
#include "../include/interface.h"

// for svn version
#include "../include/svn_version.h"

const wxString DATABASE_TYPE_STRING = _T("MySQL");

/* Application initialisation */
bool TBVApp::OnInit()
{
	wxString myProgFrameName = sProgName;
	myProgFrameName.Append(_T(".") SVN_VERSION);
	myProgFrameName.Append(wxString::Format(_T(" [%s]"), DATABASE_TYPE_STRING.c_str()));
	
	TBVFrame* frame = new TBVFrame(0L, myProgFrameName,wxPoint(50,50), wxSize(620,520));
	
	//frame->SetExtraStyle(wxDIALOG_EX_METAL);
	frame->Centre();
	frame->Show();
	
	
	return true;
}

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
EVT_IDLE (TBVFrame::OnMenuIdle)
END_EVENT_TABLE()


/* Frame initialisation */
TBVFrame::TBVFrame(wxFrame *frame, const wxString& title,wxPoint pos, wxSize size)
			: wxFrame(frame, -1, title,pos,size)
{
    // Loading icon
	wxIcon icon(Fish_sml_xpm);
    SetIcon(icon);
	
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
	wxLogDebug(_T("All GDAL driver registered..."));
	
	// getting the tree ctrl
	pTreeCtrl = (wxTreeCtrl *) FindWindowById(ID_LISTTABLE,this);
	
	// Creating the gridoperation object
	pGridOp = new GridOperation((wxGrid *) FindWindowById(ID_GRID,this));
	
}


/* Frame destruction */
TBVFrame::~TBVFrame()
{
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
	
	if(myDatabase.DataBaseOpen(myDirPath.GetPath(wxPATH_GET_SEPARATOR, wxPATH_UNIX),
							   myDirsString.Item(myDirsString.GetCount()-1))==false)
		return;
	
	wxLogMessage(_("Path : %s, Name : %s"),
				 myDatabase.DataBaseGetPath().c_str(),
				 myDatabase.DataBaseGetName().c_str());
	
	if (myDatabase.DataBaseQuery(_T("SHOW TABLES"))==false)
		return;
	
	wxArrayString myStringArray;
	myDatabase.DataBaseGetResults(myStringArray);
	myDatabase.DataBaseClearResults();
	
	// add database name
	TreeAddItem((myDatabase.DataBaseGetName()),0);
	
	// add tables names
	for (unsigned int i=0; i<myStringArray.Count(); i++) 
	{
		TreeAddItem(myStringArray.Item(i),1);
	}
	
	// get the database size
	wxLogMessage( myDatabase.DataBaseGetSize());
}

void TBVFrame::OnDeleteData (wxCommandEvent & event)
{	
	DELETETABLEDATA_DLG myDelDlg (this, wxID_ANY, &myDatabase);
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
			
		
		// create and display the SQLPROCESS dialog box.
		SQLPROCESS_DLG_OP2 * myDlg = new SQLPROCESS_DLG_OP2(this,
														  -1, _("Process SQL User Request"),
														  wxDefaultPosition,wxDefaultSize,
														  wxDEFAULT_DIALOG_STYLE	| wxRESIZE_BORDER | wxDIALOG_EX_METAL);
		
		myDlg->SetDataBase(&myDatabase);
		//myDlg->SetExtraStyle(wxDIALOG_EX_METAL);													
		myDlg->SetMinSize(wxSize(300,200));
		myDlg->SetSize(wxSize(500,400));
		myDlg->CentreOnParent();
		myDlg->Show();
		if ( myDlg->GetSuccess()) 
		{
			// clear all the controls.
			ClearCtrls();
			myDatabase.DataBaseQuery(_T("SHOW TABLES"));
			wxArrayString myStringArray;
			myDatabase.DataBaseGetResults(myStringArray);
			myDatabase.DataBaseClearResults();
			
			// add database name
			TreeAddItem((myDatabase.DataBaseGetName()),0);
			
			// add tables names
			for (unsigned int i=0; i<myStringArray.Count(); i++) 
			{
				TreeAddItem(myStringArray.Item(i),1);
			}
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
	
	ADDSPATIALDATA_DLG * myDlg = new ADDSPATIALDATA_DLG(this, &myDatabase, -1);
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
	myDBData.GISOpen(&myDatabase);
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
	SEARCHSPATIALPOINT_DLG myDlg (this, &myDatabase);
	if (myDlg.OpenDBGISData(_T(""),_T("GENERIC_LINES")))
	{
		myDlg.ShowModal();
	}
	
}


void TBVFrame::OnMenuIdle (wxIdleEvent & event)
{
	// function called during idle event for 
	// hiding menu
	bool bStarted = false;
	if (myDatabase.DataBaseGetName() != wxEmptyString)
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



void TBVFrame::OnDoubleClickListe (wxTreeEvent & event)
{
	wxArrayString myFieldArray;
	unsigned int i; // loop
	
	wxTreeItemId myItemID = event.GetItem();
	// get the table name
	wxString myTempString = pTreeCtrl->GetItemText(myItemID);
	myDatabase.DataBaseQuery(_T("SHOW COLUMNS FROM ") + myTempString);
	myDatabase.DataBaseGetResults(myFieldArray);
	
	// check for field numbers (may be not a table)
	if (myFieldArray.Count() > 0)
	{
		// debug message...
		wxLogMessage(_("%d fields readed from the table '%s'"),
					 myFieldArray.Count(),myTempString.c_str());
		
		// change the number of cols
		pGridOp->GridOpSetNumberOfColumn(myFieldArray.Count());
		
		for (i = 0; i<myFieldArray.Count(); i++) 
		{
			pGridOp->GridOpChangeColumnText(myFieldArray.Item(i),i,TRUE);
		}
		
		// get the data....
		if(myDatabase.DataBaseQuery(_T("SELECT * FROM ") + myTempString))
		{
			wxLogMessage(_("Reading table '%s' OK"),myTempString.c_str());
			
			int iArrayCount = 0;
			
			while (myDatabase.DataBaseGetNextResult(myFieldArray)) 
			{
				iArrayCount = myFieldArray.Count();
				// add a new line
				pGridOp->GridOpAddDataRow(iArrayCount,
										  &myFieldArray);
			}
			myDatabase.DataBaseClearResults();
		
		}
		else 
		{
			wxLogError(_("Error reading the table '%s'"),myTempString.c_str());
		}

		
		
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
		myDatabase.DataBaseCreateNew(myDlg->m_DLG_DB_PATH,myDlg->m_DLG_DB_NAME);
		
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
	myDatabase.DataBaseQuery(_T("SELECT COUNT(*) AS number_of_tables ") 
							 _T("FROM information_schema.tables ") 
							 _T("WHERE table_schema = \"") + myDatabase.DataBaseGetName() + _T("\""));
	if (myDatabase.DataBaseGetNextResult(myiNumberTables)==true)
		mysNumberTables = wxString::Format(_T("%d"), myiNumberTables);
	myDatabase.DataBaseClearResults();
	wxString myDataBaseSize = myDatabase.DataBaseGetSize();
		
		wxString myText = wxString::Format(_("Database : '%s' open \n"),myDatabase.DataBaseGetName().c_str());
		myText.Append(wxString::Format(_("Number of table(s) : %s \n"),mysNumberTables.c_str()));
		myText.Append(_("Size of the database : ") + myDataBaseSize);
		wxMessageBox(myText,_("Database statistics"),wxOK | wxICON_INFORMATION,
					 this);
		
}

void TBVFrame::OnAboutDlg(wxCommandEvent & event)
{
	wxLogMessage (_("About the program"));
	ABOUTDLG_OP2 * myDlg = new ABOUTDLG_OP2(this,wxID_ANY,_("About"),
		wxDefaultPosition,wxDefaultSize);
	myDlg->CenterOnParent();
	myDlg->ShowModal();
}

