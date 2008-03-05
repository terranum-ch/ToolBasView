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

bool GISDBProvider::GISOpen(DataBase * handle)
{
	if (handle != NULL)
	{
		m_pActiveDB = handle;
		GISDataProvider::GISOpen(m_pActiveDB->DataBaseGetName());
		return TRUE;
		
	}
	wxLogDebug(_T("Database handle is null..."));
	return FALSE;
	
}


OGREnvelope * GISDBProvider::GISGetExtend ()
{
	OGREnvelope * psExtent = new OGREnvelope();
	OGREnvelope oEnv;
	MYSQL_ROW row;
	unsigned long *  row_length;
	
	// query for the geometry enveloppe for all lines
	wxString sSentence = _T("SELECT Envelope(OBJECT_GEOMETRY) FROM ") + m_LayerName;
	if (m_pActiveDB->DataBaseQuery(sSentence))
	{
		// init extend based on the first object
		// to avoid 0 values for Xmin.
		row_length = m_pActiveDB->DataBaseGetNextRowResult(row);
		OGRGeometry *poGeometry = GISCreateDataBaseGeometry(row, row_length);
		poGeometry->getEnvelope(&oEnv);
		psExtent->MinX = oEnv.MinX;
		psExtent->MinY = oEnv.MinY;
		delete poGeometry;
		
		// loop all lines
		while (1)
		{
			row_length = m_pActiveDB->DataBaseGetNextRowResult(row);
			if (row_length == NULL)
				break;
			
			// compute the geometry and get the xmin xmax, ymin, ymax
			OGRGeometry *poGeometry = GISCreateDataBaseGeometry(row, row_length);
			if ( poGeometry != NULL )
			{
				poGeometry->getEnvelope(&oEnv);
				if (oEnv.MinX < psExtent->MinX) 
					psExtent->MinX = oEnv.MinX;
				if (oEnv.MinY < psExtent->MinY) 
					psExtent->MinY = oEnv.MinY;
				if (oEnv.MaxX > psExtent->MaxX) 
					psExtent->MaxX = oEnv.MaxX;
				if (oEnv.MaxY > psExtent->MaxY) 
					psExtent->MaxY = oEnv.MaxY;
			}
			delete poGeometry;
		}
		return psExtent;
		
	}
	
	wxLogDebug(_T("Error computing extend : %s "),
			   m_pActiveDB->DataBaseGetLastError().c_str());
	return NULL;	
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


bool GISDBProvider::GISSetActiveLayer (const wxString & layername)
{
	// we check that the layer name exists
	wxString sSentence = _T("SHOW TABLES LIKE \"") + layername + _T("\"");
	
	if (m_pActiveDB->DataBaseQuery(sSentence))
	{
		// ok the table exist
		if (m_pActiveDB->DataBaseHasResult())
		{
			m_LayerName = layername;
			return TRUE;
		}
		
	}
	// nothing returned, the layer dosen't exist.
	wxLogDebug(_T("No layer with name : %s"), layername.c_str());
	return FALSE;
}


OGRLayer * GISDBProvider::GISGetLayer (const wxString & layername)
{
//	// do not delete the returned layer... properties of datasource
//	OGRLayer * myLayer = m_pDatasource->GetLayerByName(layername.ToAscii());
//	if (myLayer == NULL)
//	{
//		wxLogDebug(_T("No layer with name : %s"), layername.c_str());
//	}
//	return myLayer;
	return NULL;
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

// array string is not used for mysql
bool GISDBProvider::GISComputeIndex (const wxArrayString & fields, const wxString & table)
{
	wxString sSentence = wxString::Format(_T("CREATE SPATIAL INDEX sp_index ON %s (OBJECT_GEOMETRY);"),
										  table.c_str());
	
//	// append columns for size of string array
//	for (unsigned int i = 0; i<fields.GetCount(); i++)
//	{
//		sSentence.Append(wxString::Format(_T("%s,"),(fields.Item(i)).c_str()));
//	}
//	
//	// remove the last character (the last comma)
//	sSentence.RemoveLast();
//	sSentence.Append(_T("); "));
	
	// process the query and return true if ok
	if(m_pActiveDB->DataBaseQueryMultiple(sSentence)==0)
	{
		return TRUE;
	}
		
	wxLogDebug(_T("Not able to create index : %s"),
			   m_pActiveDB->DataBaseGetLastError().c_str());
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


// bcomputextend is not used for mysql
bool GISDBProvider::GISSetFeatureAsWkTBuffer (const wxArrayString & featurelist, bool bComputeExtend)
{
	OGREnvelope myEnveloppe;
	unsigned int i;
	wxString sSentence = _T("");
	
		
	
		for (i=0; i<featurelist.GetCount();i++)
		{
			sSentence.Append(wxString::Format(_T("INSERT INTO %s")
											  _T(" VALUES (-1, GeomFromText('%s')); "),
											  m_LayerName.c_str(),
											  featurelist.Item(i).c_str()));
		}

		
	//wxLogDebug(sSentence);

	if (m_pActiveDB->DataBaseQueryMultiple(sSentence) == 0)
	{
		return TRUE;
	}
	wxLogDebug (_T("Error is : %s"), m_pActiveDB->DataBaseGetLastError().c_str());
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
		//OGRDataSource::DestroyDataSource( m_pDatasource);
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
	//char * myBuffer = NULL;
	OGRGeometry * myFoundLine = NULL;
	OGRLayer * myTempLayer = NULL;
	
	// step one, create the buffer for point
	OGRPolygon * myBuffPoint = (OGRPolygon *) GISCreateBufferPoint(x, y, ibuffer);
	if (myBuffPoint != NULL)
	{	
		// step two, calculate  use the spatial index
		//myTempLayer = GISSetSpatialFilter(m_pLayer, myBuffPoint);
		myTempLayer = GISSetSpatialFilter(myBuffPoint);
		if (myTempLayer != NULL)
		{
			// step three, find the line
			myFoundLine = GISSearchLines(myTempLayer, myBuffPoint, iFidFound);
			
			wxLogDebug(_T("Number of feature parsed in spatial index is %d"), myTempLayer->GetFeatureCount());
			
		}
		
		
		// delete the temporary layer
		GISDeleteSpatialFilter(myTempLayer);
			
		//delete myBuffer;
	}
	
	
	return myFoundLine;
}



OGRLayer * GISDBProvider::GISSetSpatialFilter (OGRGeometry * enveloppe)
{
	// create an enveloppe
	OGREnvelope myEnveloppe;
	enveloppe->getEnvelope(&myEnveloppe);
	OGRLayer * myLayer;
	
	// filter the database and extract in a view all
	// line contained in the bb.
	wxString sSentence = wxString::Format(_T("SELECT * FROM %s WHERE MINX <= %f ")
										  _T("AND MAXX >= %f AND MINY <= %f AND MAXY >= %f"),
										  m_LayerName.c_str(),
										  myEnveloppe.MaxX,
										  myEnveloppe.MinX,
										  myEnveloppe.MaxY,
										  myEnveloppe.MinY);
	 myLayer = m_pDatasource->ExecuteSQL(sSentence.ToAscii(), enveloppe, NULL);
	
	
	if (myLayer == NULL)
		wxLogDebug(_T("Not able to create spatial filter"));
	//layer->SetSpatialFilter(enveloppe);
	return myLayer;
	
}


bool	GISDBProvider::GISDeleteSpatialFilter (OGRLayer * templayer)
{
	m_pDatasource->ReleaseResultSet(templayer);
	return TRUE;
	
}


OGRGeometry * GISDBProvider::GISCreateDataBaseGeometry(MYSQL_ROW & row, unsigned long * length)
{
	OGRGeometry * geometry = NULL;
	// Geometry columns will have the first 4 bytes contain the SRID.
	OGRGeometryFactory::createFromWkb(((unsigned char *)row[0]) + 4, 
												  NULL,
												  &geometry,
												  length[0] - 4 );
	return geometry;
}



/********************************* PRIVATE GIS DB FUNCTION *************************/

// delete the retruned char when not more needed
OGRGeometry * GISDBProvider::GISCreateBufferPoint (const double & x, const double &y, const int & ibuffer)
{
	OGRPoint myPoint;
	myPoint.setX (x);
	myPoint.setY (y);
	
	// show in the log
	//wxLogMessage (_("Selected point : %.*f, %.*f, buffer = %d"),2,x,2,y,ibuffer);
	
	return myPoint.Buffer(ibuffer, 20);
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
					iFID = poFeature->GetFieldAsInteger(0);
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





