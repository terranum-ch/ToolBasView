/////////////////////////////////////////////////////////////////////////////
// Name:        deletetabledata_dlg.h
// Purpose:     
// Author:      Lucien Schreiber
// Modified by: 
// Created:     Tue 26 Feb 18:07:40 2008
// RCS-ID:      
// Copyright:   (c) 2007 CREALP
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _DELETETABLEDATA_DLG_H_
#define _DELETETABLEDATA_DLG_H_

/*!
 * Includes
 */

////@begin includes
#include "wx/statline.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DELETETABLEDATA_DLG 10004
#define ID_DLGDEL_TABLES 10005
#define ID_DLGDEL_CHK_DATA 10006
#define ID_DLGDEL_CHK_TABLE 10007
#define ID_DLGDEL_VACUUM 10008
#define ID_STATICLINE2 10010
#define SYMBOL_DELETETABLEDATA_DLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_DELETETABLEDATA_DLG_TITLE _("Delete data")
#define SYMBOL_DELETETABLEDATA_DLG_IDNAME ID_DELETETABLEDATA_DLG
#define SYMBOL_DELETETABLEDATA_DLG_SIZE wxSize(400, 300)
#define SYMBOL_DELETETABLEDATA_DLG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * DELETETABLEDATA_DLG class declaration
 */

class DELETETABLEDATA_DLG: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( DELETETABLEDATA_DLG )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    DELETETABLEDATA_DLG();
    DELETETABLEDATA_DLG( wxWindow* parent, wxWindowID id = SYMBOL_DELETETABLEDATA_DLG_IDNAME, const wxString& caption = SYMBOL_DELETETABLEDATA_DLG_TITLE, const wxPoint& pos = SYMBOL_DELETETABLEDATA_DLG_POSITION, const wxSize& size = SYMBOL_DELETETABLEDATA_DLG_SIZE, long style = SYMBOL_DELETETABLEDATA_DLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DELETETABLEDATA_DLG_IDNAME, const wxString& caption = SYMBOL_DELETETABLEDATA_DLG_TITLE, const wxPoint& pos = SYMBOL_DELETETABLEDATA_DLG_POSITION, const wxSize& size = SYMBOL_DELETETABLEDATA_DLG_SIZE, long style = SYMBOL_DELETETABLEDATA_DLG_STYLE );

    /// Destructor
    ~DELETETABLEDATA_DLG();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin DELETETABLEDATA_DLG event handler declarations

////@end DELETETABLEDATA_DLG event handler declarations

////@begin DELETETABLEDATA_DLG member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end DELETETABLEDATA_DLG member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin DELETETABLEDATA_DLG member variables
    wxCheckBox* m_DlgDel_Chk_Data;
    wxCheckBox* m_DlgDel_Chk_table;
    wxCheckBox* m_DlgDel_Chk_Vacuum;
////@end DELETETABLEDATA_DLG member variables
};

#endif
    // _DELETETABLEDATA_DLG_H_
