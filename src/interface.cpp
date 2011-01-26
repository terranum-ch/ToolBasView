/*!
@file interface.cpp
@brief  code of sizer function for the interface.
@author Lucien Schreiber (c) CREALP 2007
*/


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "../include/interface.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "../include/interface.h"
#include "../art/toolbasview_bmp.h"

#include <wx/intl.h>

// Euro sign hack of the year
#if wxUSE_UNICODE
    #define __WDR_EURO__ wxT("\u20ac")
#else
    #if defined(__WXMAC__)
        #define __WDR_EURO__ wxT("\xdb")
    #elif defined(__WXMSW__)
        #define __WDR_EURO__ wxT("\x80")
    #else
        #define __WDR_EURO__ wxT("\xa4")
    #endif
#endif



/*!
    @brief   used to create the main interface
    @param      (name) (description)
    @results     wxSizer *
*/
wxSizer *INTERFACE( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxSplitterWindow *item2 = new wxSplitterWindow( parent, ID_LEFT_SPLIT, wxDefaultPosition, wxSize(200,160), wxSP_LIVE_UPDATE|wxNO_BORDER );
    item0->Add( item2, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxPanel * Leftwindow = new wxPanel(item2,-1);
	LEFT(Leftwindow,FALSE);
	item2->Initialize(Leftwindow);
	
	Leftwindow->Show(true);
	
	wxPanel * Rightwindow = new wxPanel(item2,-1);
	RIGHT(Rightwindow,FALSE);
	item2->Initialize(Rightwindow);
	Rightwindow->Show(true);
	
	item2->SplitVertically (Leftwindow,Rightwindow,150);
	item2->SetMinimumPaneSize(150);
    item2->SetSashSize(4);
    item2->SetSashGravity(0.1);

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


wxSizer *LEFT( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxTreeCtrl *item1 = new wxTreeCtrl( parent, ID_LISTTABLE, wxDefaultPosition, wxSize(120,160), wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxBORDER_NONE );
    item0->Add( item1, 1, wxGROW | wxALIGN_CENTER, 5 );
	
    
    wxPanel* m_panel1;
	m_panel1 = new wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxBORDER_THEME );
	//m_panel1->SetBackgroundColour( *wxWHITE );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxGenericStaticBitmap* m_bitmap1 = new wxGenericStaticBitmap( m_panel1, wxID_ANY, *_img_mysql , wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bitmap1, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel1->SetSizer( bSizer3 );
	m_panel1->Layout();
	bSizer3->Fit( m_panel1 );
	item0->Add( m_panel1, 0, wxEXPAND, 5 );
	
    
	if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


wxSizer *RIGHT( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxSplitterWindow *item1 = new wxSplitterWindow( parent, ID_RIGHT_SPLIT, wxDefaultPosition, wxSize(200,160), wxSP_LIVE_UPDATE|wxNO_BORDER);
    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxPanel * TopWindow = new wxPanel(item1,-1);
	RIGHT_TOP(TopWindow,FALSE);
	item1->Initialize(TopWindow);
	
	TopWindow->Show(true);
	
	wxPanel * BottomWindow = new wxPanel(item1,-1);
	RIGHT_BTM(BottomWindow,FALSE);
	item1->Initialize(BottomWindow);
	BottomWindow->Show(true);
	
	item1->SplitHorizontally (TopWindow,BottomWindow,200);
	item1->SetMinimumPaneSize(20);
    item1->SetSashGravity(0.7); // Resize only top panel
    item1->SetSashSize(4);
    //item1->SetSashPosition(200, true);

	
	if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


wxSizer *RIGHT_TOP( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
    
    wxGrid *item1 = new wxGrid( parent, ID_GRID, wxDefaultPosition, wxSize(200,160), wxWANTS_CHARS );
    item1->CreateGrid( 10, 10, wxGrid::wxGridSelectCells );
    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


wxSizer *RIGHT_BTM( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    //wxStaticText *item1 = new wxStaticText( parent, ID_TEXT, _("Logging Console"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    //item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5 );

    wxTextCtrl *item2 = new wxTextCtrl( parent, ID_LOG, _("Log:\n"), wxDefaultPosition, wxSize(80,80), wxTE_MULTILINE );
    item0->Add( item2, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


;
wxMenuBar *MENU()
{
    wxMenuBar *item0 = new wxMenuBar;
    
    wxMenu* item1 = new wxMenu;
	item1->Append(ID_NEW_DBASE,_("Create new database...\tCtrl-N"),_("Display the dialog box for creating new database"));
    item1->Append( ID_OPEN_DB, _("Open database...\tCtrl-O"), _("Display the dialog box for selecting the database to open") );
    item1->Append( ID_MENU_STATISTICS, _("Database statistics...\tCtrl-I"), _("Display the statistics from the opened database") );
	item1->AppendSeparator();
    item1->Append( wxID_EXIT, _("Exit program"), _("Quit the program") );
    item0->Append( item1, _("File") );
    
    wxMenu* item2 = new wxMenu;
    item2->Append( ID_PROCESS_MENU, _("Process SQL Request...\tCtrl-P"), _("Allow user to edit a personalized SQL request") );
    item2->Append( ID_MENU_SPATIAL_ADD, _("Add spatial data into the database...\tCtrl-S"), 
				  _("Allow user to load spatial data into a database table (SHP)") );
	item2->Append( ID_MENU_SPATIAL_SEARCH, _("Search spatial data...\tCtrl-F"), 
				  _("Search spatial data used for benchmark") );
	item2->AppendSeparator();
	item2->Append( ID_MENU_DELETE, _("Delete data from database...\tCtrl-Del"), 
				  _("Dialog for deleting data from the database") );

    item0->Append( item2, _("Operations") );
    
	wxMenu* item3 = new wxMenu;
    item3->Append( wxID_ABOUT, _("About..."), _("Show the about dialog") );
    item0->Append( item3, _("Help") );
	
    return item0;
}


