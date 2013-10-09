/*!
 @file main.h
 @brief   declaration of TBVApp and TBVFrame Class
 @author Lucien Schreiber (c) CREALP 2007
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include <wx/treectrl.h>
#include <wx/stdpaths.h>
#include <wx/progdlg.h>
#include <wx/wupdlock.h>
#include <wx/textfile.h>
#include <wx/treectrl.h>
#include <wx/grid.h>
#include <wx/imaglist.h>
#include <wx/aui/aui.h>
#include <wx/treectrl.h>
#include <wx/stc/stc.h>
#include <wx/filehistory.h>
#include <wx/fileconf.h>
#include <wx/msgdlg.h>

#include "database.h"
#include "databaseresult.h"
#include "gridoperation.h" // for grid operation.
#include "addspatialdata_dlg.h" // for adding spatial data
#include "gisdataprovider.h"	// for dealing with spatial data
//#include "ogrsf_frmts.h"			// GDAL - GEOS SUPPORT
#include "deletetabledata_dlg.h"	// deleting data dialog
#include "searchspatialpoint_dlg.h"		// searching spatial data

class QueryListTree;

// menus
const int ID_MENU_MAINTENANCE = wxWindow::NewControlId();
const int ID_MENU_STATISTICS = wxWindow::NewControlId();
const int ID_MENU_IMPORT_TXT = wxWindow::NewControlId();
const int ID_MENU_IMPORT_SQL = wxWindow::NewControlId();
const int ID_MENU_EXPORT_TXT = wxWindow::NewControlId();
const int ID_MENU_EXPORT_DUMPCLIPBOARD = wxWindow::NewControlId();
const int ID_MENU_MANIP_CHANGE_COL_TYPE = wxWindow::NewControlId();
const int ID_MENU_MANIP_DELETE = wxWindow::NewControlId();
const int ID_MENU_SPATIAL_ADD = wxWindow::NewControlId();
const int ID_MENU_SPATIAL_SEARCH = wxWindow::NewControlId();
const int ID_MENU_SHOW_QUERYPANEL = wxWindow::NewControlId();
const int ID_MENU_SHOW_LOG = wxWindow::NewControlId();
const int ID_MENU_AUTOSIZE_COLUMNS = wxWindow::NewControlId();
const int ID_MENU_WEB_MYSQL = wxWindow::NewControlId();

// controls
const int ID_LISTTABLE = wxWindow::NewControlId();
const int ID_BTN_RUN = wxWindow::NewControlId();
const int ID_BTN_SHOW_RESULTS = wxWindow::NewControlId();
const int ID_BTN_HISTORY = wxWindow::NewControlId();
const int ID_BTN_ADD_TO_LIST = wxWindow::NewControlId();
const int ID_QUERY_LIST_TREE = wxWindow::NewControlId();


class TBVFrame: public wxFrame
{
private:
	void OnQuit(wxCloseEvent & event);
	void OnOpenDatabase(wxCommandEvent & event);
    void OnOpenRecentDatabase (wxCommandEvent & event);
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
    void OnProcessSQLFile (wxCommandEvent & event);
    void OnImportTXTFile (wxCommandEvent & event);
    void OnChangeColumnType (wxCommandEvent & event);
    void OnMySQLReference (wxCommandEvent & event);
    
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
    bool _OpenDatabase (const wxString & path);
    
    
	DataBase m_Database;
	wxTreeCtrl * m_TreeCtrl;
	GridOperation * m_GridOp;
    wxGrid * m_GridCtrl;
    wxArrayString m_History;
    wxFileName m_HistoryFileName;
    wxFileName m_QueryListFileName;
    wxFileHistory m_FileHist;
    wxFileConfig * m_ConfigFile;
    
    wxImageList * m_ImgList;
    wxAuiManager m_mgr;
    wxStaticText* m_VersionTxtCtrl;
    wxStyledTextCtrl* m_QueryTxtCtrl;
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
