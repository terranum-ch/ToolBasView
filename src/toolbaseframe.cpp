/*!
@file main.cpp
@brief   definition of TBVApp and TBVFrame Class
@author Lucien Schreiber (c) CREALP 2007
*/

#include "toolbaseframe.h"
#include "exportcsv_dlg.h"
#include "databaseoperation.h"
#include "dlg_operation.h" // for dialogs operations.
#include "resultsframe.h"
#include "toolbasview_bmp.h"
#include "results_bmp.h"
#include "querylisttree.h"
#include "changecolumn_dlg.h"
#include "version_param.h"


BEGIN_EVENT_TABLE (TBVFrame, wxFrame)
EVT_MENU (wxID_EXIT, TBVFrame::OnMenuExit)
EVT_MENU (wxID_ABOUT, TBVFrame::OnAbout)
EVT_MENU (wxID_OPEN,TBVFrame::OnOpenDatabase)
EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, TBVFrame::OnOpenRecentDatabase)
EVT_MENU (ID_MENU_SHOW_LOG, TBVFrame::OnShowLogPanel)
EVT_CLOSE(TBVFrame::OnQuit)
EVT_TREE_ITEM_ACTIVATED (ID_LISTTABLE,TBVFrame::OnDoubleClickListe)
EVT_MENU (ID_MENU_SHOW_QUERYPANEL,TBVFrame::OnShowProcessRequest)
EVT_MENU (wxID_NEW,TBVFrame::OnNewDataBase)
EVT_MENU (ID_MENU_STATISTICS,TBVFrame::OnDisplayStatistics)
EVT_MENU (ID_MENU_SPATIAL_ADD,TBVFrame::OnSpatialDataAdd)
EVT_MENU (ID_MENU_MANIP_DELETE, TBVFrame::OnDeleteData)
EVT_MENU (ID_MENU_SPATIAL_SEARCH, TBVFrame::OnSpatialDataSearch )
EVT_MENU(ID_MENU_EXPORT_TXT, TBVFrame::OnExportData)
EVT_MENU(ID_MENU_MAINTENANCE, TBVFrame::OnDatabaseOperation)
EVT_MENU(ID_MENU_EXPORT_DUMPCLIPBOARD, TBVFrame::OnExportStructureToClipboard)
EVT_MENU(ID_MENU_AUTOSIZE_COLUMNS, TBVFrame::OnColumnSize)
EVT_MENU(ID_MENU_IMPORT_SQL, TBVFrame::OnProcessSQLFile)
EVT_MENU(ID_MENU_IMPORT_TXT, TBVFrame::OnImportTXTFile)
EVT_MENU(ID_MENU_MANIP_CHANGE_COL_TYPE, TBVFrame::OnChangeColumnType)
EVT_MENU(ID_MENU_WEB_MYSQL, TBVFrame::OnMySQLReference)

EVT_UPDATE_UI(ID_MENU_STATISTICS, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_SPATIAL_ADD, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_MANIP_DELETE, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_SPATIAL_SEARCH, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_EXPORT_TXT, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_MAINTENANCE, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_EXPORT_DUMPCLIPBOARD, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_AUTOSIZE_COLUMNS, TBVFrame::OnUpdateUIAutosize)
EVT_UPDATE_UI(ID_BTN_ADD_TO_LIST, TBVFrame::OnUpdateUIAddToList)
EVT_UPDATE_UI(ID_MENU_IMPORT_SQL, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_IMPORT_TXT, TBVFrame::OnUpdateUIDatabaseOpen)
EVT_UPDATE_UI(ID_MENU_MANIP_CHANGE_COL_TYPE, TBVFrame::OnUpdateUIDatabaseOpen)

EVT_BUTTON(ID_BTN_HISTORY, TBVFrame::OnBtnHistory)
EVT_BUTTON(ID_BTN_RUN, TBVFrame::OnBtnRun)
EVT_BUTTON(ID_BTN_SHOW_RESULTS, TBVFrame::OnBtnShowResults)
EVT_BUTTON(ID_BTN_ADD_TO_LIST, TBVFrame::OnAddToList)

EVT_TREE_ITEM_ACTIVATED(ID_QUERY_LIST_TREE, TBVFrame::OnTreeItemDoubleClick)
EVT_SYS_COLOUR_CHANGED(TBVFrame::OnSysColourChanged)

EVT_UPDATE_UI(ID_BTN_RUN, TBVFrame::OnUpdateUIBtnRun)
EVT_UPDATE_UI(ID_BTN_SHOW_RESULTS, TBVFrame::OnUpdateUIBtnShowResults)
EVT_UPDATE_UI(ID_BTN_HISTORY, TBVFrame::OnUpdateUIBtnHistory)

END_EVENT_TABLE()


/* Frame initialisation */
TBVFrame::TBVFrame(wxFrame *frame, const wxString& title,wxPoint pos, wxSize size): wxFrame(frame, -1, title,pos,size){
    
    m_ConfigFile = new wxFileConfig("toolbasview", "CREALP");
    
    wxInitAllImageHandlers();
    initialize_images();
    results_initialize_images();
    
    // Loading icon
	wxIcon myIcon;
    myIcon.CopyFromBitmap(*_img_toolbasview);
    SetIcon(myIcon);
	
    // adding status bar
	CreateStatusBar(2);
    SetStatusBarPane(-1);
    _CreateControls();
    _CreateMenu();
    _CreateToolBar();
    
    
    m_ImgList= new wxImageList(16,16);
    m_ImgList->Add(*_img_database_small);
    m_ImgList->Add(*_img_table_sml);
    m_TreeCtrl->SetImageList(m_ImgList);
	
	// define as log window
	wxLog::SetActiveTarget (new wxLogTextCtrl (m_LogCtrl));
	wxLogMessage(_("Program started"));
	
	// loading GDAL 
	OGRRegisterAll();
	wxLogMessage(_T("All GDAL driver registered..."));
	m_GridOp = new GridOperation(m_GridCtrl);
    
    // loading history
    m_HistoryFileName = wxFileName(wxStandardPaths::Get().GetAppDocumentsDir(), _T("toolbasview_history.txt"));
  	wxTextFile myHistoryFile (m_HistoryFileName.GetFullPath());
    if(m_HistoryFileName.Exists() == false){
        myHistoryFile.Create();
    }
    else{
        myHistoryFile.Open();
    }
    m_History.Clear();
    for (wxString str = myHistoryFile.GetFirstLine(); !myHistoryFile.Eof(); str = myHistoryFile.GetNextLine() ){
        m_History.Add(str);
    }
    
    // loading querylist
    m_QueryListFileName = wxFileName(wxStandardPaths::Get().GetAppDocumentsDir(), _("toolbasview_querylist.txt"));
    m_QueryListTreeCtrl->Load(m_QueryListFileName);
}



void TBVFrame::_CreateControls(){
    wxPanel* m_mainpanel;
    wxPanel* m_tocpanel;
    wxPanel* m_logpanel;
    
    
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_mainpanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_mainpanel, wxAuiPaneInfo() .Name( wxT("main") ).Left() .CaptionVisible( false ).CloseButton( false ).PinButton( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_GridCtrl = new wxGrid( m_mainpanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_GridCtrl->CreateGrid( 50, 5);
	m_GridCtrl->EnableEditing( true );
	m_GridCtrl->EnableGridLines( true );
	m_GridCtrl->EnableDragGridSize( false );
	m_GridCtrl->SetMargins( 0, 0 );
    
	// Columns
	m_GridCtrl->EnableDragColMove( false );
	m_GridCtrl->EnableDragColSize( true );
	m_GridCtrl->SetColLabelSize( 30 );
	m_GridCtrl->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_GridCtrl->EnableDragRowSize( true );
	m_GridCtrl->SetRowLabelSize( 80 );
	m_GridCtrl->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_GridCtrl->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer5->Add( m_GridCtrl, 1, wxEXPAND, 5 );
	
        
	
	m_mainpanel->SetSizer( bSizer5 );
	m_mainpanel->Layout();
	bSizer5->Fit( m_mainpanel );

    
	m_tocpanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_tocpanel, wxAuiPaneInfo() .Name( wxT("toc") ).Left() .Caption( wxT("Table of content") ).CloseButton( false ).Dock().Resizable().FloatingSize( wxSize( -1,-1 ) ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).Floatable( false ).BestSize( wxSize( 200,-1 ) ).MinSize( wxSize( 100,-1 ) ).Layer( 1 ) );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_TreeCtrl = new wxTreeCtrl( m_tocpanel, ID_LISTTABLE, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer4->Add( m_TreeCtrl, 1, wxEXPAND, 5 );
	
	wxStaticBitmap* m_bitmap2 = new wxStaticBitmap( m_tocpanel, wxID_ANY, *_img_mysql , wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_bitmap2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
    
    m_mgr.GetPane(_T("toc")).MinSize(-1, m_bitmap2->GetSize().GetWidth());
	
	m_VersionTxtCtrl = new wxStaticText( m_tocpanel, wxID_ANY, _("Version: ") + DataBase::DataBaseGetVersion(), wxDefaultPosition, wxDefaultSize, 0 );
	m_VersionTxtCtrl->Wrap( -1 );
	bSizer4->Add( m_VersionTxtCtrl, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_tocpanel->SetSizer( bSizer4 );
	m_tocpanel->Layout();
	bSizer4->Fit( m_tocpanel );
	m_querypanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_querypanel, wxAuiPaneInfo() .Name( wxT("query") ).Bottom() .Caption( wxT("Query") ).CloseButton( false ).MaximizeButton(true).PinButton( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).Row( 1 ).Position( 0 ).BestSize( wxSize( -1,0 ) ).Layer( 0 ) );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_QueryTxtCtrl = new wxStyledTextCtrl( m_querypanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    m_QueryTxtCtrl->StyleClearAll();
    m_QueryTxtCtrl->SetLexer(wxSTC_LEX_SQL);
    m_QueryTxtCtrl->StyleSetForeground (wxSTC_SQL_STRING,            wxColour(150,0,0));
    
    // comments
    wxColourDatabase myDb;
    wxColour myCommentColour = myDb.Find(_T("FOREST GREEN"));
    m_QueryTxtCtrl->StyleSetForeground (wxSTC_SQL_COMMENT, myCommentColour);
    m_QueryTxtCtrl->StyleSetForeground (wxSTC_SQL_COMMENTDOC,        myCommentColour);
    m_QueryTxtCtrl->StyleSetForeground (wxSTC_SQL_COMMENTDOCKEYWORD,        myCommentColour);
    m_QueryTxtCtrl->StyleSetForeground (wxSTC_SQL_COMMENTLINE,        myCommentColour);
    m_QueryTxtCtrl->StyleSetForeground (wxSTC_SQL_COMMENTLINEDOC,       myCommentColour);
    m_QueryTxtCtrl->StyleSetForeground (wxSTC_SQL_COMMENTDOCKEYWORDERROR,       myCommentColour);
    m_QueryTxtCtrl->StyleSetBold(wxSTC_SQL_COMMENTDOCKEYWORD, true);
    
    // code
    m_QueryTxtCtrl->StyleSetForeground(wxSTC_SQL_WORD, *wxBLUE);
    m_QueryTxtCtrl->StyleSetForeground(wxSTC_SQL_WORD2, *wxBLUE);
    m_QueryTxtCtrl->StyleSetBold(wxSTC_SQL_WORD, true);
    m_QueryTxtCtrl->StyleSetBold(wxSTC_SQL_WORD2, true);
    
    m_QueryTxtCtrl->SetKeyWords(0, _T("accessible add all alter analyze and as asc asensitive before between bigint binary blob both by call cascade case change char character check collate column condition constraint continue convert create cross current_date current_time current_timestamp current_user cursor database databases day_hour day_microsecond day_minute day_second dec decimal declare default delayed delete desc describe deterministic distinct distinctrow div double drop dual each else elseif enclosed escaped exists exit explain false fetch float float4 float8 for force foreign from fulltext general grant group having high_priority hour_microsecond hour_minute hour_second if ignore ignore_server_ids in index infile inner inout insensitive insert int int1 int2 int3 int4 int8 integer interval into is iterate join key keys kill leading leave left like limit linear lines load localtime localtimestamp lock long longblob longtext loop low_priority master_heartbeat_period master_ssl_verify_server_cert match maxvalue mediumblob mediumint mediumtext middleint minute_microsecond minute_second mod modifies natural not no_write_to_binlog null numeric on optimize option optionally or order out outer outfile precision primary procedure purge range read reads read_write real references regexp release rename repeat replace require resignal restrict return revoke right rlike schema schemas second_microsecond select sensitive separator set show signal slow[d] smallint spatial specific sql sqlexception sqlstate sqlwarning sql_big_result sql_calc_found_rows sql_small_result ssl starting straight_join table terminated then tinyblob tinyint tinytext to trailing trigger true undo union unique unlock unsigned update usage use using utc_date utc_time utc_timestamp values varbinary varchar varcharacter varying when where while with write xor year_month zerofill   general ignore_server_ids master_heartbeat_period maxvalue resignal signal slow"));
    
    m_QueryTxtCtrl->SetMarginWidth(0, 30);
    m_QueryTxtCtrl->SetMarginWidth(1, 0);
    m_QueryTxtCtrl->SetMarginType(0, 1);
    
	bSizer6->Add( m_QueryTxtCtrl, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_QueryRunCtrl = new wxButton( m_querypanel, ID_BTN_RUN, _("Run"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_QueryRunCtrl, 0, wxALL, 5 );
	
	m_QueryShowCtrl = new wxButton( m_querypanel, ID_BTN_SHOW_RESULTS, _("Show Results..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_QueryShowCtrl, 0, wxALL, 5 );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
    m_AddToListBtnCtrl = new wxButton( m_querypanel, ID_BTN_ADD_TO_LIST, _("Add to List..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_AddToListBtnCtrl, 0, wxALL, 5 );
    
	m_QueryHistoryCtrl = new wxButton( m_querypanel, ID_BTN_HISTORY, _("History..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_QueryHistoryCtrl, 0, wxALL, 5 );
	
	
	bSizer6->Add( bSizer7, 0, wxEXPAND, 5 );
	
	
	m_querypanel->SetSizer( bSizer6 );
	m_querypanel->Layout();
	bSizer6->Fit( m_querypanel );
	m_logpanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_logpanel, wxAuiPaneInfo() .Name( wxT("log") ).Bottom() .Caption( wxT("Log") ).CloseButton( false ).PinButton( false ).MaximizeButton(true).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).Row( 0 ).BestSize( wxSize( -1,0 ) ) );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_LogCtrl = new wxTextCtrl( m_logpanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer8->Add( m_LogCtrl, 1, wxEXPAND, 5 );
	
	
	m_logpanel->SetSizer( bSizer8 );
	m_logpanel->Layout();
	bSizer8->Fit( m_logpanel );
    
    m_QueryListPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_QueryListPanel, wxAuiPaneInfo() .Name( wxT("querylist") ).Right() .Caption( wxT("Query List") ).CloseButton( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).BestSize( wxSize( 200,-1 ) ) );
	
	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxVERTICAL );
	
	m_QueryListTreeCtrl = new QueryListTree( m_QueryListPanel, ID_QUERY_LIST_TREE, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_EDIT_LABELS|wxTR_HIDE_ROOT );
	bSizer61->Add( m_QueryListTreeCtrl, 1, wxEXPAND, 5 );
	
	
	m_QueryListPanel->SetSizer( bSizer61 );
	m_QueryListPanel->Layout();
	bSizer61->Fit( m_QueryListPanel );
    
	m_mgr.Update();
	this->Centre( wxBOTH );
    
    this->Bind(wxEVT_AUI_PANE_MAXIMIZE, &TBVFrame::OnAuiButtonPressed, this, wxID_ANY);
    
    
    // update cols width
    int myWidth = m_GridCtrl->GetClientSize().GetWidth() - 80;
    int myColWidth = wxRound(myWidth / m_GridCtrl->GetNumberCols());
    for (int i = 0; i< m_GridCtrl->GetNumberCols(); i++) {
        m_GridCtrl->SetColSize(i, myColWidth);
    }
}



void TBVFrame::_CreateMenu(){
    wxMenuBar *myMenuBar = new wxMenuBar;
    
    // FILE
    wxMenu* item1 = new wxMenu;
	item1->Append( wxID_NEW,_("Create...\tCtrl-N"));
    item1->Append( wxID_OPEN, _("Open...\tCtrl-O"));
    
    wxMenu* recentmenu = new wxMenu();
    item1->AppendSubMenu(recentmenu, _("Recent"));
    
    m_FileHist.UseMenu(recentmenu);
    m_FileHist.AddFilesToMenu(recentmenu);

    // load configuration
    wxASSERT(m_ConfigFile);
    m_FileHist.Load(*m_ConfigFile);
    
    item1->AppendSeparator();
    item1->Append(ID_MENU_MAINTENANCE, _("Maintenance..."));
    item1->Append( ID_MENU_STATISTICS, _("Statistics..."));
#ifndef __WXMAC__
    item1->AppendSeparator();
#endif
    item1->Append( wxID_EXIT );
    myMenuBar->Append( item1, _("File") );
    
    
    // DATA
    wxMenu* item2 = new wxMenu;
    wxMenu* import_menu = new wxMenu();
    import_menu->Append(ID_MENU_IMPORT_TXT, _("From TXT...\tCtrl+Alt+I"));
    import_menu->Append(ID_MENU_IMPORT_SQL, _("From SQL...\tCtrl+Alt+P"));
    item2->AppendSubMenu(import_menu, _("Import"));
    
    wxMenu* export_menu = new wxMenu();
    export_menu->Append(ID_MENU_EXPORT_TXT, _("To TXT...\tCtrl+Alt+E"));
    export_menu->Append(ID_MENU_EXPORT_DUMPCLIPBOARD, _("Structure to clipboard\tCtrl+Alt+D"));
    item2->AppendSubMenu(export_menu, _("Export"));
    
    item2->AppendSeparator();
    
    wxMenu* manipulation_menu = new wxMenu();
    manipulation_menu->Append(ID_MENU_MANIP_CHANGE_COL_TYPE, _("Change column type...\tCtrl+M"));
    manipulation_menu->Append(ID_MENU_MANIP_DELETE, _("Delete data...\tCtrl+Del"));
    item2->AppendSubMenu(manipulation_menu, _("Manipulation"));
    myMenuBar->Append( item2, _("Data") );

    
    // SPATIAL
    wxMenu * spatial_menu = new wxMenu();
    spatial_menu->Append(ID_MENU_SPATIAL_ADD, _("Add spatial data..."));
    spatial_menu->Append(ID_MENU_SPATIAL_SEARCH, _("Search spatial data..."));
    myMenuBar->Append(spatial_menu, _("Spatial"));
    
    
    // VIEW
    wxMenu * view_menu = new wxMenu();
    view_menu->Append(ID_MENU_SHOW_QUERYPANEL, _("Show query panel\tCtrl+P"));
    view_menu->Append(ID_MENU_SHOW_LOG, _("Show log panel\tCtrl+L"));
    view_menu->AppendSeparator();
    view_menu->Append(ID_MENU_AUTOSIZE_COLUMNS, _("Autosize columns"));
    myMenuBar->Append(view_menu, _("View"));

   
    /*
    item1->Append( wxID_SAVEAS, _("Export as CSV...\tCtrl-Alt-E"), _("Select and Export data as CSV.") );
    item1->Append(ID_MENU_EXPORT_STRUCTURE, _("Dump to Clipboard...\tCtrl+D"));
    item1->AppendSeparator();
    
   
    wxMenu* item2 = new wxMenu;
    item2->Append( ID_PROCESS_MENU, _("Show Process Query...\tCtrl-P"), _("Allow user to edit a personalized SQL request") );
    item2->Append(ID_MENU_SHOW_LOG, _("Show Log panel\tCtrl+L"), _("Show the log panel"));
    item2->AppendSeparator();
    item2->Append( ID_MENU_SPATIAL_ADD, _("Add spatial data into the database...\tCtrl-S"), _("Allow user to load spatial data into a database table (SHP)") );
	item2->Append( ID_MENU_SPATIAL_SEARCH, _("Search spatial data...\tCtrl-F"), _("Search spatial data used for benchmark") );
    item2->Append(ID_MENU_PROCESS_SQL_FILE, _("Process SQL file...\tCtrl+Alt+P"), wxEmptyString);
	item2->AppendSeparator();
	item2->Append( ID_MENU_DELETE, _("Delete data from database...\tCtrl-Del"),_("Dialog for deleting data from the database") );
    item2->AppendSeparator();
    item2->Append(ID_MENU_AUTOSIZE_COLUMNS, _("Autosize columns"), _("Autosize columns"));
    */
    
    // HELP
	wxMenu* item3 = new wxMenu;
    item3->Append(wxID_ABOUT, _("About..."));
    item3->Append(ID_MENU_WEB_MYSQL, _("MySQL web references..."));
    myMenuBar->Append( item3, _("Help") );
    SetMenuBar(myMenuBar);
}


void TBVFrame::_CreateToolBar(){
	long style = wxTB_FLAT | wxTB_HORIZONTAL;
#ifndef __WXMSW__
	style += wxTB_TEXT;
#endif

    wxToolBar* m_toolBar1 = this->CreateToolBar( style, wxID_ANY );
	m_toolBar1->SetToolBitmapSize(wxSize(32,32));
    wxString myText = _("New database");
	m_toolBar1->AddTool( wxID_NEW, myText, *_img_database_new, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
    myText = _("Open database");
    m_toolBar1->AddTool( wxID_OPEN, myText, *_img_database_open, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
    
    //m_toolBar1->AddSeparator();
    
    myText = _("Query panel");
    m_toolBar1->AddTool( ID_MENU_SHOW_QUERYPANEL, myText, *_img_database_process, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
    myText = _("Autosize columns");
    m_toolBar1->AddTool( ID_MENU_AUTOSIZE_COLUMNS, myText, *_img_results_autosize, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
    myText = _("Export...");
    m_toolBar1->AddTool( wxID_SAVEAS, myText, *_img_database_export, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
	_UpdateToolBarColour();
    m_toolBar1->Realize();
}


/* Frame destruction */
TBVFrame::~TBVFrame()
{
    // save query list
    m_QueryListTreeCtrl->Save (m_QueryListFileName);

    
    this->Unbind(wxEVT_AUI_PANE_MAXIMIZE, &TBVFrame::OnAuiButtonPressed, this, wxID_ANY);
    m_mgr.UnInit();
    
    // write history (limit to 1000 records)
    wxASSERT(m_HistoryFileName.Exists());
    wxTextFile myHistoryFile (m_HistoryFileName.GetFullPath());
    myHistoryFile.Open();
    myHistoryFile.Clear();
    
    for (unsigned int i = 0; i< m_History.GetCount(); i++) {
        myHistoryFile.AddLine(m_History[i]);
        if (i >= 1000) {
            break;
        }
    }
    myHistoryFile.Write();
    uninitialize_images();
    results_clean_images();
    
    wxDELETE(m_ImgList);
    
    // save configuration
    m_FileHist.Save(*m_ConfigFile);
    wxDELETE(m_ConfigFile);
}


void TBVFrame::OnOpenDatabase(wxCommandEvent & event){
	const wxString & dir = wxDirSelector (_("Choose the database folder"));
	if (dir.empty()){
		return;
    }
	
    if (_OpenDatabase(dir) == false) {
        return;
    }
    m_FileHist.AddFileToHistory(dir);
}



bool TBVFrame::_OpenDatabase (const wxString & path){
    wxFileName myDbFileName (path, "");
    
    // clear all the controls.
	ClearCtrls();
	if (myDbFileName.IsOk()==false)	{
		wxLogError(_T("Incorrect path"));
		return false;
	}
    
    wxArrayString myDirs = myDbFileName.GetDirs();
    myDbFileName.RemoveLastDir();
    
    if (m_Database.DataBaseOpen(myDbFileName.GetFullPath(wxPATH_NATIVE) , myDirs.Last()) == false) {
        wxLogError(_("Loading: %s failed!"), myDbFileName.GetFullPath());
        return false;
    }
    wxLogMessage(myDbFileName.GetFullPath());
	_LoadTablesIntoToc();
    wxLogMessage( m_Database.DataBaseGetSize());
    return true;
}


void TBVFrame::_UpdateToolBarColour(){
    // this function is only used in OSX for Dark mode support
#if defined( __WXMAC__ ) && wxOSX_USE_COCOA_OR_CARBON
    wxColor baseColour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
    if ((baseColour.Red() < 75)  //dark mode
        && (baseColour.Green() < 75)
        && (baseColour.Blue() < 75)) {
        GetToolBar()->SetToolNormalBitmap(wxID_NEW, *_img_w_database_new);
        GetToolBar()->SetToolNormalBitmap(wxID_OPEN, *_img_w_database_open);
        GetToolBar()->SetToolNormalBitmap(ID_MENU_SHOW_QUERYPANEL, *_img_w_database_process);
        GetToolBar()->SetToolNormalBitmap(ID_MENU_AUTOSIZE_COLUMNS, *_img_w_results_autosize);
        GetToolBar()->SetToolNormalBitmap(wxID_SAVEAS, *_img_w_database_export);
    }
    else{ // light mode
        GetToolBar()->SetToolNormalBitmap(wxID_NEW, *_img_database_new);
        GetToolBar()->SetToolNormalBitmap(wxID_OPEN, *_img_database_open);
        GetToolBar()->SetToolNormalBitmap(ID_MENU_SHOW_QUERYPANEL, *_img_database_process);
        GetToolBar()->SetToolNormalBitmap(ID_MENU_AUTOSIZE_COLUMNS, *_img_results_autosize);
        GetToolBar()->SetToolNormalBitmap(wxID_SAVEAS, *_img_database_export);
    }
#endif
}


void TBVFrame::OnOpenRecentDatabase (wxCommandEvent & event){
    wxString myFileNameTxt (m_FileHist.GetHistoryFile(event.GetId() - wxID_FILE1));
    if (myFileNameTxt.IsEmpty()) {
        return;
    }
    _OpenDatabase(myFileNameTxt);
}



void TBVFrame::OnDeleteData (wxCommandEvent & event)
{	
	DELETETABLEDATA_DLG myDelDlg (this, wxID_ANY, &m_Database);
	// set the active possibilities for the database
	// deleting
	myDelDlg.SetActiveFlags(DEL_FLAGS_DATA | DEL_FLAGS_TABLE);
	
	// if we choose to delete some tables
	// processing is done into the dialog itself.
	myDelDlg.ShowModal();
}


void TBVFrame::OnMenuExit(wxCommandEvent & event)
{
	Close();
}


void TBVFrame::OnQuit(wxCloseEvent & event)
{
	this->Destroy();
}


void TBVFrame::OnAbout(wxCommandEvent &event) {
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetName("ToolBasView");
    aboutInfo.SetVersion(wxString::Format("%s.%s.%s %s %s",
                                          VERSION_MAJOR,
                                          VERSION_MINOR,
                                          VERSION_SOFT_VERSION,
                                          VERSION_SOFT_VERSION_BRANCH,
                                          VERSION_SOFT_VERSION_REVISION));
    aboutInfo.SetDescription(_("ToolMap project explorer"));
    aboutInfo.SetCopyright(wxString::Format("(C) TERRANUM, %d", wxDateTime::Now().GetYear()));
    wxAboutBox(aboutInfo);
}


void TBVFrame::OnShowProcessRequest (wxCommandEvent & event){
    m_mgr.GetPane(_T("query")).Maximize();
    m_mgr.Update();
    m_QueryTxtCtrl->SelectAll();
    m_QueryTxtCtrl->SetFocus();
}

void TBVFrame::OnShowLogPanel (wxCommandEvent & event){
    m_mgr.GetPane(_T("log")).Maximize();
    m_mgr.Update();
}


void TBVFrame::OnSpatialDataAdd (wxCommandEvent & event)
{
	GISOgrProvider myOgrData;
	GISDBProvider myDBData;
	wxString myWkbString;
	wxArrayString myReadData;
	int i=1;
	long lFeatureCount = 0;
	
	ADDSPATIALDATA_DLG * myDlg = new ADDSPATIALDATA_DLG(this, &m_Database, -1);
	// show the dialog
	if (myDlg->ShowModal() != wxID_OK)
	{
		delete myDlg;
		return;
	}
	

	// try to open spatial data
	myOgrData.GISOpen(myDlg->m_VectorFileName);
	lFeatureCount = myOgrData.GISGetFeatureCount();
	wxLogDebug(_T("Number of feature read : %d"), lFeatureCount);
	
	// try to open database data
	myDBData.GISOpen(&m_Database);
	myDBData.GISSetActiveLayer(myDlg->m_DBTableName);
	
	// create a progress dialog for showing
	// import progress
	int iMax = lFeatureCount / 1000;
	wxProgressDialog myPrgDlg (_("Importing data into the Database"),
							   _("Importing in progress, please wait..."),
							   iMax);
	
	
	// count elapsed time
	wxStopWatch sw;
	
	while (myOgrData.GISGetNextFeatureAsWktBuffer(&myReadData, 1000))
	{
		myDBData.GISSetFeatureAsWkTBuffer(myReadData, TRUE);
		
		if (i <= iMax)
		{
			myPrgDlg.Update(i);
			i++;	
		}
		
		// clear the buffer
		myReadData.Clear();
	}
	
	// show elapsed time
	wxLogMessage(_("Elapsed time for adding %d spatial data is : %u [ms]"), 
				 lFeatureCount,  sw.Time());
	
	
	// creating index if asked
	if (myDlg->m_bComputeIndex == TRUE)
	{
		sw.Start();
		wxArrayString myFields;
		
		if(myDBData.GISComputeIndex(myFields, myDlg->m_DBTableName))
		{
			wxLogMessage(_("Creating index take %u [ms]"), sw.Time());
		}
	}
	
	// don't forget to close the spatial data
	myOgrData.GISClose();
	myDBData.GISClose();
	
	delete myDlg;
}



void TBVFrame::OnSpatialDataSearch (wxCommandEvent & event)
{
	SEARCHSPATIALPOINT_DLG myDlg (this, &m_Database);
	if (myDlg.OpenDBGISData(_T(""),_T("GENERIC_LINES")))
	{
		myDlg.ShowModal();
	}
	
}


void TBVFrame::OnExportData (wxCommandEvent & event){
    ExportCSV_DLG myDlg(this, wxID_ANY, _("Export Data"), &m_Database);
    myDlg.ShowModal();
}


void TBVFrame::OnDatabaseOperation (wxCommandEvent & event){
    DatabaseOp_DLG myDlg(this, wxID_ANY);
    if (myDlg.ShowModal() != wxID_OK) {
        return;
    }
    
    // get all tables
    wxString myQuery = _T("SHOW TABLES");
    if (m_Database.DataBaseQuery(myQuery, true)==false) {
        return;
    }
    wxArrayString myTables;
    if (m_Database.DataBaseGetResults(myTables)==false) {
        wxLogError(_("Listing database tables failed!"));
        return;
    }
    m_Database.DataBaseClearResults();
    
    
    wxArrayString myResults;
    if (myDlg.GetCheck() == true) {
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            if(m_Database.DataBaseQuery(_T("CHECK TABLE ") + myTables[i],true)==false){
                return;
            }
            myResults.Clear();
            wxString myResultsAggregated = wxEmptyString;
            m_Database.DataBaseGetNextResult(myResults);
            for (unsigned int m = 0; m < myResults.GetCount(); m++) {
                myResultsAggregated.Append(myResults[m] + _T(" | "));
            }
            myResultsAggregated.RemoveLast(3);
            wxLogMessage(myResultsAggregated);
            m_Database.DataBaseClearResults();
        }
    }
    
    
    if (myDlg.GetOptimize() == true) {
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            if(m_Database.DataBaseQuery(_T("OPTIMIZE TABLE ") + myTables[i],true)==false){
                return;
            }
            myResults.Clear();
            wxString myResultsAggregated = wxEmptyString;
            if(m_Database.DataBaseHasResults() == true){
                m_Database.DataBaseGetNextResult(myResults);
                for (unsigned int m = 0; m < myResults.GetCount(); m++) {
                    myResultsAggregated.Append(myResults[m] + _T(" | "));
                }
                myResultsAggregated.RemoveLast(3);
                wxLogMessage(myResultsAggregated);
                m_Database.DataBaseClearResults();
            }
        }
    }
    
    
    if (myDlg.GetRepair() == true) {
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            if(m_Database.DataBaseQuery(_T("REPAIR TABLE ") + myTables[i],true)==false){
                return;
            }
            myResults.Clear();
            wxString myResultsAggregated = wxEmptyString;
            if(m_Database.DataBaseHasResults() == true){
                m_Database.DataBaseGetNextResult(myResults);
                for (unsigned int m = 0; m < myResults.GetCount(); m++) {
                    myResultsAggregated.Append(myResults[m] + _T(" | "));
                }
                myResultsAggregated.RemoveLast(3);
                wxLogMessage(myResultsAggregated);
                m_Database.DataBaseClearResults();
            }
        }
    }


    
}



void TBVFrame::TreeAddItem (wxString tname, int parent){
	if (parent == 0) {
		m_TreeCtrl->AddRoot (tname, 0);
	}
	else {
		m_TreeCtrl->AppendItem(m_TreeCtrl->GetRootItem(),tname, 1);
    }
}



void TBVFrame::ClearCtrls (){
	m_TreeCtrl->DeleteAllItems();
	m_GridOp->GridClear();
}



void TBVFrame::_LoadTablesIntoToc(){
    m_GridOp->GridClear();
    wxWindowUpdateLocker noUpdates(m_TreeCtrl);
    m_TreeCtrl->DeleteAllItems();
    
    if (m_Database.DataBaseQuery(_T("SHOW TABLES"))==false){
        return;
    }

	wxArrayString myStringArray;
	m_Database.DataBaseGetResults(myStringArray);
	m_Database.DataBaseClearResults();
	
	// add database name
	TreeAddItem((m_Database.DataBaseGetName()),0);
	
	// add tables names
	for (unsigned int i=0; i<myStringArray.Count(); i++){
		TreeAddItem(myStringArray.Item(i),1);
	}
    m_TreeCtrl->ExpandAll();
}




void TBVFrame::OnDoubleClickListe (wxTreeEvent & event)
{
	wxArrayString myFieldArray;
	unsigned int i; // loop
	
	wxTreeItemId myItemID = event.GetItem();
	// get the table name
	wxString myTempString = m_TreeCtrl->GetItemText(myItemID);
	if (!m_Database.DataBaseQuery(_T("SHOW COLUMNS FROM ") + myTempString)) {
        wxLogError(_("Building query failed!"));
    }
	m_Database.DataBaseGetResults(myFieldArray);
	
    long myNumberRow = 0;
    long myNumberCol = myFieldArray.Count();
	// check for field numbers (may be not a table)
	if (myFieldArray.Count() > 0)
	{
		// debug message...
		wxLogMessage(_("%d fields readed from the table '%s'"),
                     (int)myFieldArray.Count(),myTempString.c_str());
		
		// change the number of cols
		m_GridOp->GridOpSetNumberOfColumn(myFieldArray.Count());
		
		for (i = 0; i<myFieldArray.Count(); i++) 
		{
			m_GridOp->GridOpChangeColumnText(myFieldArray.Item(i),i,TRUE);
		}
		
		// get the data....
		if(m_Database.DataBaseQuery(_T("SELECT * FROM ") + myTempString))
		{
			wxLogMessage(_("Reading table '%s' OK"),myTempString.c_str());
			
			int iArrayCount = 0;
			
			while (m_Database.DataBaseGetNextResult(myFieldArray)) 
			{
				myNumberRow++;
                iArrayCount = myFieldArray.Count();
				// add a new line
				m_GridOp->GridOpAddDataRow(iArrayCount,
										  &myFieldArray);
			}
			m_Database.DataBaseClearResults();
		
		}
		else 
		{
			wxLogError(_("Error reading the table '%s'"),myTempString.c_str());
		}

		
		
	}
	GetStatusBar()->SetStatusText(wxString::Format(_("%ld columns, %ld rows"), myNumberCol, myNumberRow),1);
}


void TBVFrame::OnExportStructureToClipboard (wxCommandEvent & event){
    wxString myExportChoices [] = {_("Structure"), _("Data")};
    wxMultiChoiceDialog myDlg(this, _("Choose what to export:"),  _("Dump to clipboard"), 2, &myExportChoices[0]);
    if(myDlg.ShowModal()== wxID_CANCEL){
        return;
    }
    
    wxArrayInt myDlgChoice = myDlg.GetSelections();
    if (myDlgChoice.GetCount() == 0) {
        wxLogWarning(_("Nothing selected! Nothing exported!"));
        return;
    }
    
    wxString myClipboardTxt = wxEmptyString;
    wxString myQuery = _T("SHOW TABLES");
    if (m_Database.DataBaseQuery(myQuery)==false) {
        wxLogError(_("Error loading tables structure to clipboard"));
        return;
    }
    if (m_Database.DataBaseHasResults() == false) {
        wxLogError(_("Database didn't contain any table!"));
        return;
    }
    wxArrayString myTables;
    m_Database.DataBaseGetResults(myTables);
    
    
    // export structure
    if (myDlgChoice.Index(0) != wxNOT_FOUND) {
        myClipboardTxt.Append(_T("-- DATABASE STRUCTURE --\n"));
        wxLogMessage(_("Exporting structure to clipboard..."));
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            myQuery = wxString::Format(_T("SHOW CREATE TABLE %s"), myTables.Item(i));
            if (m_Database.DataBaseQuery(myQuery)==false) {
                wxLogError(_("Getting table structure for '%s' failed!"), myTables.Item(i));
                continue;
            }
            DataBaseResult myResult;
            wxString myText = wxEmptyString;
            m_Database.DataBaseGetResults(&myResult);
            myResult.NextRow();
            myResult.GetValue(1, myText);
            myClipboardTxt.Append(wxString::Format(_T("-- %s --\n"), myTables.Item(i)));
            myClipboardTxt.Append(myText);
            myClipboardTxt.Append(_T("\n\n"));
        }
    }
    
    // export data
    if (myDlgChoice.Index(1) != wxNOT_FOUND) {
        wxLogMessage(_("Exporting data to clipboard..."));
        myClipboardTxt.Append(_T("-- DATABASE DATA --\n\n"));
        for (unsigned int i = 0; i< myTables.GetCount(); i++) {
            myQuery = wxString::Format(_T("SELECT * FROM %s"), myTables.Item(i));
            if (m_Database.DataBaseQuery(myQuery)==false) {
                wxLogError(_("Getting table data for '%s' failed!"), myTables.Item(i));
                continue;
            }
            
            myClipboardTxt.Append(wxString::Format(_T("-- %s --\n"), myTables.Item(i)));
            
            DataBaseResult myResult;
            m_Database.DataBaseGetResults(&myResult);
            
            for (long r = 0; r < myResult.GetRowCount(); r++) {
                wxString myText = wxEmptyString;
                myResult.NextRow();
                myText = wxString::Format(_("INSERT INTO %s VALUES("), myTables.Item(i));
                for (int c = 0; c < myResult.GetColCount(); c++) {
                    if (myResult.IsTextField(c)==true) {
                        wxString myColValue;
                        myResult.GetValue(c, myColValue);
                        myText.Append(wxString::Format(_T("\"%s\","), myColValue));
                    }
                    
                    if (myResult.IsNumField(c)==true) {
                        wxString myColValue;
                        myResult.GetValue(c, myColValue);
                        myText.Append(wxString::Format(_T("%s,"), myColValue));
                    }
                    
                    if (myResult.IsGeomField(c)==true) {
                        //OGRGeometry * myGeom = NULL;
                        wxString myValue = wxEmptyString;
                        myResult.GetValue(c, myValue);
                        /*
                        char * myExport;
                        myGeom->exportToWkt(&myExport);
                        wxString sExport = wxString::FromAscii(myExport);
                        wxDELETE(myExport);
                        wxDELETE(myGeom);*/
                        if (myValue == wxEmptyString) {
                            myValue = _T("NULL");
                        }
                        myText.Append(wxString::Format(_T("%s,"), myValue));
                    }
                    
                }
                myText.RemoveLast();
                myText.Append(_T(");\n"));
                myClipboardTxt.Append(myText);
            }
            
            myClipboardTxt.Append(_T("\n\n"));
        }

    }
    
    
       
    if (wxTheClipboard->Open()){
        wxTheClipboard->SetData( new wxTextDataObject(myClipboardTxt) );
        wxTheClipboard->Close();
    }
}



void TBVFrame::OnNewDataBase (wxCommandEvent & event)
{
	wxLogMessage (_("New database"));
	NEWDBASE_OP2 * myDlg = new NEWDBASE_OP2(this,-1,_("Create a new database"),
				wxDefaultPosition, wxDefaultSize);
	myDlg->CenterOnParent();
	if (myDlg->ShowModal()==wxID_OK)
	{
	// clean the tree ctrl
		ClearCtrls();
		
		// create realy the database...
		m_Database.DataBaseCreateNew(myDlg->m_DLG_DB_PATH,myDlg->m_DLG_DB_NAME);
		
		wxLogMessage(_("Database '%s' created OK"), myDlg->m_DLG_DB_NAME.c_str());
		
		// add database name
		TreeAddItem((myDlg->m_DLG_DB_NAME),0);
	}
	
}

void TBVFrame::OnDisplayStatistics (wxCommandEvent & event)
{
	// checking if a database is open ?
	// getting the stats...
	long myiNumberTables = 0;
	wxString mysNumberTables = _T("Unkhown");
	if (!m_Database.DataBaseQuery(_T("SELECT COUNT(*) AS number_of_tables ")
							 _T("FROM information_schema.tables ")
							 _T("WHERE table_schema = \"") + m_Database.DataBaseGetName() + _T("\""))) {
        wxLogError(_("Building query failed!"));
    }
	if (m_Database.DataBaseGetNextResult(myiNumberTables)==true)
		mysNumberTables = wxString::Format(_T("%d"), myiNumberTables);
	m_Database.DataBaseClearResults();
	wxString m_DatabaseSize = m_Database.DataBaseGetSize();
		
		wxString myText = wxString::Format(_("Database : '%s' open \n"),m_Database.DataBaseGetName().c_str());
		myText.Append(wxString::Format(_("Number of table(s) : %s \n"),mysNumberTables.c_str()));
		myText.Append(_("Size of the database : ") + m_DatabaseSize);
		wxMessageBox(myText,_("Database statistics"),wxOK | wxICON_INFORMATION,
					 this);
		
}


void TBVFrame::OnAuiButtonPressed (wxAuiManagerEvent& evt){
    if (evt.GetPane()->IsMaximized() == false) {
        evt.GetPane()->Maximize();
        m_mgr.Update();
    }
    else{       
        evt.GetPane()->Restore();
        m_mgr.Update();
    }
    evt.Veto();
}



void TBVFrame::OnColumnSize (wxCommandEvent & event){
    wxBusyCursor myCursor;
    m_GridCtrl->AutoSizeColumns();
}


void TBVFrame::OnProcessSQLFile (wxCommandEvent & event){
    wxFileDialog myOpenDlg(this, _("Open SQL file"), "","", _("SQL file (*.sql)|*.sql"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (myOpenDlg.ShowModal() != wxID_OK) {
        return;
    }
    
    wxFileInputStream inputStream (myOpenDlg.GetPath());
    if (inputStream.IsOk() == false) {
        wxLogError(_("Opening file: '%s' failed!"), myOpenDlg.GetPath());
        return;
    }
    wxTextInputStream textStream (inputStream, _T(" \t"), wxConvUTF8);
    wxString myQuery;
    long index = 0;
    while (inputStream.Eof() == false) {
        wxString myLine = textStream.ReadLine();
        if (myLine.StartsWith(_T("--"))) {
            continue;
        }
        
        myQuery.Append(myLine);
        if (myQuery.Find(';', true) == wxNOT_FOUND) {
            continue;
        }
        
        // execute query
        if (m_Database.DataBaseQueryNoResults(myQuery)==false) {
            wxLogError(_("Query num: %ld failed: %s"), index, myQuery);
            return;
        }
        /*else{
            wxString myQueryNoSpace (myQuery);
            myQueryNoSpace.Replace(_("\n"), _(""));
            wxLogMessage(_("OK: %s"), myQueryNoSpace);
        }*/
        ++ index;
        myQuery = wxEmptyString;
    }
    ClearCtrls();
    _LoadTablesIntoToc();
    wxMessageBox(wxString::Format(_("%ld Queries passed!"), index));
}



void TBVFrame::OnImportTXTFile (wxCommandEvent & event){
    wxFileDialog myOpenDlg(this, _("Open TXT file"), "","", _("txt file (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (myOpenDlg.ShowModal() != wxID_OK) {
        return;
    }
    
    wxFileInputStream inputStream (myOpenDlg.GetPath());
    if (inputStream.IsOk() == false) {
        wxLogError(_("Opening file: '%s' failed!"), myOpenDlg.GetPath());
        return;
    }
    wxTextInputStream textStream (inputStream, _T(" \t"));
    
    // read first line to create table
    wxArrayString myFirstLine = wxStringTokenize(textStream.ReadLine(), _T("\t"), wxTOKEN_RET_EMPTY_ALL);
    if (myFirstLine.GetCount() == 0) {
        wxLogError(_("Nothing to import!"));
        return;
    }
    
    wxFileName myTxtFileName (myOpenDlg.GetPath());
    wxString myQueryCols = wxEmptyString;
    for (unsigned int i = 0; i<myFirstLine.GetCount(); i++) {
        myQueryCols.Append(wxString::Format(_T("`%s` VARCHAR(1000) NULL DEFAULT NULL,"), myFirstLine.Item(i)));
    }
    myQueryCols.RemoveLast();
    wxString myQuery = wxString::Format( _T("CREATE TABLE `%s` (%s) ENGINE=MyISAM  DEFAULT CHARSET=utf8;"), myTxtFileName.GetName(), myQueryCols);
    
    if (m_Database.DataBaseQueryNoResults(myQuery) == false) {
        wxLogMessage(myQuery);
        wxLogError(_("Error creating table for storing TXT file content"));
        return;
    }

    // import data
    long myLineSkipped = 0;
    long myLineImported = 0;
    int myNbError = 0;
    
    while (inputStream.Eof() == false) {
        wxArrayString myLineContent = wxStringTokenize( textStream.ReadLine(), _T("\t"), wxTOKEN_RET_EMPTY_ALL);
        if (myLineContent.GetCount() == 0) {
            ++ myLineSkipped;
            continue;
        }
        
        wxString myInsQuery = wxString::Format(_T("INSERT INTO `%s` VALUES ("), myTxtFileName.GetName());
        for (unsigned int i = 0; i< myLineContent.GetCount(); i++) {
            wxString myItem = myLineContent.Item(i);
            if (myItem.IsEmpty() == true) {
                myInsQuery.Append(_T("NULL,"));
            }
            else {
                myInsQuery.Append(_T("\"") + myItem + _T("\","));
            }
        }
        myInsQuery.RemoveLast();
        myInsQuery.Append(_T(");"));
        if (m_Database.DataBaseQueryNoResults(myInsQuery) == false) {
            wxLogError(myInsQuery);
            if (myNbError == 10) {
                break;
            }
            ++ myNbError;
            continue;
        }
        
        ++ myLineImported;
    }
    
    wxMessageBox(wxString::Format(_("%ld line imported\n%ld line skipped (empty lines)\n%d errors!"), myLineImported, myLineSkipped, myNbError));
}




void TBVFrame::OnChangeColumnType (wxCommandEvent & event){
    
    wxArrayString myTables;
    if(m_Database.DataBaseQuery(_T("SHOW TABLES"))==true){
        m_Database.DataBaseGetResults(myTables);
    }
    wxSingleChoiceDialog myTableDlg(this, _("Select Table"), _("Change column type on"), myTables);
    if (myTableDlg.ShowModal() != wxID_OK) {
        return;
    }
    wxString myTableName = myTableDlg.GetStringSelection();
    if (myTableName.IsEmpty()) {
        wxLogError(_("No table name specified!"));
        return;
    }
    
    ChangeColumn_DLG myDlg(this, &m_Database, myTableName);
    myDlg.ShowModal();
}


void TBVFrame::OnMySQLReference (wxCommandEvent & event){
    wxLaunchDefaultBrowser(_T("http://dev.mysql.com/doc/refman/5.6/en/sql-syntax.html"));
}


void TBVFrame::OnUpdateUIBtnRun (wxUpdateUIEvent & event){
    if (m_Database.DataBaseGetName() != wxEmptyString && m_QueryTxtCtrl->IsEmpty() == false) {
        event.Enable(true);
        return;
    }
    event.Enable(false);
}



void TBVFrame::OnUpdateUIBtnShowResults (wxUpdateUIEvent & event){
    event.Enable(m_Database.DataBaseHasResults());
}



void TBVFrame::OnUpdateUIBtnHistory (wxUpdateUIEvent & event){
    if (GetHistory() != NULL && GetHistory()->GetCount() > 0) {
        event.Enable(true);
        return;
    }
    event.Enable(false);
}


void TBVFrame::OnUpdateUIAutosize (wxUpdateUIEvent & event){
    if (m_GridCtrl->GetNumberRows() == 0) {
        event.Enable(false);
        return;
    }
    
    // check first row
    for (unsigned int i = 0; i< m_GridCtrl->GetNumberCols(); i++) {
        if (m_GridCtrl->GetCellValue(0, i) != wxEmptyString) {
            event.Enable(true);
            return;
        }
    }
    event.Enable(false);
}


void TBVFrame::OnUpdateUIAddToList (wxUpdateUIEvent & event){
    event.Enable(!m_QueryTxtCtrl->GetValue().IsEmpty());
}

void TBVFrame::OnSysColourChanged (wxSysColourChangedEvent & event){
    _UpdateToolBarColour();
    event.Skip();
}


void TBVFrame::_UpdateHistory (const wxString & sentence){
    wxArrayString * myHistory = GetHistory();
    if (myHistory == NULL) {
        wxLogError(_("History will not be saved!"));
        return;
    }
    
    if (myHistory->GetCount() == 0) {
        myHistory->Insert(sentence, 0);
        return;
    }
    
    if (myHistory->Item(0) == sentence) {
        return;
    }
    myHistory->Insert(sentence, 0);
}



void TBVFrame::OnBtnRun (wxCommandEvent & event){
	wxArrayString myRequestArray; // contain multiple request if needed
	wxArrayInt myErrorsArray;
	wxString myTempRequest;
	
	wxBusyCursor myBusyCursor;
	// if results, destroy them
	if (m_Database.DataBaseHasResults()==true){
		m_Database.DataBaseClearResults();
		wxLogWarning(_("Results of last query where automatically cleared"));
	}
	
	// get the text to process.
    wxString myRequest = m_QueryTxtCtrl->GetValue();
	int myNumberOfRequest = m_Database.DataBaseQueriesNumber(myRequest);
	wxLogMessage(_("Processing Request... %d Request Found"), myNumberOfRequest);
	
	wxString myComment = _("Query error, please check syntax");
	if (m_Database.DataBaseQuery(myRequest)==true){
        // add to history
        _UpdateHistory(myRequest);
        
        myComment = _("Query passed OK, no results");
		if (m_Database.DataBaseHasResults()==true){
			myComment = _("Query passed OK");
		}
	}
    
	// display results
    SetStatusText(myComment, 1);
}


void TBVFrame::OnBtnShowResults (wxCommandEvent & event){
    Results_DLG * myDlg = new Results_DLG(this, &m_Database, m_QueryTxtCtrl->GetValue());
    myDlg->Show();
}


void TBVFrame::OnBtnHistory (wxCommandEvent & event){
    wxString myHistoryValue = wxGetSingleChoice(_("SQL command history"), _("History"), *(GetHistory()), this, wxDefaultCoord, wxDefaultCoord, false, 500, 500);
    if (myHistoryValue == wxEmptyString) {
        return;
    }
    m_QueryTxtCtrl->SetValue(myHistoryValue);
}



void TBVFrame::OnAddToList (wxCommandEvent & event){
    wxString myQueryName = wxGetTextFromUser(_("Query Name"));
    if (myQueryName == wxEmptyString) {
        return;
    }
    
    m_QueryListTreeCtrl->AddQuery(myQueryName, m_QueryTxtCtrl->GetValue());
}



void TBVFrame::OnTreeItemDoubleClick (wxTreeEvent & event){
    wxTreeItemId myId = event.GetItem();
    if (myId.IsOk() == false) {
        return;
    }
    
    QueryListTreeData * myData = static_cast<QueryListTreeData*>(m_QueryListTreeCtrl->GetItemData(myId));
    if (myData == NULL || myData->m_ItemType != QueryListTreeData::DATA_QUERY) {
        return;
    }
    
    m_QueryTxtCtrl->SetValue(myData->m_Query);
}


wxArrayString * TBVFrame::GetHistory(){
    return & m_History;
}



void TBVFrame::OnUpdateUIDatabaseOpen (wxUpdateUIEvent & event){
    if (m_Database.DataBaseGetName() != wxEmptyString) {
        event.Enable(true);
        return;
    }
    event.Enable(false);
}









