/***************************************************************************
 searchspatialpoint.h
 Dialog functions for searching spatial data. Mainly used for benchmarks 
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
#ifndef _SEARCHSPATIALPOINT_DLG_H_
#define _SEARCHSPATIALPOINT_DLG_H_


#include "wx/statline.h"
#include "gisdataprovider.h"

#define ID_SEARCHSPATIALPOINT_DLG 10011
#define ID_TEXTCTRL1 10012
#define ID_TEXTCTRL2 10013
#define ID_SLIDER1 10014
#define SYMBOL_SEARCHSPATIALPOINT_DLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_SEARCHSPATIALPOINT_DLG_TITLE _("Search spatial data")
#define SYMBOL_SEARCHSPATIALPOINT_DLG_IDNAME ID_SEARCHSPATIALPOINT_DLG
#define SYMBOL_SEARCHSPATIALPOINT_DLG_SIZE wxSize(400, 300)
#define SYMBOL_SEARCHSPATIALPOINT_DLG_POSITION wxDefaultPosition


class SEARCHSPATIALPOINT_DLG: public wxDialog
{  
private:
    DECLARE_DYNAMIC_CLASS( SEARCHSPATIALPOINT_DLG )
    DECLARE_EVENT_TABLE()
	
	DataBase * m_pDatabase;
	GISDBProvider m_GISDB;

public:
    SEARCHSPATIALPOINT_DLG();
    SEARCHSPATIALPOINT_DLG( wxWindow* parent,
						   DataBase * database,
						   wxWindowID id = SYMBOL_SEARCHSPATIALPOINT_DLG_IDNAME,
						   const wxString& caption = SYMBOL_SEARCHSPATIALPOINT_DLG_TITLE,
						   const wxPoint& pos = SYMBOL_SEARCHSPATIALPOINT_DLG_POSITION,
						   const wxSize& size = SYMBOL_SEARCHSPATIALPOINT_DLG_SIZE, 
						   long style = SYMBOL_SEARCHSPATIALPOINT_DLG_STYLE );
   ~SEARCHSPATIALPOINT_DLG();
	
    bool Create( wxWindow* parent, 
				wxWindowID id = SYMBOL_SEARCHSPATIALPOINT_DLG_IDNAME,
				const wxString& caption = SYMBOL_SEARCHSPATIALPOINT_DLG_TITLE,
				const wxPoint& pos = SYMBOL_SEARCHSPATIALPOINT_DLG_POSITION, 
				const wxSize& size = SYMBOL_SEARCHSPATIALPOINT_DLG_SIZE, 
				long style = SYMBOL_SEARCHSPATIALPOINT_DLG_STYLE );

	bool OpenDBGISData (const wxString & dbname, const wxString & table);
	

    void Init();

    void CreateControls();


    wxStaticText* m_DLGSS_Map_Xmin;
    wxStaticText* m_DLGSS_Map_Xmax;
    wxStaticText* m_DLGSS_Map_Ymin;
    wxStaticText* m_DLGSS_Map_Ymax;
    wxTextCtrl* m_DLGSS_coord_x;
    wxTextCtrl* m_DLGSS_coord_y;
    wxSlider* m_DLGSS_buffer;
    wxStaticText* m_DLGSS_result_index;
    wxStaticText* m_DLGSS_result_index_tm;
    wxStaticText* m_DLGSS_result_status;
    wxStaticText* m_DLGSS_result_status_tm;
};

#endif

