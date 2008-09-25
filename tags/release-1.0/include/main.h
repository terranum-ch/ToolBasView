/*!
@file main.h
@brief   declaration of TBVApp and TBVFrame Class
@author Lucien Schreiber (c) CREALP 2007
*/


#ifndef MAIN_H
#define MAIN_H

const int ID_RUN = 10001;
const int ID_ABOUT = 10002;
const int ID_STATUS = 10003;

#include "../include/database.h"
#include <wx/treectrl.h> // for tree control
#include "../include/gridoperation.h" // for grid operation.
#include "../include/dlg_operation.h" // for dialogs operations.


// ART FILES
#include "../art/Fish_sml.xpm"

const wxString sProgName = _("ToolBasView version 1.0");

/*!
@class		TBVApp
@abstract    (brief description)
@discussion  (comprehensive description)
*/
class TBVApp : public wxApp
{
public:
	virtual bool OnInit();
	
};
IMPLEMENT_APP(TBVApp);


/*!
@class		TBVFrame
@abstract    (brief description)
@discussion  (comprehensive description)
*/
class TBVFrame: public wxFrame
{
public:
	TBVFrame(wxFrame *frame, const wxString& title,
			 wxPoint  pos,  wxSize  size);
	~TBVFrame();
	
	/*!
    @function 
    @brief   Append data to the tree item
    @param   tname a wxString used for the item name
	@param   parent a integer used to define if an item is master or child
	(0 for master and 1 for child)
 	*/
	void TreeAddItem (wxString tname, int parent = 0);
	
	/*!
    @function
	@brief Delete all tree item content and call deletion of all
	the grid table.
	*/
	void ClearCtrls();
	
	
private:
	void OnQuit(wxCloseEvent & event);
	void OnOpenDatabase(wxCommandEvent & event);
	void OnProcessRequest (wxCommandEvent & event);
	void OnDisplayStatistics (wxCommandEvent & event);
	void OnAboutDlg (wxCommandEvent & event);
	void OnMenuExit (wxCommandEvent & event);
	/*!
    @function 
    @brief Called when user double click on the treectrl
	*/
	void OnDoubleClickListe (wxTreeEvent & event);

	/*!
    @function 
    @brief function called when user select 'create new database'
	*/	
	void OnNewDataBase (wxCommandEvent & event);

	
	DECLARE_EVENT_TABLE();
	
	
	DataBase myDatabase;
	
	wxTreeCtrl * pTreeCtrl;
	
	GridOperation * pGridOp;
	
};

#endif