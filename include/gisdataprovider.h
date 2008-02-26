/***************************************************************************
								gisdataprovider.h
                    Generic class for providing GIS data
                             -------------------
    copyright            : (C) 2007 CREALP Lucien Schreiber 
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

// comment doxygen


#ifndef GISDATAPROVIDER_H
#define GISDATAPROVIDER_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// Include wxWidgets' headers
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif



#include <ogrsf_frmts.h>	// compile GDAL with GEOS support !
#include "geos_c.h"			// for geos (Geographic data processing)
#include "database.h"		// for GISDBProvider to support direct com with DB

enum GISPROVIDER_SUPPORTED_TYPE
{
	GISTYPE_ESRI_SHP = 0,
	GISTYPE_TIFF,	
};
const int GISPROVIDER_SUPPORTED_TYPE_NUMBER = 2;


/*************************  GENERIC GIS PROVIDER ***************************/
class GISDataProvider  : public wxObject
	{
	private:
		DECLARE_CLASS (GISDataProvider);
		bool m_GISisOpen;
		
	protected:
		
	public:
		GISDataProvider();
		~GISDataProvider();
		
		virtual bool GISOpen (const wxString & filename);
		virtual wxRect GISGetExtend ();
		virtual bool GISClose ();
		bool GISIsOpened ();
		
		

	};



/*************************  OGR GIS PROVIDER (SHP,...) ***************************/
class GISOgrProvider : public GISDataProvider
	{
	private:
		OGRLayer			* m_pLayer;
		OGRDataSource       *m_pDatasource;
		//long				m_NumOfVector;
		unsigned int		m_iFeatureLoop;
		
	public:
		GISOgrProvider();
		~GISOgrProvider();
		
		virtual bool GISOpen (const wxString & filename);
		virtual wxRect GISGetExtend ();
		virtual long GISGetFeatureCount ();
		virtual bool GISGetNextFeatureAsWkT (wxString & wkbstring);
		virtual bool GISGetNextFeatureAsWktBuffer(wxArrayString * featurelist, int iBufferSize);
		virtual bool GISClose ();

	};


/*************************  DATABASE GIS PROVIDER (sqlite) ***************************/
class GISDBProvider : public GISDataProvider
	{
	private:
		OGRLayer			* m_pLayer;
		OGRDataSource       *m_pDatasource;
		//long				m_NumOfVector;
		unsigned int		m_iFeatureLoop;
		DataBase		*	m_pActiveDB;
		
	public:
		GISDBProvider();
		~GISDBProvider();
		
		virtual bool GISOpen (const wxString & filename);
		virtual wxRect GISGetExtend ();
		virtual long GISGetFeatureCount ();
		virtual bool GISGetNextFeatureAsWkT (wxString & wkbstring);
		virtual bool GISSetFeatureAsWkT (const wxString & wkbstring, bool bComputeExtend = TRUE);
		virtual bool GISSetFeatureAsWkTBuffer (const wxArrayString & featurelist, bool bComputeExtend = TRUE);
		virtual int  GISGetLayerCount ();
		virtual bool GISSetLayer (const wxString & layername);
		virtual void GISSetActiveDatabase(DataBase * pDB) {m_pActiveDB = pDB;}
		virtual bool GISComputeBoundingBox (wxString  wktstring, OGREnvelope * enveloppe);
		virtual bool GISClose ();
		
		
	};



#endif
