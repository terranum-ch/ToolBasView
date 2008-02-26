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
		m_iFeatureLoop ++;
		OGRFeature::DestroyFeature( poFeature );
		return TRUE;
			
	}
	
	OGRFeature::DestroyFeature( poFeature );
	wxLogDebug(_T("No Geometery / Feature found"));
	return FALSE;
}


bool GISOgrProvider::GISGetNextFeatureAsWktBuffer(wxArrayString * featurelist, int iBufferSize)
{
	OGRGeometry *poGeometry;
	bool bReturnValue = FALSE;
	
	// loop for reading multiple feature in memory
	// specify number of feature to read with iBuffersize
	for (int i=0; i<iBufferSize; i++)
	{
		OGRFeature *poFeature;
		char * myExport;
		if ((poFeature = m_pLayer->GetNextFeature()) != NULL)
		{
			poGeometry = poFeature->GetGeometryRef();
			if (poGeometry != NULL)
			{
				if (wkbFlatten(poGeometry->getGeometryType()) == wkbLineString )
				{
					
					OGRLineString * poLine = (OGRLineString *) poGeometry;
					
					poLine->exportToWkt(&myExport);
					featurelist->Add(wxString::FromAscii(myExport));
					delete myExport;
					bReturnValue = TRUE;
				}
								
				OGRFeature::DestroyFeature( poFeature );
			}
			else
			{
				wxLogDebug(_T("No Geometery / Feature found"));
				break;
			}
		}
		else
			break;
		
	}
	return bReturnValue;
	
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



bool GISDBProvider::GISComputeBoundingBox (wxString  wktstring, OGREnvelope * enveloppe)
{
	OGRSpatialReference mySpatRef;
	OGRLineString * myGeom;
	bool bReturnValue = FALSE;
	//OGREnvelope myEnveloppe;

		
	std::string nomtr((char const*)wktstring.mb_str(*wxConvCurrent));
	char * mypChar = (char *) nomtr.c_str();
	
	OGRErr myErr;
	myErr = OGRGeometryFactory::createFromWkt( &mypChar, &mySpatRef, (OGRGeometry**) &myGeom);
	
	// check that a geometry was created
	if (myErr == 0)
	{
		// get the bounding box of the geometry
		myGeom->getEnvelope(enveloppe);
		bReturnValue = TRUE;
		
		// delete the geometry
		delete myGeom;
	}
	else
		wxLogDebug(_T("Unable to create geometry, error is %d"), myErr);
	
	//delete mypChar;
	return bReturnValue;
}



bool GISDBProvider::GISSetFeatureAsWkT (const wxString & wkbstring,  bool bComputeExtend)
{
	//double * rect;
	OGREnvelope myEnveloppe;
	wxString sSentence = _T("");
	
	// if we must compute the bounding box for new added line
	if(bComputeExtend)
	{
		
		// check if we can compute the enveloppe (a.k.a bounding box)
		if(GISComputeBoundingBox(wkbstring, &myEnveloppe))
		{
			sSentence = wxString::Format(_T("INSERT INTO GENERIC_LINES ")
										 _T("(WKT_GEOMETRY, MINX, MINY, MAXX, MAXY)")
										 _T("VALUES (\"%s\", %f, %f, %f, %f)"),
										 wkbstring.c_str(), myEnveloppe.MinX, myEnveloppe.MinY,
										 myEnveloppe.MaxX, myEnveloppe.MaxY);
		}
		
	}
	else
	{
		sSentence = wxString::Format(_T("INSERT INTO GENERIC_LINES (WKT_GEOMETRY) VALUES (\"%s\")"),
									 wkbstring.c_str());
	}
	
	// add WKT string to the database
	// warning the table must have a WKT_GEOMETRY field
	if (m_pActiveDB->DataBaseQuery(sSentence))
	{
		return TRUE;
	}
	return FALSE;
}


bool GISDBProvider::GISSetFeatureAsWkTBuffer (const wxArrayString & featurelist, bool bComputeExtend)
{
	OGREnvelope myEnveloppe;
	unsigned int i;
	wxString sSentence = _T("BEGIN TRANSACTION test; ");
	
	// if we must compute the bounding box for new added line
	// this will allow creation of false spatial index
	// for faster retriving of data
	if(bComputeExtend)
	{
		
		// check if we can compute the enveloppe (a.k.a bounding box)
		for (i=0; i<featurelist.GetCount();i++)
		{
			if(GISComputeBoundingBox(featurelist.Item(i), &myEnveloppe))
			{
				sSentence.Append(wxString::Format(_T("INSERT INTO GENERIC_LINES ")
											 _T("(WKT_GEOMETRY, MINX, MINY, MAXX, MAXY)")
											 _T("VALUES (\"%s\", %f, %f, %f, %f); "),
											 (featurelist.Item(i)).c_str(), myEnveloppe.MinX, myEnveloppe.MinY,
											 myEnveloppe.MaxX, myEnveloppe.MaxY));
			}
			else 
			{
				wxLogDebug(_T("Error computing bounding box"));
			}
		}

		
	}
	
	// no bounding box needed for new added line
	else
	{
		
		for (i=0; i<featurelist.GetCount();i++)
		{
			sSentence.Append(wxString::Format(_T("INSERT INTO GENERIC_LINES (WKT_GEOMETRY) VALUES (\"%s\"); "),
							 (featurelist.Item(i)).c_str()));
		}
		
	}
	
	sSentence.Append(_T(" END TRANSACTION test;"));
	
	// add WKT string to the database
	// warning the table must have a WKT_GEOMETRY field
	if (m_pActiveDB->DataBaseQueryMultiple(sSentence) == 0)
	{
		return TRUE;
	}
	return FALSE;
	
	
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




