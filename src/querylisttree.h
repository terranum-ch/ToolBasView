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
#ifndef _QUERYLISTTREE_H_
#define _QUERYLISTTREE_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/treectrl.h>
#include <wx/filename.h>
#include <wx/imaglist.h>
#include <wx/file.h>

const int ID_QUERY_TREE_CATEGORY_ADD = wxWindow::NewControlId();
const int ID_QUERY_TREE_CATEGORY_DEL = wxWindow::NewControlId();


class QueryListTreeData : public wxTreeItemData {
public:
    enum {DATA_CATEGORY = 0, DATA_QUERY = 1 } m_ItemType;
    wxString m_Query;
    
    QueryListTreeData(){
        m_ItemType = DATA_CATEGORY;
        m_Query = wxEmptyString;
    }
};


class QueryListTree : public wxTreeCtrl {
  public:
    QueryListTree(wxWindow * parent, wxWindowID id, const wxPoint & pos, const wxSize & size, long style);
    virtual ~QueryListTree();

    bool Save(const wxFileName & filename);
    bool Load(const wxFileName & filename);
    
    void AddQuery(const wxString & name, const wxString & sql);


  private:
    void OnContextualMenu(wxContextMenuEvent & event);
    void OnCategoryAdd(wxCommandEvent & event);
    void OnCategoryDel(wxCommandEvent & event);
    void OnUpdateUICategoryDel (wxUpdateUIEvent & event);
    
    void OnDragStart(wxTreeEvent & event);
    void OnDragStop(wxTreeEvent & event);
    
    enum IMAGE_TYPE {IMAGE_CATEGORY = 0, IMAGE_QUERY = 1} ;
    
    void _CopyTreeItems(wxTreeItemId origin, wxTreeItemId destination, bool isRoot = true);
    void _MoveLayer (wxTreeItemId origin, wxTreeItemId destination);
    void _RecursiveWrite (wxTreeItemId origin, wxFile * file);
    
    wxTreeItemId m_DragItemID;
    wxTreeItemId m_RootNode;
};
#endif
