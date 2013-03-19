/***************************************************************************
 resultsframe.h
 -------------------
 copyright            : (C) 2013 CREALP Lucien Schreiber
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
#ifndef _RESULTSFRAME_H_
#define _RESULTSFRAME_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/grid.h>
#include <wx/aui/aui.h>
#include <wx/artprov.h>
#include <wx/display.h>

const int ID_EXPORT_EXCEL = wxID_HIGHEST + 17;
const int ID_AUTOSIZE_COLUMN = wxID_HIGHEST + 18;


class Results_DLG : public wxFrame{
private:
    wxGrid* m_GridCtrl;
    wxTextCtrl* m_QueryCtrl;
    wxAuiManager m_mgr;
    

    
    void _CreateControls();
    void _SetRandomPosition();
	
    // events
    void OnCloseResults( wxCloseEvent& event );
    void OnMenuCopy( wxCommandEvent& event );
    void OnMenuExport( wxCommandEvent& event );
    void OnMenuAutosize( wxCommandEvent& event ) ;
    void OnMenuClose( wxCommandEvent& event );
    void OnUpdateUICopy( wxUpdateUIEvent& event ) ;
    void OnUpdateUIAutosize( wxUpdateUIEvent& event ) ;
    void OnUpdateUIExport( wxUpdateUIEvent& event );
    DECLARE_EVENT_TABLE()

    
public:
    Results_DLG( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxSize( 600,480 ),
                long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
    ~Results_DLG();
	
};



#endif
