#ifndef TOOLBASVIEW_TOOLBARBITMAPS_H
#define TOOLBASVIEW_TOOLBARBITMAPS_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class Bitmaps {
 public:
  static wxString SvgText[];
  static wxString SvgLogo;
  enum ID { NEW = 0, OPEN, COPY, EXPORT, QUERY_PANEL, SIZE_COLS, SIZE_ROWS, DATABASE, TABLE, GROUP, QUERY };
  static wxBitmap GetBitmap(Bitmaps::ID id, const wxString& colour = "#000000", const wxSize& size = wxSize(16, 16));
  static wxBitmap GetLogo(const wxSize & size = wxSize(32,32));
};

#endif
