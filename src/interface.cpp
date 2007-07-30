/*!
    @header interface.cpp
    @abstract   describ file for interface
    @discussion this file is used to build the interface.
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


const int ID_LEFT_SPLIT = wxNewId();


/*!
    @function	INTERFACE
    @abstract   used to create the main interface
    @discussion (description)
    @param      (name) (description)
    @result     wxSizer *
*/
wxSizer *INTERFACE( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxSplitterWindow *item2 = new wxSplitterWindow( parent, ID_LEFT_SPLIT, wxDefaultPosition, wxSize(200,160), wxSP_BORDER|wxSP_3D|wxCLIP_CHILDREN );
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
	item2->SetMinimumPaneSize(20);

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


const int ID_LISTTABLE = wxNewId();
wxSizer *LEFT( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxTreeCtrl *item1 = new wxTreeCtrl( parent, ID_LISTTABLE, wxDefaultPosition, wxSize(120,160), wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxSUNKEN_BORDER );
    item0->Add( item1, 1, wxGROW | wxALIGN_CENTER, 5 );
	
	
    
	if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

const int ID_RIGHT_SPLIT = wxNewId();
wxSizer *RIGHT( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxSplitterWindow *item1 = new wxSplitterWindow( parent, ID_RIGHT_SPLIT, wxDefaultPosition, wxSize(200,160), wxSP_BORDER|wxSP_3D|wxCLIP_CHILDREN );
    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxPanel * TopWindow = new wxPanel(item1,-1);
	RIGHT_TOP(TopWindow,FALSE);
	item1->Initialize(TopWindow);
	
	TopWindow->Show(true);
	
	wxPanel * BottomWindow = new wxPanel(item1,-1);
	RIGHT_BTM(BottomWindow,FALSE);
	item1->Initialize(BottomWindow);
	BottomWindow->Show(true);
	
	item1->SplitHorizontally (TopWindow,BottomWindow,300);
	item1->SetMinimumPaneSize(20);

	
	if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

const int ID_GRID = wxNewId();
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

const int ID_TEXT = wxNewId();
const int ID_LOG = wxNewId();
wxSizer *RIGHT_BTM( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item1 = new wxStaticText( parent, ID_TEXT, _("Logging Console"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5 );

    wxTextCtrl *item2 = new wxTextCtrl( parent, ID_LOG, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_MULTILINE );
    item0->Add( item2, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


const int ID_OPEN_DB = wxNewId();
const int ID_MENU = wxNewId();
const int ID_FILE_MENU = wxNewId();
const int ID_PROCESS_MENU = wxNewId();
const int ID_OP_MENU = wxNewId();
const int ID_NEW_DBASE = wxNewId();
const int ID_MENU_STATISTICS = wxNewId();
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
    item0->Append( item2, _("Operations") );
    
	wxMenu* item3 = new wxMenu;
    item3->Append( wxID_ABOUT, _("About..."), _("Show the about dialog") );
    item0->Append( item3, _("Help") );
	
    return item0;
}


