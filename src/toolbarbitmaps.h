#ifndef TOOLBASVIEW_TOOLBARBITMAPS_H
#define TOOLBASVIEW_TOOLBARBITMAPS_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class Bitmaps {
 public:
  static wxString SvgText[];
  enum ID { NEW = 0, OPEN, COPY, EXPORT, QUERY, SIZE_COLS, SIZE_ROWS };
  static wxBitmap GetBitmap(Bitmaps::ID id, const wxString& colour = "#000000", const wxSize& size = wxSize(16, 16));
};

#endif  // TOOLBASVIEW_TOOLBARBITMAPS_H
