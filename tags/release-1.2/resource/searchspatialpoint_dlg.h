/////////////////////////////////////////////////////////////////////////////
// Name:        searchspatialpoint_dlg.h
// Purpose:     
// Author:      Lucien Schreiber
// Modified by: 
// Created:     Wed 27 Feb 17:08:27 2008
// RCS-ID:      
// Copyright:   (c) 2007 CREALP
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _SEARCHSPATIALPOINT_DLG_H_
#define _SEARCHSPATIALPOINT_DLG_H_


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
#define ID_SEARCHSPATIALPOINT_DLG 10011
#define ID_TEXTCTRL1 10012
#define ID_TEXTCTRL2 10013
#define ID_SLIDER1 10014
#define SYMBOL_SEARCHSPATIALPOINT_DLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_SEARCHSPATIALPOINT_DLG_TITLE _("Search spatial data")
#define SYMBOL_SEARCHSPATIALPOINT_DLG_IDNAME ID_SEARCHSPATIALPOINT_DLG
#define SYMBOL_SEARCHSPATIALPOINT_DLG_SIZE wxSize(400, 300)
#define SYMBOL_SEARCHSPATIALPOINT_DLG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * SEARCHSPATIALPOINT_DLG class declaration
 */

class SEARCHSPATIALPOINT_DLG: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( SEARCHSPATIALPOINT_DLG )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SEARCHSPATIALPOINT_DLG();
    SEARCHSPATIALPOINT_DLG( wxWindow* parent, wxWindowID id = SYMBOL_SEARCHSPATIALPOINT_DLG_IDNAME, const wxString& caption = SYMBOL_SEARCHSPATIALPOINT_DLG_TITLE, const wxPoint& pos = SYMBOL_SEARCHSPATIALPOINT_DLG_POSITION, const wxSize& size = SYMBOL_SEARCHSPATIALPOINT_DLG_SIZE, long style = SYMBOL_SEARCHSPATIALPOINT_DLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SEARCHSPATIALPOINT_DLG_IDNAME, const wxString& caption = SYMBOL_SEARCHSPATIALPOINT_DLG_TITLE, const wxPoint& pos = SYMBOL_SEARCHSPATIALPOINT_DLG_POSITION, const wxSize& size = SYMBOL_SEARCHSPATIALPOINT_DLG_SIZE, long style = SYMBOL_SEARCHSPATIALPOINT_DLG_STYLE );

    /// Destructor
    ~SEARCHSPATIALPOINT_DLG();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin SEARCHSPATIALPOINT_DLG event handler declarations

////@end SEARCHSPATIALPOINT_DLG event handler declarations

////@begin SEARCHSPATIALPOINT_DLG member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SEARCHSPATIALPOINT_DLG member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SEARCHSPATIALPOINT_DLG member variables
    wxStaticText* m_DLGSS_Map_Xmin;
    wxStaticText* m_DLGSS_Map_Xmax;
    wxStaticText* m_DLGSS_Map_Ymin;
    wxStaticText* m_DLGSS_Map_Ymax;
    wxTextCtrl* m_DLGSS_coord_x;
    wxTextCtrl* m_DLGSS_coord_x;
    wxSlider* m_DLGSS_buffer;
    wxStaticText* m_DLGSS_result_index;
    wxStaticText* m_DLGSS_result_index_tm;
    wxStaticText* m_DLGSS_result_status;
    wxStaticText* m_DLGSS_result_status_tm;
////@end SEARCHSPATIALPOINT_DLG member variables
};

#endif
    // _SEARCHSPATIALPOINT_DLG_H_
