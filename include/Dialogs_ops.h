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
    
    
private:
	DataBase * m_DataBase;

    
private:
    // WDR: handler declarations for SQLPROCESS_DLG_OP
    void OnProcess( wxCommandEvent &event );
    void OnCancel( wxCommandEvent &event );

private:
    DECLARE_EVENT_TABLE()
};



#endif
