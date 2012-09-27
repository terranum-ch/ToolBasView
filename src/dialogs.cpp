/*!
    @file dialogs.h
    @brief code of ressources dialogs
    @author Lucien Schreiber (c) CREALP 2007
*/

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "../include/dialogs.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "dialogs.h"




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

    wxTextCtrl *item1 = new wxTextCtrl( parent, ID_TEXTCTRL, wxT(""), wxDefaultPosition, wxSize(600,200), wxTE_MULTILINE );
    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL| wxALL, 5 );

	
    wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( parent, wxID_ANY, _("Results") ), wxHORIZONTAL );
	
	wxStaticText* m_staticText1;
	m_staticText1 = new wxStaticText( parent, ID_REQUEST_RESULT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_staticText1, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxButton* m_button1;
	m_button1 = new wxButton( parent, ID_BTN_SHOWRESULTS, _("Show results..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_button1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
    m_button1->Enable(false);
	
	//bSizer1->Add( sbSizer1, 1, wxEXPAND|wxALL, 5 );
    item0->Add(sbSizer1, 0, wxEXPAND|wxALL, 5 );
    wxBoxSizer *item5 = new wxBoxSizer( wxHORIZONTAL );
    
    wxButton *item61 = new wxButton( parent, ID_HISTORY, _("History..."), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item61, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
    
    wxButton *item6 = new wxButton( parent, ID_PROCESS, _("Execute SQL Code"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxButton *item7 = new wxButton( parent, wxID_CANCEL, _("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
    item7->SetDefault();
    item5->Add( item7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    item0->Add( item5, 0, wxALL| wxALIGN_RIGHT, 5 );

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
        _("ToolBasView\n A small tool used to open\nembedded MySQL Databases\n\n(c) Lucien Schreiber CREALP 2008"),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticBitmap *item2 = new wxStaticBitmap( parent, ID_SQL_BMP, *_img_mysql, wxDefaultPosition, wxDefaultSize );
    item0->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticLine *item3 = new wxStaticLine( parent, ID_LINE, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item0->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item4 = new wxButton( parent, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}


wxSizer *NEWDBASE( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxStaticBox *item2 = new wxStaticBox( parent, -1, _("New database properties") );
    wxStaticBoxSizer *item1 = new wxStaticBoxSizer( item2, wxHORIZONTAL );

    wxFlexGridSizer *item3 = new wxFlexGridSizer( 3, 0, 0 );
    item3->AddGrowableCol( 1 );

    wxStaticText *item4 = new wxStaticText( parent, ID_TEXT2, _("Database Path :"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item5 = new wxTextCtrl( parent, ID_TXT_DB_PATH, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item6 = new wxButton( parent, ID_BTN_CHOOSE_PATH, _("..."), wxDefaultPosition, wxSize(40,-1), 0 );
    item3->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item7 = new wxStaticText( parent, ID_TEXT2, _("Database Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item8 = new wxTextCtrl( parent, ID_TXT_DB_NAME, wxT(""), wxDefaultPosition, wxSize(300,-1), 0 );
    item3->Add( item8, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item1->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item1, 0, wxALIGN_CENTER|wxALL, 5 );

    wxBoxSizer *item9 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item10 = new wxButton( parent, wxID_OK, _("Create new database"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item11 = new wxButton( parent, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->SetDefault();
    item9->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item9, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}



wxSizer *SHOWRESULT( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxGrid *item1 = new wxGrid( parent, ID_GRID_PROCESS, wxDefaultPosition, wxSize(200,160), wxWANTS_CHARS );
    item1->CreateGrid( 10, 10, wxGrid::wxGridSelectCells );
    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxButton* m_button1;
	m_button1 = new wxButton( parent, wxID_COPY, _("Copy Results"));
	bSizer2->Add( m_button1, 0, wxALL, 5 );
	
	wxButton* m_button2;
	m_button2 = new wxButton( parent, wxID_CANCEL, _("Exit Results"));
	bSizer2->Add( m_button2, 0, wxALL, 5 );
	
	item0->Add( bSizer2, 0, wxALIGN_RIGHT | wxALL, 5 );
	

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

/*IMPLEMENT_CLASS (AboutDialog,wxDialog);
AboutDialog::AboutDialog (wxWindow*,const wxChar* ,  int,int)
{
	wxLogMessage (_("Coucuo"));

}

//AboutDialog::~AboutDialog()
//{
//	wxLogMessage (_("Coucuo"));
//	Destroy();
//}*/
