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
#include <wx/treectrl.h>
#include <wx/grid.h>
#include <wx/imaglist.h>
#include <wx/aui/aui.h>
#include <wx/treectrl.h>



#include "database.h"
#include "databaseresult.h"
#include "gridoperation.h" // for grid operation.
#include "addspatialdata_dlg.h" // for adding spatial data
#include "gisdataprovider.h"	// for dealing with spatial data
//#include "ogrsf_frmts.h"			// GDAL - GEOS SUPPORT
#include "deletetabledata_dlg.h"	// deleting data dialog
#include "searchspatialpoint_dlg.h"		// searching spatial data

class lsFoldBarCtrl;
class QueryListTree;


const int ID_FILE_MENU = wxID_HIGHEST + 1;
const int ID_MENU = wxID_HIGHEST + 3;
const int ID_OP_MENU = wxID_HIGHEST + 4;
const int ID_PROCESS_MENU = wxID_HIGHEST + 5;
const int ID_NEW_DBASE = wxID_HIGHEST + 6;
const int ID_MENU_STATISTICS = wxID_HIGHEST + 7;
const int ID_MENU_SPATIAL_ADD = wxID_HIGHEST + 8;
const int ID_MENU_DELETE = wxID_HIGHEST + 9;
const int ID_MENU_SPATIAL_SEARCH = wxID_HIGHEST + 10;
const int ID_MENU_DB_OPERATION = wxID_HIGHEST + 11;
const int ID_MENU_EXPORT_STRUCTURE = wxID_HIGHEST + 12;
const int ID_LISTTABLE = wxID_HIGHEST + 13;
const int ID_BTN_RUN = wxID_HIGHEST + 14;
const int ID_BTN_SHOW_RESULTS = wxID_HIGHEST + 15;
const int ID_BTN_HISTORY = wxID_HIGHEST + 16;
const int ID_MENU_AUTOSIZE_COLUMNS = wxID_HIGHEST + 19;
const int ID_MENU_SHOW_LOG = wxWindow::NewControlId();
const int ID_BTN_ADD_TO_LIST = wxWindow::NewControlId();
const int ID_QUERY_LIST_TREE = wxWindow::NewControlId();


class TBVFrame: public wxFrame
{
private:
	void OnQuit(wxCloseEvent & event);
	void OnOpenDatabase(wxCommandEvent & event);
	void OnShowProcessRequest (wxCommandEvent & event);
    void OnShowLogPanel (wxCommandEvent & event);
	void OnDisplayStatistics (wxCommandEvent & event);
	void OnAboutDlg (wxCommandEvent & event);
	void OnMenuExit (wxCommandEvent & event);
	void OnDeleteData (wxCommandEvent & event);
	void OnSpatialDataAdd (wxCommandEvent & event);
	void OnSpatialDataSearch (wxCommandEvent & event);
    void OnExportData (wxCommandEvent & event);
    void OnDatabaseOperation (wxCommandEvent & event);
	void OnDoubleClickListe (wxTreeEvent & event);
	void OnNewDataBase (wxCommandEvent & event);
    void OnExportStructureToClipboard (wxCommandEvent & event);
    void OnUpdateUIDatabaseOpen (wxUpdateUIEvent & event);
    void OnAuiButtonPressed (wxAuiManagerEvent& evt);
    void OnColumnSize (wxCommandEvent & event);
    
    void OnBtnRun (wxCommandEvent & event);
    void OnBtnShowResults (wxCommandEvent & event);
    void OnBtnHistory (wxCommandEvent & event);
    void OnAddToList (wxCommandEvent & event);
    
    void OnTreeItemDoubleClick (wxTreeEvent & event);
    
    void OnUpdateUIBtnRun (wxUpdateUIEvent & event);
    void OnUpdateUIBtnShowResults (wxUpdateUIEvent & event);
    void OnUpdateUIBtnHistory (wxUpdateUIEvent & event);
    void OnUpdateUIAutosize (wxUpdateUIEvent & event);
    void OnUpdateUIAddToList (wxUpdateUIEvent & event);
    
    void _LoadTablesIntoToc();
    void _CreateControls();
    void _CreateMenu();
    void _CreateToolBar();
    void _UpdateHistory (const wxString & sentence);

    
	DataBase m_Database;
	wxTreeCtrl * m_TreeCtrl;
	GridOperation * m_GridOp;
    wxGrid * m_GridCtrl;
    wxArrayString m_History;
    wxFileName m_HistoryFileName;
    
    wxImageList * m_ImgList;
    wxAuiManager m_mgr;
    wxStaticText* m_VersionTxtCtrl;
    wxTextCtrl* m_QueryTxtCtrl;
    wxButton* m_QueryRunCtrl;
    wxButton* m_QueryShowCtrl;
    wxButton* m_QueryHistoryCtrl;
    wxTextCtrl* m_LogCtrl;
    wxPanel* m_querypanel;
    wxPanel* m_QueryListPanel;
    QueryListTree* m_QueryListTreeCtrl;
    wxButton* m_AddToListBtnCtrl;

  
    
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
