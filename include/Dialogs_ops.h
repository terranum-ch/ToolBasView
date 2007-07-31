/*!
    @file dialogs_ops.h
    @brief declaration of ressources dialogs operations
*/

#ifndef __Dialogs_ops_H__
#define __Dialogs_ops_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "../src/Dialogs_ops.cpp"
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "../include/dialogs.h"
#include "../include/database.h" 
#include <wx/dirdlg.h>
#include <wx/filename.h> // for verification purpose



//----------------------------------------------------------------------------
// SQLPROCESS_DLG_OP
//----------------------------------------------------------------------------
class SQLPROCESS_DLG_OP: public wxDialog
{
public:
    // constructors and destructors
    SQLPROCESS_DLG_OP( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );
    virtual ~SQLPROCESS_DLG_OP();
	
	/*!
    @function 
    @brief Call this function to transfer the class adress to the dialogbox
	@param      pointerMySQL a MYSQL pointer to an existing MYSQL database.
	*/
	void SetDataBase(DataBase * pDatabase);
	
	/*!
    @function 
    @brief Return true if a request was made correctely 
	*/
	bool GetSuccess (){return m_hasRequest;}
    
    
private:
	DataBase * m_DataBase;
	
	bool m_hasRequest;

    
private:
    // WDR: handler declarations for SQLPROCESS_DLG_OP
    void OnProcess( wxCommandEvent &event );
    void OnCancel( wxCommandEvent &event );
	void OnShowResult (wxCommandEvent & event);

private:
    DECLARE_EVENT_TABLE()
};


//----------------------------------------------------------------------------
// NEWDBASE_OP
//----------------------------------------------------------------------------
class NEWDBASE_OP: public wxDialog
{
public:
    // constructors and destructors
    NEWDBASE_OP( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );
    virtual ~NEWDBASE_OP();
    
 
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

//----------------------------------------------------------------------------
// ABOUTDLG_OP
//----------------------------------------------------------------------------
class ABOUTDLG_OP: public wxDialog
{
public:
    // constructors and destructors
    ABOUTDLG_OP( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );
    virtual ~ABOUTDLG_OP();
    
    
    
private:
    void OnOk( wxCommandEvent &event );

private:
    DECLARE_EVENT_TABLE()
};



#endif
