/***************************************************************************
							gisdataprovider.cpp
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

#include "../include/gisdataprovider.h"


/*************************  GENERIC GIS PROVIDER ***************************/
IMPLEMENT_CLASS (GISDataProvider, wxObject);

GISDataProvider::GISDataProvider()
{
	m_GISisOpen = FALSE;

}



GISDataProvider::~GISDataProvider()
{

}


bool GISDataProvider::GISOpen (const wxString & filename)
{
	m_GISisOpen = TRUE;
	return TRUE;
}


wxRect GISDataProvider::GISGetExtend ()
{

	return wxRect(0,0,0,0);
}


bool GISDataProvider::GISClose ()
{
	m_GISisOpen = FALSE;
	return TRUE;
}

bool GISDataProvider::GISIsOpened ()
{
	return m_GISisOpen;
}






/*************************  OGR GIS PROVIDER (SHP,...) ***************************/
GISOgrProvider::GISOgrProvider()
{
	//m_NumOfVector		= 0;
	m_pLayer			= NULL;
	m_pDatasource		= NULL;
	m_iFeatureLoop		= 0;
	
}



GISOgrProvider::~GISOgrProvider()
{
	
}


bool GISOgrProvider::GISOpen (const wxString & filename)
{
		
	m_pDatasource = OGRSFDriverRegistrar::Open(filename.ToAscii(), FALSE );
    if( m_pDatasource != NULL )
    {
		GISDataProvider::GISOpen(filename);
		m_pLayer = m_pDatasource->GetLayer(0);
		m_pLayer->ResetReading();
		
		wxLogDebug(_T("Opening vector file OK"));
		return TRUE;
    }
	
	// if we couldn't open the vector file try to know why
	const char * myError = CPLGetLastErrorMsg();
	wxString myErrMsg = wxString::FromAscii(myError);
	wxLogDebug(_T("Open vector failed for file %s, error msg is : %s"), 
			   filename.c_str(), myErrMsg.c_str());
	return FALSE;
}


wxRect GISOgrProvider::GISGetExtend ()
{
	
	return wxRect(0,0,0,0);
}


long GISOgrProvider::GISGetFeatureCount ()
{
	return m_pLayer->GetFeatureCount();
}


bool GISOgrProvider::GISGetNextFeatureAsWkT (wxString & wkbstring)
{
	OGRFeature *poFeature;
	OGRGeometry *poGeometry;
	char * myExport;
	
	poFeature = m_pLayer->GetNextFeature();
	poGeometry = poFeature->GetGeometryRef();
	if (poGeometry != NULL)
	{
		if (wkbFlatten(poGeometry->getGeometryType()) == wkbLineString )
		{
					
			OGRLineString * poLine = (OGRLineString *) poGeometry;
			
			poLine->exportToWkt(&myExport);
			wkbstring = wxString::FromAscii(myExport);
			delete myExport;
		}
		
		wxLogDebug(_T("WKT : %s"), wkbstring.c_str());
		
		m_iFeatureLoop ++;
		OGRFeature::DestroyFeature( poFeature );
		return TRUE;
			
	}
	
	OGRFeature::DestroyFeature( poFeature );
	wxLogDebug(_T("No Geometery / Feature found"));
	return FALSE;
}



bool GISOgrProvider::GISClose ()
{
	if (GISIsOpened())
	{
		OGRDataSource::DestroyDataSource( m_pDatasource);
		GISDataProvider::GISClose();
		return TRUE;
	}
	
	wxLogDebug(_T("Unable to close, no data open."));
	return FALSE;
}






/*************************  DB GIS PROVIDER (sqlite) ***************************/
GISDBProvider::GISDBProvider()
{
	//m_NumOfVector		= 0;
	m_pLayer			= NULL;
	m_pDatasource		= NULL;
	m_iFeatureLoop		= 0;
	
}



GISDBProvider::~GISDBProvider()
{
	
}


bool GISDBProvider::GISOpen (const wxString & filename)
{
	
	m_pDatasource = OGRSFDriverRegistrar::Open(filename.ToAscii(), TRUE );
    if( m_pDatasource != NULL )
    {
		GISDataProvider::GISOpen(filename);
//		m_pLayer = m_pDatasource->GetLayer(0);
//		m_pLayer->ResetReading();
		
		wxLogDebug(_T("Opening Database vector file OK"));
		return TRUE;
    }
	
	// if we couldn't open the vector file try to know why
	const char * myError = CPLGetLastErrorMsg();
	wxString myErrMsg = wxString::FromAscii(myError);
	wxLogDebug(_T("Open vector failed for file %s, error msg is : %s"), 
			   filename.c_str(), myErrMsg.c_str());
	return FALSE;
}


wxRect GISDBProvider::GISGetExtend ()
{
	
	return wxRect(0,0,0,0);
}


long GISDBProvider::GISGetFeatureCount ()
{
	//return m_pLayer->GetFeatureCount();
	return -1;
}

int GISDBProvider::GISGetLayerCount ()
{
	return m_pDatasource->GetLayerCount();
}


bool GISDBProvider::GISSetLayer (const wxString & layername)
{
	m_pLayer = m_pDatasource->GetLayerByName(layername.ToAscii());
	if (m_pLayer != NULL)
		return TRUE;
	
	wxLogDebug(_T("No layer with name : %s"), layername.c_str());
	return FALSE;
}


bool GISDBProvider::GISSetFeatureAsWkT (const wxString & wkbstring)
{
	OGRFeature *poFeature;
	OGRGeometry *poGeometry;
	wxString myString = wkbstring;
	char * myWKTChar = (char *) myString.GetWriteBuf(myString.Len());
	bool bReturn = TRUE;
	
	poFeature = OGRFeature::CreateFeature(m_pLayer->GetLayerDefn());
	
	OGRSpatialReference  ref;
    OGRGeometry * new_geom;
    OGRErr err = OGRGeometryFactory::createFromWkt(&myWKTChar, &ref, &new_geom);
	
	poFeature->SetGeometry(new_geom);
	if( m_pLayer->CreateFeature( poFeature ) != OGRERR_NONE )
	{
		wxLogDebug(_T("Failed to create feature"));
		bReturn = FALSE;
	}
	
	OGRFeature::DestroyFeature( poFeature );
	return bReturn;
}


bool GISDBProvider::GISGetNextFeatureAsWkT (wxString & wkbstring)
{
//	OGRFeature *poFeature;
//	OGRGeometry *poGeometry;
//	char * myExport;
//	
//	poFeature = m_pLayer->GetNextFeature();
//	poGeometry = poFeature->GetGeometryRef();
//	if (poGeometry != NULL)
//	{
//		if (wkbFlatten(poGeometry->getGeometryType()) == wkbLineString )
//		{
//			
//			OGRLineString * poLine = (OGRLineString *) poGeometry;
//			
//			poLine->exportToWkt(&myExport);
//			wkbstring = wxString::FromAscii(myExport);
//			delete myExport;
//		}
//		
//		wxLogDebug(_T("WKT : %s"), wkbstring.c_str());
//		
//		m_iFeatureLoop ++;
//		OGRFeature::DestroyFeature( poFeature );
//		return TRUE;
//		
//	}
//	
//	OGRFeature::DestroyFeature( poFeature );
//	wxLogDebug(_T("No Geometery / Feature found"));
	return FALSE;
}



bool GISDBProvider::GISClose ()
{
	if (GISIsOpened())
	{
		OGRDataSource::DestroyDataSource( m_pDatasource);
		GISDataProvider::GISClose();
		return TRUE;
	}
	
	wxLogDebug(_T("Unable to close, no data open."));
	return FALSE;
}




