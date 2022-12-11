#ifndef TOOLBASVIEW_TOOLBARBITMAPS_H
#define TOOLBASVIEW_TOOLBARBITMAPS_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum ToolbarBitmapsID {
  TBID_NEW = 0,
  TBID_OPEN,
  TBID_COPY,
  TBID_EXPORT,
  TBID_QUERY,
  TBID_SIZE_COLS,
  TBID_SIZE_ROWS
};


class ToolbarBitmaps {
 public:
  static wxBitmap GetBitmapFromSVG(ToolbarBitmapsID id, const wxString& colour = "#000000", const wxSize& size = wxSize(16,16));
};

#endif  // TOOLBASVIEW_TOOLBARBITMAPS_H
