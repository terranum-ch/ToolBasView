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
#include <geos_c.h>			// for geos (Geographic data processing)
#include "database.h"		// for GISDBProvider to support direct com with DB

enum GISPROVIDER_SUPPORTED_TYPE
{
	GISTYPE_ESRI_SHP = 0,
	GISTYPE_TIFF,	
};
const int GISPROVIDER_SUPPORTED_TYPE_NUMBER = 2;


/***************************************************************************//**
 @brief List of supported formats
 @author Lucien Schreiber (c) CREALP 2008
 @date 22 September 2008
 *******************************************************************************/
enum GISSPATIAL_TYPE
{
	GISSPATIAL_ERROR = -1,
	GISSPATIAL_POINT = 0,
	GISSPATIAL_LINE = 1,
	GISSPATIAL_POLYGON =2
};


/*************************  GENERIC GIS PROVIDER ***************************/
class GISDataProvider : public wxObject
{
private:
DECLARE_CLASS (GISDataProvider);
	bool m_GISisOpen;

protected:

public:
	GISDataProvider();

	~GISDataProvider();

	virtual bool GISOpen(const wxString &filename);

	virtual OGREnvelope *GISGetExtend();

	virtual bool GISClose();

	bool GISIsOpened();

};



/*************************  OGR GIS PROVIDER (SHP,...) ***************************/
class GISOgrProvider : public GISDataProvider
{
protected:
	OGRLayer *m_Layer;
	GDALDataset *m_Datasource;
	//long				m_NumOfVector;
	unsigned int m_iFeatureLoop;
	GISSPATIAL_TYPE m_LayerSpatType;

	//bool GISGetNextFeatureAsWktBufferPoint (wxArrayString * featurelist, int iBufferSize);
	//bool GISGetNextFeatureAsWktBufferLine (wxArrayString * featurelist, int iBufferSize);


public:
	GISOgrProvider();

	~GISOgrProvider();

	GISSPATIAL_TYPE GetLayerSpatialType();

	virtual bool GISOpen(const wxString &filename);

	virtual OGREnvelope *GISGetExtend();

	virtual long GISGetFeatureCount();

	virtual bool GISGetNextFeatureAsWkT(wxString &wkbstring);

	virtual bool GISGetNextFeatureAsWktBuffer(wxArrayString *featurelist, int iBufferSize);

	virtual bool GISClose();

};


/*************************  DATABASE GIS PROVIDER (sqlite) ***************************/
class GISDBProvider : public GISDataProvider
{
private:

	OGRLayer *m_Layer;
	wxString m_LayerName;
	GDALDataset *m_Datasource;
	//long				m_NumOfVector;
	unsigned int m_iFeatureLoop;
	DataBase *m_pActiveDB;

	OGRGeometry *GISCreateBufferPoint(const double &x, const double &y, const int &ibuffer);

	OGRGeometry *GISSearchLines(OGRLayer *layer, OGRGeometry *pointbuffer, int &iFID);


public:
	GISDBProvider();

	~GISDBProvider();

	virtual bool GISOpen(const wxString &filename);

	bool GISOpen(DataBase *handle);

	virtual OGREnvelope *GISGetExtend();

	virtual long GISGetFeatureCount();

	virtual bool GISGetNextFeatureAsWkT(wxString &wkbstring);

	virtual bool GISSetFeatureAsWkT(const wxString &wkbstring, bool bComputeExtend = TRUE);

	virtual bool GISSetFeatureAsWkTBuffer(const wxArrayString &featurelist, bool bComputeExtend = TRUE);

	virtual int GISGetLayerCount();

	virtual OGRLayer *GISGetLayer(const wxString &layername);

	virtual bool GISSetActiveLayer(const wxString &layername);

	virtual void GISSetActiveDatabase(DataBase *pDB)
	{ m_pActiveDB = pDB; }

	virtual bool GISComputeBoundingBox(wxString wktstring, OGREnvelope *enveloppe);

	virtual bool GISComputeIndex(const wxArrayString &fields, const wxString &table);

	virtual bool GISClose();

	// Search functions //
	virtual OGRGeometry *GISGetFeatureByBuffer(const double &x,
											   const double &y, const int &ibuffer,
											   int &iFidFound);

	bool GISSetSpatialFilter(const wxString &table, OGRGeometry *enveloppe);

	bool GISDeleteSpatialFilter(OGRLayer *templayer);

	// create function
	OGRGeometry *GISCreateDataBaseGeometry(MYSQL_ROW &row, const tmArrayULong &length, int geometry_col = 0);

};



#endif
