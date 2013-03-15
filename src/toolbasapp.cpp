/***************************************************************************
toolbaseapp.cpp
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

#include "toolbasapp.h"
#include "toolbaseframe.h"

bool TBVApp::OnInit()
{
	TBVFrame * frame = new TBVFrame(NULL, _T("ToolBasView"), wxPoint(50,50), wxSize(800,600));
	frame->Centre();
	frame->Show();
	return true;
}