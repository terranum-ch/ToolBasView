/***************************************************************************
 lsfoldbar.h
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
#ifndef _LSFOLDBAR_H_
#define _LSFOLDBAR_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/statline.h>


class lsFoldBarCtrl : public wxControl {
private:
    wxSizer * m_ClientSizer;
    wxSizerItem * m_ParentSizerItem;
    
    wxPanel* m_TitleBarPanel;
    wxStaticText* m_TitleText;
    wxBitmapButton* m_TitleButtonCtrl;
    
    void OnButtonClick(wxCommandEvent & event);
    
    
public:
    lsFoldBarCtrl(wxWindow * parent, wxWindowID id);
    virtual ~lsFoldBarCtrl();
    
    void SetTitle(const wxString & title);
    void SetTitleBackground (const wxColour & colour);
    void SetSizerItem (wxSizerItem * sizeritem){m_ParentSizerItem = sizeritem;}

    inline wxSizer * GetClientSizer();
    
    void ShowBar();
    void HideBar();
    
};


inline wxSizer * lsFoldBarCtrl::GetClientSizer(){
    return m_ClientSizer;
}

#endif
