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


OGREnvelope * GISDataProvider::GISGetExtend ()
{

	return NULL;
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


OGREnvelope * GISOgrProvider::GISGetExtend ()
{
	// if returned value is not NULL then 
	// caller must delete OGREnveloppe *
	// otherwise OGREnveloppe is deleted
	// here...
	OGREnvelope * myEnveloppe = new OGREnvelope();
	// compute the extend
	if (m_pLayer->GetExtent(myEnveloppe, TRUE) == OGRERR_NONE)
	{
		return myEnveloppe;
	}
	else 
	{
		delete myEnveloppe;
	}
	return NULL;
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
	m_LayerName			= _T("");
	
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


OGREnvelope * GISDBProvider::GISGetExtend ()
{
	OGREnvelope * myEnveloppe = new OGREnvelope();
	
	// compute the extend using query on spatial index
	if(m_pActiveDB->DataBaseQuery(_T("SELECT MIN(MINX) FROM ") + m_LayerName))
		myEnveloppe->MinX = m_pActiveDB->DataBaseGetResultAsDouble();
	if(m_pActiveDB->DataBaseQuery(_T("SELECT MIN(MINY) FROM ") + m_LayerName))
		myEnveloppe->MinY = m_pActiveDB->DataBaseGetResultAsDouble();
	if(m_pActiveDB->DataBaseQuery(_T("SELECT MAX(MAXX) FROM ") + m_LayerName))
		myEnveloppe->MaxX = m_pActiveDB->DataBaseGetResultAsDouble();
	if(m_pActiveDB->DataBaseQuery(_T("SELECT MAX(MAXY) FROM ") + m_LayerName))
		myEnveloppe->MaxY = m_pActiveDB->DataBaseGetResultAsDouble();
		
	
	return myEnveloppe;
}


long GISDBProvider::GISGetFeatureCount ()
{
	wxString sSentence = wxString::Format(_T("SELECT  COUNT(*) FROM %s"),
										  m_LayerName.c_str());
	
	if (m_pActiveDB->DataBaseQuery(sSentence))
	{
	  return m_pActiveDB->DataBaseGetResultAsInt();
	}
	// bellow function is slower as the one used
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
	{
		m_LayerName = layername;
		return TRUE;
	}
	
	m_LayerName = _T("");
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


bool GISDBProvider::GISComputeIndex (const wxArrayString & fields, const wxString & table)
{
	wxString sSentence = wxString::Format(_T("CREATE INDEX index_%s ON %s ("),
										  table.c_str(), table.c_str());
	
	// append columns for size of string array
	for (unsigned int i = 0; i<fields.GetCount(); i++)
	{
		sSentence.Append(wxString::Format(_T("%s,"),(fields.Item(i)).c_str()));
	}
	
	// remove the last character (the last comma)
	sSentence.RemoveLast();
	sSentence.Append(_T("); "));
	
	// process the query and return true if ok
	if(m_pActiveDB->DataBaseQueryMultiple(sSentence)==0)
	{
		return TRUE;
	}
	
	wxLogDebug(_T("Not able to create index, sentence is : %s"),
			   sSentence.c_str());
	return FALSE;
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


OGRGeometry * GISDBProvider:: GISGetFeatureByBuffer (const double & x,
													 const double & y, const int & ibuffer,
													 int & iFidFound)
{
	char * myBuffer = NULL;
	int iFidLineFound = 0;
	OGRGeometry * myFoundLine = NULL;
	
	// step one, create the buffer for point
	myBuffer = GISCreateBufferPoint(x, y, ibuffer);
	if (myBuffer != NULL)
	{	
		// create the point->polygon geometry
		OGRPolygon * myBuffPoint = new OGRPolygon();
		myBuffPoint->importFromWkt(&myBuffer); // mybuffer not more needed...
		
	
		// step two, find the line
		myFoundLine = GISSearchLines(m_pLayer, myBuffPoint, iFidFound);
			
		delete myBuffer;
	}
	
	
	return myFoundLine;
}


/********************************* PRIVATE GIS DB FUNCTION *************************/

// delete the retruned char when not more needed
char * GISDBProvider::GISCreateBufferPoint (const double & x, const double &y, const int & ibuffer)
{
	OGRPoint myPoint;
	myPoint.setX (x);
	myPoint.setY (y);
	char * myChar = NULL; 
	
	// export to GEOS and compute the buffer
	GEOSGeom g1 = myPoint.exportToGEOS();
	GEOSGeom g2 = GEOSBuffer(g1,ibuffer,20);
	myChar = GEOSGeomToWKT(g2);
	
	// show in the log
	wxLogMessage (_("Selected point : %.*f, %.*f, buffer = %d"),2,x,2,y,ibuffer);
	
	return myChar;
}


OGRGeometry * GISDBProvider::GISSearchLines (OGRLayer * layer, OGRGeometry * pointbuffer, int & iFID)
{
	iFID = -1;
	int i=0;
	bool bStatus = FALSE;
	//		
	OGRFeature *poFeature;
	OGRGeometry *poGeometry;

	
	// get first layer
	layer->ResetReading();
	
	// show an busy cursor, will automaticaly be destroyed after
	// this function.
	wxBusyCursor wait;
	
	// itterate all the lines
	while( (poFeature = layer->GetNextFeature()) != NULL )
	{
		
		poGeometry = poFeature->GetGeometryRef();
		
		if( poGeometry != NULL)
		{
			if (wkbFlatten(poGeometry->getGeometryType()) == wkbLineString )
			{
				OGRLineString * poLine = (OGRLineString *) poGeometry;
				
				// if we found the selected line
				if(pointbuffer->Intersects(poLine))
				{
					// get the selected line FID
					iFID = i;
					bStatus = TRUE;
					// get the geometry
					break;
				}
			}
			i++;
		}
	}
	// delete the feature ??
	OGRFeature::DestroyFeature(poFeature);

	// return the Geometry
	if (bStatus == TRUE)
		return poGeometry;
	
	return NULL;	
}



