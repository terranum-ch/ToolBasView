/***************************************************************************
 addspatialdata_dlg.h
 Functions for adding spatial data into a database
 -------------------
 copyright            : (C) 2007 CREALP Lucien Schreiber 
 email                : lucien.schreiber at crealp dot vs dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef _ADDSPATIALDATA_DLG_H_
#define _ADDSPATIALDATA_DLG_H_

/*!
 * Includes
 */
#include "../include/database.h"
#include <wx/filepicker.h>
#include "wx/statline.h"

////@begin includes
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
#define ID_ADDSPATIALDATA_DLG 10000
#define ID_FILESELECTOR 10001
#define ID_LISTTABLES 10002
#define ID_STATICLINE 10003
#define SYMBOL_ADDSPATIALDATA_DLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_ADDSPATIALDATA_DLG_TITLE _("Add spatial data into database")
#define SYMBOL_ADDSPATIALDATA_DLG_IDNAME ID_ADDSPATIALDATA_DLG
#define SYMBOL_ADDSPATIALDATA_DLG_SIZE wxSize(500, 400)
#define SYMBOL_ADDSPATIALDATA_DLG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * ADDSPATIALDATA_DLG class declaration
 */

class ADDSPATIALDATA_DLG: public wxDialog
{    
    DataBase * m_pDatabase;
	
	DECLARE_DYNAMIC_CLASS( ADDSPATIALDATA_DLG )
    DECLARE_EVENT_TABLE()
	


public:
    /// Constructors
    ADDSPATIALDATA_DLG();
    ADDSPATIALDATA_DLG( wxWindow* parent,
					   DataBase * pDatabase,
					   wxWindowID id = SYMBOL_ADDSPATIALDATA_DLG_IDNAME, 
					   const wxString& caption = SYMBOL_ADDSPATIALDATA_DLG_TITLE, 
					   const wxPoint& pos = SYMBOL_ADDSPATIALDATA_DLG_POSITION, 
					   const wxSize& size = SYMBOL_ADDSPATIALDATA_DLG_SIZE, 
					   long style = SYMBOL_ADDSPATIALDATA_DLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent,
				DataBase * pDatabase,
				wxWindowID id = SYMBOL_ADDSPATIALDATA_DLG_IDNAME, 
				const wxString& caption = SYMBOL_ADDSPATIALDATA_DLG_TITLE, 
				const wxPoint& pos = SYMBOL_ADDSPATIALDATA_DLG_POSITION, 
				const wxSize& size = SYMBOL_ADDSPATIALDATA_DLG_SIZE, 
				long style = SYMBOL_ADDSPATIALDATA_DLG_STYLE );

    /// Destructor
    ~ADDSPATIALDATA_DLG();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();
	
	bool AddListOfTable ();

////@begin ADDSPATIALDATA_DLG event handler declarations

////@end ADDSPATIALDATA_DLG event handler declarations

////@begin ADDSPATIALDATA_DLG member function declarations
	void SetDataBase(DataBase * pDatabase){m_pDatabase = pDatabase;}

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end ADDSPATIALDATA_DLG member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin ADDSPATIALDATA_DLG member variables
    wxFilePickerCtrl * m_DLGAS_FileSelector;
	wxChoice* m_DLGAS_ListTables;
////@end ADDSPATIALDATA_DLG member variables
};

#endif
    // _ADDSPATIALDATA_DLG_H_
