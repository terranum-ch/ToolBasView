/*!
@file dlg_operation.h
@brief   definition of all dialogs class
@author Lucien Schreiber (c) CREALP 2007
*/

#ifndef __DLG_OPERATION_H__
#define __DLG_OPERATION_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "dlg_operation.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"



// Include wxWidgets' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/toolbar.h>


#include "dialogs.h"
#include "gridoperation.h"
#include "database.h" 
#include <wx/filename.h> // for verification purpose

#include <wx/hyperlink.h>




//----------------------------------------------------------------------------
// SQLPROCESS_DLG_OP2
//----------------------------------------------------------------------------
class SQLPROCESS_DLG_OP2 : public wxDialog
{
private:
	DataBase * m_DataBase;
	bool m_hasRequest;
    
    // WDR: handler declarations for SQLPROCESS_DLG_OP2
    void OnProcess( wxCommandEvent &event );
    void OnCancel( wxCommandEvent &event );
	void OnShowResult (wxCommandEvent & event);
    
    DECLARE_EVENT_TABLE();
    
public:
    // constructors and destructors
    SQLPROCESS_DLG_OP2( wxWindow *parent, DataBase * database, wxWindowID id = wxID_ANY, const wxString &title = _("Run SQL code"), const wxPoint& pos = wxDefaultPosition,const wxSize& size = wxDefaultSize,long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER );
    virtual ~SQLPROCESS_DLG_OP2();
	
	/*!
    @function 
    @brief Return true if a request was made correctely 
	*/
	bool GetSuccess ();
        
};


//----------------------------------------------------------------------------
// SHOWRESULT_OP2
//----------------------------------------------------------------------------

class SHOWRESULT_OP2: public wxDialog
{
private:
    DataBase * m_DB;
    
public:
    // constructors and destructors
    SHOWRESULT_OP2( wxWindow *parent, DataBase * database, wxWindowID id = wxID_ANY, const wxString &title = _("SQL Results"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxSize(500,500),
        long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
   // virtual ~SHOWRESULT_OP2();
    
	virtual bool TransferDataToWindow();

    
private:
    // WDR: handler declarations for SHOWRESULT_OP2
    void OnCancel( wxCommandEvent &event );
	void OnCopyResults (wxCommandEvent & event);

private:
    DECLARE_EVENT_TABLE()
};



//----------------------------------------------------------------------------
// NEWDBASE_OP2
//----------------------------------------------------------------------------
class NEWDBASE_OP2: public wxDialog
{
public:
    // constructors and destructors
    NEWDBASE_OP2( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );
     //virtual ~NEWDBASE_OP2();
    
 
    virtual bool TransferDataFromWindow();
    
	wxString m_DLG_DB_NAME;
	wxString m_DLG_DB_PATH;

    
private:
    void OnOk( wxCommandEvent &event );
    void OnCancel( wxCommandEvent &event );
	void OnDisplayDirectory (wxCommandEvent &event);

private:
    DECLARE_EVENT_TABLE()
		
};

#endif
