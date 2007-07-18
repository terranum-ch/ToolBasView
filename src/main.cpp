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
		TreeAddItem(_("essai"),0);
		
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

void TBVFrame::TreeAddItem (wxString tname, int parent)
{
	wxTreeCtrl * myTreeCtrl = (wxTreeCtrl *) FindWindowById(ID_LISTTABLE,this);
	
	if (parent == 0) 
	{
		myTreeCtrl->AddRoot (tname); 
	}
	else 
		myTreeCtrl->AppendItem(myTreeCtrl->GetRootItem(),tname);
	
}

void TBVFrame::OnDoubleClickListe (wxTreeEvent & event)
{
	

}

//void TBVFrame::OnAbout(wxCommandEvent &event)
//{
//	wxMessageDialog * dialog = new wxMessageDialog (this,"coucou","Essai");
//	dialog->ShowModal();
//}