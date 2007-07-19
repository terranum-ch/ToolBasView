/*!
    @file dialogs.cpp
    @brief declaration of ressources dialogs
*/

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "../include/dialogs_wdr.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "../include/dialogs.h"


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

// Implement window functions

wxSizer *SQLPROCESS( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxTextCtrl *item1 = new wxTextCtrl( parent, ID_TEXTCTRL, wxT(""), wxDefaultPosition, wxSize(80,40), wxTE_MULTILINE );
    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item2 = new wxStaticText( parent, ID_REQUEST_RESULT, wxT("Result :"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticLine *item3 = new wxStaticLine( parent, ID_LINE, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item0->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxBoxSizer *item4 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item5 = new wxButton( parent, ID_PROCESS, wxT("Process Request"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item5, 1, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxButton *item6 = new wxButton( parent, wxID_CANCEL, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
    item6->SetDefault();
    item4->Add( item6, 1, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    item0->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

wxSizer *ABOUT( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item1 = new wxStaticText( parent, ID_ABOUT_TEXT, 
        wxT("ToolBasView\n")
        wxT("A small tool used to open\n")
        wxT("enbedded MySQL Databases\n")
        wxT("\n")
        wxT("(c) Lucien Schreiber CREALP 2007"),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item2 = new wxStaticText( parent, ID_SQL_BMP, "No image", wxDefaultPosition, wxDefaultSize );
    item0->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticLine *item3 = new wxStaticLine( parent, ID_LINE, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item0->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item4 = new wxButton( parent, wxID_YES, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

