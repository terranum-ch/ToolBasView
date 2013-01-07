/*!
@file main.h
@brief   declaration of TBVApp and TBVFrame Class
@author Lucien Schreiber (c) CREALP 2007
*/


#ifndef _MAIN_H_
#define _MAIN_H_

const int ID_RUN = 10001;
const int ID_ABOUT = 10002;
const int ID_STATUS = 10003;

#include <wx/treectrl.h> // for tree control
#include <wx/stdpaths.h>
#include <wx/progdlg.h>				// progress dialog.
#include <wx/wupdlock.h>
#include <wx/textfile.h>


#include "database.h"
#include "databaseresult.h"
#include "gridoperation.h" // for grid operation.
#include "addspatialdata_dlg.h" // for adding spatial data
#include "gisdataprovider.h"	// for dealing with spatial data
//#include "ogrsf_frmts.h"			// GDAL - GEOS SUPPORT
#include "deletetabledata_dlg.h"	// deleting data dialog
#include "searchspatialpoint_dlg.h"		// searching spatial data




class TBVFrame: public wxFrame
{
private:
	void OnQuit(wxCloseEvent & event);
	void OnOpenDatabase(wxCommandEvent & event);
	void OnProcessRequest (wxCommandEvent & event);
	void OnDisplayStatistics (wxCommandEvent & event);
	void OnAboutDlg (wxCommandEvent & event);
	void OnMenuExit (wxCommandEvent & event);
	void OnDeleteData (wxCommandEvent & event);
	void OnSpatialDataAdd (wxCommandEvent & event);
	void OnSpatialDataSearch (wxCommandEvent & event);
    void OnExportData (wxCommandEvent & event);
    void OnDatabaseOperation (wxCommandEvent & event);
	void OnMenuIdle (wxIdleEvent & event);
	void EnableMenuItem (bool benable);
	void OnDoubleClickListe (wxTreeEvent & event);
	void OnNewDataBase (wxCommandEvent & event);
    void OnExportStructureToClipboard (wxCommandEvent & event);
    
	DataBase m_Database;
	wxTreeCtrl * pTreeCtrl;
	GridOperation * pGridOp;
    wxArrayString m_History;
    wxFileName m_HistoryFileName;
    
    void _LoadTablesIntoToc();
    
    DECLARE_EVENT_TABLE();
    
public:  
	TBVFrame(wxFrame *frame, const wxString& title,
			 wxPoint  pos,  wxSize  size);
	~TBVFrame();
	
	void TreeAddItem (wxString tname, int parent = 0);
	void ClearCtrls();
    
    wxArrayString * GetHistory();
};

#endif
