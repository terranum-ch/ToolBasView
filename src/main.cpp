/*!
@header main.cpp
 @abstract   (description)
 @discussion (description)
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



/* Application initialisation */
bool TBVApp::OnInit()
{
	
	
	
	TBVFrame* frame = new TBVFrame(0L, sProgName,wxPoint(50,50), wxSize(620,480));
	
	
	frame->Show();
	frame->Centre();
	
	return true;
}

BEGIN_EVENT_TABLE (TBVFrame, wxFrame)
//EVT_MENU (ID_RUN, TBVFrame::OnAbout)
  EVT_MENU (ID_OPEN_DB,TBVFrame::OnOpenDatabase)
  EVT_CLOSE(TBVFrame::OnQuit)
  EVT_TREE_ITEM_ACTIVATED (ID_LISTTABLE,TBVFrame::OnDoubleClickListe)
  EVT_MENU (ID_PROCESS_MENU,TBVFrame::OnProcessRequest)
END_EVENT_TABLE()


/* Frame initialisation */
TBVFrame::TBVFrame(wxFrame *frame, const wxString& title,wxPoint pos, wxSize size)
			: wxFrame(frame, -1, title,pos,size)
{
    // Loading icon
	// wxIcon icon(sirs_xpm);
    //SetIcon(icon);
	
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
	SetStatusText(_("MySQL embedded version : ") + myDatabase.DatabaseGetVersion(),1);
	
	
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
	wxArrayString myStringArray;
	
	if(myDatabase.DataBaseOpen(_("/Users/Lucien/DATA/PRJ/TOOLMAP/TestBDD/BDD/data/")))
	{
		wxLogMessage(_("Database opened"));
				
		myStringArray = myDatabase.DataBaseListTables();
		
		// add database name
		TreeAddItem(_("i4418575"),0);
		
		// add tables names
		for (int i=0; i<myStringArray.Count(); i++) 
		{
			TreeAddItem(myStringArray.Item(i),1);
		}
		
	}
	else
	{
		wxLogError(_("Error opening the database"));
	}
	

}


void TBVFrame::OnQuit(wxCloseEvent & event)
{
		// if the database is opened, we close the database.
		if (myDatabase.DataBaseIsOpen()) 
		{
			myDatabase.DataBaseClose();
		}
		
		this->Destroy();

}


void TBVFrame::OnProcessRequest (wxCommandEvent & event)
{
	if (myDatabase.DataBaseIsOpen()) 
	{
			
		// create and display the SQLPROCESS dialog box.
		SQLPROCESS_DLG_OP * myDlg = new SQLPROCESS_DLG_OP(this,
														  -1, _("Process SQL User Request"),
														  wxDefaultPosition,wxDefaultSize,
														  wxDEFAULT_DIALOG_STYLE	| wxRESIZE_BORDER);
		
		myDlg->SetDataBase(&myDatabase);													
		myDlg->SetMinSize(wxSize(300,200));
		myDlg->CentreOnParent();
		myDlg->ShowModal();	
	}
	else
	{
		wxLogError(_("No Database opened, please open a database first"));
	}
 	
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



void TBVFrame::OnDoubleClickListe (wxTreeEvent & event)
{
	wxArrayString myFieldArray;
	int i; // loop
	
	wxTreeItemId myItemID = event.GetItem();
	// get the table name
	wxString myTempString = pTreeCtrl->GetItemText(myItemID);
	myFieldArray = myDatabase.DatabaseListFields(myTempString);
	
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
		if(myDatabase.DataBaseGetAllTableContent(myTempString))
		{
			wxLogMessage(_("Reading table '%s' OK"),myTempString.c_str());
			
			int iArrayCount = 0;
			
			while (1) 
			{
				myFieldArray = myDatabase.DataBaseGetNextResult();
				iArrayCount = myFieldArray.Count();
				if (iArrayCount == 0) 
				{
					break;
				}
				
				// add a new line
				pGridOp->GridOpAddDataRow(iArrayCount,
										  &myFieldArray);
			}
		
		}
		else 
		{
			wxLogError(_("Error reading the table '%s'"),myTempString.c_str());
		}

		
		
	}
	
}

//void TBVFrame::OnAbout(wxCommandEvent &event)
//{
//	wxMessageDialog * dialog = new wxMessageDialog (this,"coucou","Essai");
//	dialog->ShowModal();
//}