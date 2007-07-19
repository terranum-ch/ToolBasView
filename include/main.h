/*!
@header main.h
@abstract   (description)
@discussion (description)

*/


#ifndef MAIN_H
#define MAIN_H

const int ID_RUN = 10001;
const int ID_ABOUT = 10002;
const int ID_STATUS = 10003;

#include "../include/database.h"
#include <wx/treectrl.h> // for tree control
#include "../include/gridoperation.h" // for grid operation.
#include "../include/Dialogs_ops.h" // for dialogs operations.


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
	
	
private:
	void OnQuit(wxCloseEvent & event);
	void OnAbout(wxCommandEvent& event);
	void OnOpenDatabase(wxCommandEvent & event);
	void OnProcessRequest (wxCommandEvent & event);
	/*!
    @function 
    @brief Called when user double click on the treectrl
	*/
	void OnDoubleClickListe (wxTreeEvent & event);

	
	DECLARE_EVENT_TABLE();
	
	
	DataBase myDatabase;
	
	wxTreeCtrl * pTreeCtrl;
	
	GridOperation * pGridOp;
	
};

#endif
