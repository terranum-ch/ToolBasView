/***************************************************************************
 resultsframe.cpp
 -------------------
 copyright            : (C) 2012 CREALP Lucien Schreiber
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
#include "resultsframe.h"
#include "results_bmp.h"
#include "database.h"
#include "databaseresult.h"
#include "gridoperation.h"
#include "Excel.h"


BEGIN_EVENT_TABLE( Results_DLG, wxFrame )
EVT_CLOSE( Results_DLG::OnCloseResults )
EVT_TOOL( wxID_COPY, Results_DLG::OnMenuCopy )
EVT_UPDATE_UI( wxID_COPY, Results_DLG::OnUpdateUICopy )
EVT_TOOL( ID_EXPORT_EXCEL, Results_DLG::OnMenuExport )
EVT_UPDATE_UI( ID_EXPORT_EXCEL, Results_DLG::OnUpdateUIExport )
EVT_TOOL( ID_AUTOSIZE_COLUMN, Results_DLG::OnMenuAutosize )
EVT_TOOL(ID_AUTOSIZE_ROW, Results_DLG::OnMenuAutosizeVertical)
EVT_UPDATE_UI( ID_AUTOSIZE_COLUMN, Results_DLG::OnUpdateUIAutosize )
EVT_UPDATE_UI(ID_AUTOSIZE_ROW, Results_DLG::OnUpdateUIAutosize)
EVT_TOOL( wxID_EXIT, Results_DLG::OnMenuClose )
END_EVENT_TABLE()



Results_DLG::Results_DLG( wxWindow* parent, DataBase * database, const wxString & query, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) :
wxFrame( parent, id, title, pos, size, style ){
    m_DB = database;
    m_ResultDisplayed = false;
    wxASSERT(m_DB);
    results_initialize_images();
    _CreateControls();
    _SetRandomPosition();
    
    m_QueryCtrl->SetValue(query);
    
    _DisplayResults();
}



Results_DLG::~Results_DLG(){
    m_mgr.UnInit();
    results_clean_images();
}




void Results_DLG::OnCloseResults( wxCloseEvent& event ) {
    Destroy();
}


void Results_DLG::OnMenuCopy( wxCommandEvent& event ) {
	wxString myValues = wxEmptyString;
    
    // get header
	for (int icol = 0; icol < m_GridCtrl->GetNumberCols(); icol++) {
        myValues.Append(m_GridCtrl->GetColLabelValue(icol));
        myValues.Append(_T("\t"));
    }
    myValues.RemoveLast();
    myValues.Append(_T("\n"));
    
    // get values
    for (int irow = 0; irow < m_GridCtrl->GetNumberRows(); irow++){
		for (int icol = 0; icol < m_GridCtrl->GetNumberCols(); icol++) {
            myValues.Append(m_GridCtrl->GetCellValue(irow, icol));
			if (icol < m_GridCtrl->GetNumberCols() -1) {
				myValues.Append(_T("\t"));
			}
		}
		myValues.Append(_T("\n"));
	}
    myValues.RemoveLast();
	
	if (wxTheClipboard->Open())
    {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData(new wxTextDataObject(myValues));
        wxTheClipboard->Close();
    }
}



void Results_DLG::OnMenuExport( wxCommandEvent& event ) {
    wxFileDialog saveDlg (this, _("Save XLS file"), "", "", "XLS files (*.xls)|*.xls", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveDlg.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    Excel myExcel;
    wxFileName mySaveFileName (saveDlg.GetPath());
    if(myExcel.Open((const char *) mySaveFileName.GetFullPath().mb_str(wxConvUTF8))==false){
        wxLogError(_("Unable to open: '%s'"), mySaveFileName.GetFullName());
        return;
    }
    
    myExcel.Begin();
    // get header
	for (int icol = 0; icol < m_GridCtrl->GetNumberCols(); icol++) {
        myExcel.Write(0, icol, m_GridCtrl->GetColLabelValue(icol).mb_str(wxConvUTF8));
    }
    
    
    // get values
    for (int irow = 0; irow < m_GridCtrl->GetNumberRows(); irow++){
		for (int icol = 0; icol < m_GridCtrl->GetNumberCols(); icol++) {
            myExcel.Write(irow + 1, icol, m_GridCtrl->GetCellValue(irow, icol).mb_str(wxConvUTF8));
        }
	}

    myExcel.End();
    wxLogMessage(_("Exporting data to '%s' OK!"), mySaveFileName.GetFullName());
}



void Results_DLG::OnMenuAutosize( wxCommandEvent& event ) {
    wxBusyCursor myCursor;
    m_GridCtrl->AutoSizeColumns(false);
}


void Results_DLG::OnMenuAutosizeVertical ( wxCommandEvent& event ){
    wxBusyCursor myCursor;
    m_GridCtrl->AutoSizeRows(false);
}



void Results_DLG::OnMenuClose( wxCommandEvent& event ) {
    Close();
}


void Results_DLG::OnUpdateUICopy( wxUpdateUIEvent& event ) {
    event.Enable(m_ResultDisplayed);
}


void Results_DLG::OnUpdateUIAutosize( wxUpdateUIEvent& event ) {
    event.Enable(m_ResultDisplayed);
}


void Results_DLG::OnUpdateUIExport( wxUpdateUIEvent& event ) {
    event.Enable(m_ResultDisplayed);
}



void Results_DLG::_DisplayResults(){
    DataBaseResult myResult;
    if (m_DB->DataBaseGetResults(&myResult)==false) {
        wxLogError(_("Getting results failed!"));
        return;
    }
    
    if (myResult.HasResults() == false) {
        wxLogMessage(_("No results returned by your request"));
        return;
    }
    
    GridOperation * myGridOP = new GridOperation(m_GridCtrl);
    myGridOP->GridOpSetNumberOfColumn(myResult.GetColCount());
    wxArrayString myColsName;
    myResult.GetColName(myColsName);
    for (unsigned int i = 0; i< myColsName.GetCount(); i++) {
        myGridOP->GridOpChangeColumnText(myColsName.Item(i), i);
    }
    
    int myColCount = myResult.GetColCount();
    int iRow = 0;
    while (myResult.NextRow()) {
        m_GridCtrl->AppendRows(1,false);
        for (unsigned int i = 0; i < myColCount; i++) {
            wxString myText;
            myResult.GetValue(i, myText);
            m_GridCtrl->SetCellValue(iRow, i, myText);
        }
        iRow++;
    }
    
    SetStatusText(wxString::Format(_T("columns: %d, rows: %ld"),myColCount, myResult.GetRowCount()));
    m_ResultDisplayed = true;
    wxDELETE(myGridOP);
}




void Results_DLG::_CreateControls(){
    wxPanel* m_panel2;
    wxToolBar* m_toolBar1;
    wxPanel* m_panel4;
    wxStatusBar* m_statusBar1;
     
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel2, wxAuiPaneInfo() .Name( wxT("main") ).Left() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).CentrePane() );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_GridCtrl = new wxGrid( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_GridCtrl->CreateGrid( 5, 5 );
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
	bSizer3->Add( m_GridCtrl, 1, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer3 );
	m_panel2->Layout();
	bSizer3->Fit( m_panel2 );
		
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel4, wxAuiPaneInfo() .Name( wxT("query") ).Bottom() .Caption( _("Original query") ).CloseButton( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).BestSize( wxSize( -1,40 ) ) );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_QueryCtrl = new wxTextCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_QueryCtrl, 1, wxEXPAND, 5 );
	
	
	m_panel4->SetSizer( bSizer4 );
	m_panel4->Layout();
	bSizer4->Fit( m_panel4 );
	
	m_mgr.Update();
	//this->Centre( wxBOTH );

	long style = wxTB_FLAT | wxTB_HORIZONTAL;
#ifndef __WXMSW__
	style += wxTB_TEXT;
#endif

    // TOOLBAR
	m_toolBar1 = this->CreateToolBar(style, wxID_ANY );
	m_toolBar1->SetToolBitmapSize( wxSize( 32,32 ) );
    
    wxString myText = _("Copy");
	m_toolBar1->AddTool( wxID_COPY, myText, *_img_results_copy, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
	
    myText = _("Export");
	m_toolBar1->AddTool( ID_EXPORT_EXCEL, myText,*_img_results_excel, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
	
    myText = _("Resize columns");
	m_toolBar1->AddTool( ID_AUTOSIZE_COLUMN, myText, *_img_results_autosize, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
    
    myText = _("Resize rows");
    m_toolBar1->AddTool(ID_AUTOSIZE_ROW, myText, *_img_results_autosize_row, wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL);
    
	
    myText = _("Close");
	m_toolBar1->AddTool(wxID_EXIT, myText, *_img_results_close,  wxNullBitmap, wxITEM_NORMAL, myText, wxEmptyString, NULL );
	
	m_toolBar1->Realize();
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
}



void Results_DLG::_SetRandomPosition(){
    wxDisplay myDisplay;
    wxSize myMaxPosition = myDisplay.GetClientArea().GetSize() - GetSize();
    
    srand(wxDateTime::Now().GetTicks());
    int iLeft = (rand() % myMaxPosition.GetWidth());
    int iTop = (rand() % myMaxPosition.GetHeight());
    
    SetPosition(wxPoint(iLeft, iTop));
}


