/***************************************************************************
 querylisttree
 -------------------
 copyright            : (C) 2013 Lucien Schreiber 
 email                : lucien.schreiber at gmail dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "querylisttree.h"
#include "toolbasview_bmp.h"

QueryListTree::QueryListTree(wxWindow * parent, wxWindowID id, const wxPoint & pos, const wxSize & size, long style):
wxTreeCtrl(parent, id, pos, size, style){
    wxImageList *images = new wxImageList(16, 16, true);
    images->Add(*_img_query_category);
    images->Add(*_img_query_item);
    AssignImageList(images);
    
	//QueryListTreeData * myData = new QueryListTreeData();
    m_RootNode = AddRoot(_T("List"));
    
    this->Bind(wxEVT_CONTEXT_MENU, &QueryListTree::OnContextualMenu, this);
    this->Bind(wxEVT_COMMAND_MENU_SELECTED, &QueryListTree::OnCategoryAdd, this, ID_QUERY_TREE_CATEGORY_ADD);
    this->Bind(wxEVT_COMMAND_MENU_SELECTED, &QueryListTree::OnCategoryDel, this, ID_QUERY_TREE_CATEGORY_DEL);
    this->Bind(wxEVT_COMMAND_MENU_SELECTED, &QueryListTree::OnQueryDel, this, ID_QUERY_TREE_QUERY_DEL);

    this->Bind(wxEVT_UPDATE_UI, &QueryListTree::OnUpdateUICategoryDel, this, ID_QUERY_TREE_CATEGORY_DEL);
    this->Bind(wxEVT_UPDATE_UI, &QueryListTree::OnUpdateUIQueryDel, this, ID_QUERY_TREE_QUERY_DEL);

    this->Bind(wxEVT_TREE_BEGIN_DRAG, &QueryListTree::OnDragStart, this);
    this->Bind(wxEVT_TREE_END_DRAG, &QueryListTree::OnDragStop, this);
}



QueryListTree::~QueryListTree() {
    this->Unbind(wxEVT_CONTEXT_MENU, &QueryListTree::OnContextualMenu, this);
    this->Unbind(wxEVT_COMMAND_MENU_SELECTED, &QueryListTree::OnCategoryAdd, this, ID_QUERY_TREE_CATEGORY_ADD);
    this->Unbind(wxEVT_COMMAND_MENU_SELECTED, &QueryListTree::OnCategoryDel, this, ID_QUERY_TREE_CATEGORY_DEL);
    this->Unbind(wxEVT_COMMAND_MENU_SELECTED, &QueryListTree::OnQueryDel, this, ID_QUERY_TREE_QUERY_DEL);

    this->Unbind(wxEVT_UPDATE_UI, &QueryListTree::OnUpdateUICategoryDel, this, ID_QUERY_TREE_CATEGORY_DEL);
    this->Unbind(wxEVT_UPDATE_UI, &QueryListTree::OnUpdateUIQueryDel, this, ID_QUERY_TREE_QUERY_DEL);

    this->Unbind(wxEVT_TREE_BEGIN_DRAG, &QueryListTree::OnDragStart, this);
    this->Unbind(wxEVT_TREE_END_DRAG, &QueryListTree::OnDragStop, this);
}



bool QueryListTree::Save(const wxFileName & filename) {
    wxFile myFile;
    if (filename.Exists() == false) {
        myFile.Create(filename.GetFullPath());
    }
    myFile.Open(filename.GetFullPath(), wxFile::write);
    if (myFile.IsOpened() == false) {
        return false;
    }
    
    _RecursiveWrite(m_RootNode, &myFile);
    return true;
}



void QueryListTree::_RecursiveWrite (wxTreeItemId origin, wxFile * file){
    wxASSERT(file);
    wxTreeItemIdValue cookie;
    wxTreeItemId myItem = GetFirstChild( origin, cookie );
    
	while( myItem.IsOk() ){
        QueryListTreeData * myDataOrigin = static_cast<QueryListTreeData*>(GetItemData(myItem));
        wxString myParentName = ""; 
        if (origin != m_RootNode) {
            myParentName = GetItemText(origin);
        }
        
        wxString myName = GetItemText(myItem);
        int myType = myDataOrigin->m_ItemType;
        wxString myQuery = myDataOrigin->m_Query;
        bool bExpended = IsExpanded(myItem);
        
        // support multi-line query
        myQuery.Replace(_T("\n"), _T("###"));
        file->Write(wxString::Format(_T("%s\t%s\t%d\t%d\t%s\n"), myParentName, myName, myType, bExpended, myQuery));
		if( ItemHasChildren( myItem ) ){
            _RecursiveWrite(myItem, file);
		}
		myItem = GetNextChild( origin, cookie);
	}
}



bool QueryListTree::Load(const wxFileName & filename) {
    if (filename.Exists() == false) {
        return false;
    }
    
    wxFileInputStream myInputStream (filename.GetFullPath());
    wxTextInputStream myTxtStream ( myInputStream );
    wxString myLine;
    wxTreeItemId myAddedItem;
    wxASSERT(myAddedItem.IsOk() == false);
    
    while ((myLine = myTxtStream.ReadLine()) != wxEmptyString) {
        // process line : parent name, name, type, isexpanded, query
        wxStringTokenizer myTokenizer (myLine, _T("\t"), wxTOKEN_RET_EMPTY_ALL);
        if (myTokenizer.CountTokens() != 5) {
            wxLogWarning(_("Incorrect data found while loading query list! skipping"));
            continue;
        }
        
        wxString myParentName = myTokenizer.GetNextToken();
        wxString myName = myTokenizer.GetNextToken();
        long myType = 0;
        myTokenizer.GetNextToken().ToLong(&myType);
        long myExpended = 0;
        myTokenizer.GetNextToken().ToLong(&myExpended);
        wxString myQuery = myTokenizer.GetNextToken();
        
        myQuery.Replace(_T("###"), _T("\n"));
        
        wxTreeItemId myParent;
        if (myParentName == wxEmptyString) {
            myParent = m_RootNode;
        }
        else {
            QueryListTreeData * myData = static_cast<QueryListTreeData*>(GetItemData(myAddedItem));
            wxASSERT(myData);
            if ( GetItemText(myAddedItem) == myParentName && myData->m_ItemType == QueryListTreeData::DATA_CATEGORY ) {
                myParent = myAddedItem;
            }
            else {
                while ( (myParent = GetItemParent(myAddedItem)) .IsOk() ) {
                    QueryListTreeData * myData = static_cast<QueryListTreeData*>(GetItemData(myParent));
                    wxASSERT(myData);
                    if ( GetItemText(myParent) == myParentName && myData->m_ItemType == QueryListTreeData::DATA_CATEGORY ) {
                        break;
                    }
                }
            }
        }
        if (myParent.IsOk() == false) {
            wxLogWarning(_("Parent not found for: '%s', using Root"), myName);
            myParent = m_RootNode;
        }
        
        QueryListTreeData * myData = new QueryListTreeData();
        if (myType == QueryListTreeData::DATA_QUERY) {
            myData->m_ItemType = QueryListTreeData::DATA_QUERY;
            myData->m_Query = myQuery;
        }
        myAddedItem = AppendItem(myParent, myName, myData->m_ItemType, -1, myData);
        if (myExpended == 1 && myData->m_ItemType == QueryListTreeData::DATA_CATEGORY) {
            Expand(myAddedItem);
        }
    }
    return true;
}


void QueryListTree::OnContextualMenu(wxContextMenuEvent & event) {
    wxLogError(_("Coucou"));
    wxMenu myPopupMenu;
    myPopupMenu.Append(ID_QUERY_TREE_CATEGORY_ADD, _("Add category..."), wxEmptyString, false);
    myPopupMenu.Append(ID_QUERY_TREE_CATEGORY_DEL, _("Remove category"), wxEmptyString, false);
    myPopupMenu.AppendSeparator();
    myPopupMenu.Append(ID_QUERY_TREE_QUERY_DEL, _("Remove query"), wxEmptyString, false);
    PopupMenu(&myPopupMenu);
}


void QueryListTree::OnUpdateUICategoryDel (wxUpdateUIEvent & event){
    if (GetSelection().IsOk() == false) {
        event.Enable(false);
        return;
    }
    
    QueryListTreeData * myData = static_cast<QueryListTreeData*>(GetItemData(GetSelection()));
    if (myData == NULL || myData->m_ItemType != QueryListTreeData::DATA_CATEGORY) {
        event.Enable(false);
        return;
    }
    
    event.Enable(true);
}



void QueryListTree::OnUpdateUIQueryDel (wxUpdateUIEvent & event ){
    if (GetSelection().IsOk() == false) {
        event.Enable(false);
        return;
    }
    
    QueryListTreeData * myData = static_cast<QueryListTreeData*>(GetItemData(GetSelection()));
    if (myData == NULL || myData->m_ItemType != QueryListTreeData::DATA_QUERY) {
        event.Enable(false);
        return;
    }
    
    event.Enable(true);
}




void QueryListTree::OnCategoryAdd(wxCommandEvent & event) {
    wxString myCategoryName = wxGetTextFromUser(_("New category name"));
    if (myCategoryName == wxEmptyString) {
        return;
    }
    
    QueryListTreeData * myData = new QueryListTreeData();
    AppendItem(GetRootItem(), myCategoryName, IMAGE_CATEGORY, -1, myData);
}



void QueryListTree::OnCategoryDel(wxCommandEvent & event) {
    wxTreeItemId mySelectedId = GetSelection();
    wxASSERT(mySelectedId.IsOk());
    if (HasChildren(mySelectedId) == true) {
        DeleteChildren(mySelectedId);
    }
    Delete(mySelectedId);
}


void QueryListTree::OnQueryDel(wxCommandEvent & event){
    Delete(GetSelection());
}



void QueryListTree::AddQuery(const wxString & name, const wxString & sql) {
    wxTreeItemId mySelectedId = GetSelection();
    if (mySelectedId.IsOk() == false || GetCount() == 0) {
        mySelectedId = m_RootNode;
		QueryListTreeData * myData = new QueryListTreeData();
		myData->m_ItemType = QueryListTreeData::DATA_QUERY;
		myData->m_Query = sql;
		AppendItem(m_RootNode, name, QueryListTreeData::DATA_QUERY, -1, myData);
		return;
    }
    
    wxTreeItemId myAddId = mySelectedId;
    QueryListTreeData * mySelectedData = static_cast<QueryListTreeData*>(GetItemData(mySelectedId));
    wxASSERT(mySelectedData);
    if (mySelectedData->m_ItemType == QueryListTreeData::DATA_QUERY) {
        myAddId = GetItemParent(mySelectedId);
    }
    
    QueryListTreeData * myData = new QueryListTreeData();
    myData->m_ItemType = QueryListTreeData::DATA_QUERY;
    myData->m_Query = sql;
    
    AppendItem(myAddId, name, QueryListTreeData::DATA_QUERY, -1, myData);
}



void QueryListTree::OnDragStart(wxTreeEvent & event){
    m_DragItemID = wxTreeItemId();
	wxASSERT(m_DragItemID.IsOk() == false);
	
    m_DragItemID = event.GetItem();
    if (m_DragItemID == m_RootNode) {
        wxLogWarning("This can't be dragged!");
        return;
    }
    
    QueryListTreeData * myData = static_cast<QueryListTreeData*>(GetItemData(m_DragItemID));
    wxASSERT(myData);
    
    switch (myData->m_ItemType) {
        case QueryListTreeData::DATA_CATEGORY:
        case QueryListTreeData::DATA_QUERY:
            event.Allow();
            break;
            
        default:
            wxLogWarning("This can't be dragged!");
            break;
    }
}



void QueryListTree::OnDragStop(wxTreeEvent & event){
    if (m_DragItemID.IsOk() == false) {
        return;
    }
    
    wxTreeItemId myItemStart = m_DragItemID;
	wxTreeItemId myItemStop = event.GetItem();
    
    if (myItemStart == myItemStop){
        return;
    }
    
	if (myItemStop == NULL || myItemStop.IsOk() == false){
		return;
	}
    
	QueryListTreeData * myDataStop = static_cast<QueryListTreeData*>(GetItemData(myItemStop));
	if(myDataStop == NULL){
		return;
	}
    
   
    // drag into group
    if (myDataStop->m_ItemType == QueryListTreeData::DATA_CATEGORY) {
        _CopyTreeItems(myItemStart, myItemStop);
        //_ReorderFromTree(myItemStop);
        Delete(myItemStart);
    }
    
    if (myDataStop->m_ItemType == QueryListTreeData::DATA_QUERY) {
        if (myItemStop == GetNextSibling(myItemStart)) {
            return;
        }
        _MoveLayer(myItemStart, myItemStop);
        Delete(myItemStart);
    }
}



void QueryListTree::_CopyTreeItems(wxTreeItemId origin, wxTreeItemId destination, bool isRoot) {
	wxTreeItemId myDestination = destination;
    if (isRoot == true) {
        // first loop, no recursivity
        QueryListTreeData * myDataOrigin = static_cast<QueryListTreeData*>(GetItemData(origin));
        QueryListTreeData * myDataCopy = new QueryListTreeData(*myDataOrigin);
        myDestination = AppendItem(destination, GetItemText(origin),GetItemImage(origin), -1, myDataCopy);
    }
    
    wxTreeItemIdValue cookie;
    wxTreeItemId myItem =  GetFirstChild( origin, cookie );
    
	while( myItem.IsOk() ){
        QueryListTreeData * myDataOrigin = static_cast<QueryListTreeData*>(GetItemData(myItem));
        QueryListTreeData * myDataCopy = new QueryListTreeData(*myDataOrigin);
        wxTreeItemId myCopyItem =  AppendItem(myDestination, GetItemText(myItem), GetItemImage(myItem), -1, myDataCopy);
        
		if( ItemHasChildren( myItem ) ){
            _CopyTreeItems(myItem, myCopyItem, false);
		}
		myItem = GetNextChild( origin, cookie);
	}
}


void QueryListTree::_MoveLayer (wxTreeItemId origin, wxTreeItemId destination){
    QueryListTreeData * myDataOrigin = static_cast<QueryListTreeData*>(GetItemData(origin));
    QueryListTreeData * myDataCopy = new QueryListTreeData(*myDataOrigin);
    
    wxTreeItemId myDestParent = GetItemParent(destination);
    wxTreeItemId myTarget = GetPrevSibling(destination);
    if (myTarget.IsOk() == false) {
        myTarget = 0;
    }
    wxASSERT(myDestParent.IsOk());
    // insert item before destination
    wxTreeItemId myNewId =  InsertItem(myDestParent, myTarget,GetItemText(origin), GetItemImage(origin), -1, myDataCopy);
    SelectItem(myNewId);
    //_CopyTreeItems(origin, myNewId);
    
    //_ReorderFromTree(myNewId);
}




