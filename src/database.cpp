/***************************************************************************
								database.cpp
				Basic function for connecting a MySQL embedded database 
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

/*!
    @file database.cpp
    @brief code for the class DataBase
	
	The Database class is used for Opening, creating and processing request
	to a MySQL embedded Database.
    @author Lucien Schreiber (c) CREALP 2007
*/


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "database.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "../include/database.h"
#include <wx/filename.h> // to create the database path and name.


//----------------------------------------------------------------------------
// DataBase
//----------------------------------------------------------------------------
DataBase::DataBase()
{
	IsDatabaseOpen = FALSE;
	m_pDB = NULL;
}

DataBase::~DataBase()
{
}



bool DataBase::DataBaseOpen (wxString path, enum Lang_Flag flag)
{
	int iRetour = 0;
	wxString sFullNamePath = _T("");
	
	// conversion from path, return values in m_DBName and m_DBPath
	// and check that no value is empty
	if (DataBaseConvertFullPath(path))
	{
		// construct the full database name (path, name, . and extension)
		sFullNamePath = m_DBPath + m_DBName + _T(".") + DATABASE_EXTENSION_STRING;
		
		// try opening the database
		//sqlite3_open_v2((const char*)sFullNamePath.mb_str(wxConvUTF8), &m_pDB,  SQLITE_OPEN_READWRITE);
		iRetour = sqlite3_open((const char*)sFullNamePath.mb_str(wxConvUTF8), &m_pDB);
		
		if (iRetour != 0)
		{
			IsDatabaseOpen = FALSE;
			wxLogMessage(_("Error opening the database. Error code is [%d]"), iRetour);
			return FALSE;
		}
		
		IsDatabaseOpen = TRUE;
		return TRUE;
	}
	return FALSE;
	
}

bool DataBase::DataBaseClose()
{
	int iRetour = sqlite3_close(m_pDB);
	if (iRetour != 0)
	{
		wxLogMessage(_("Error closing the database return code is [%d]"), iRetour);
		return FALSE;
	}
	
	wxLogDebug(_T("Closing database OK"));
	return TRUE;
}

bool DataBase::DataBaseIsOpen()
{
return IsDatabaseOpen;
}

wxArrayString DataBase::DataBaseListTables()
{
	// getting a list of all tables from a
	// database is as simple as passing
	// this sql request
	//SELECT name FROM sqlite_master
	//WHERE type='table'
	//ORDER BY name;
	wxArrayString myStingArray;
	
	if (DataBaseQuery(_T("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name")))
	{
		// have we got some results ?
		if (DataBaseHasResult())
		{
			// do not take into account the first item from the array (column name)
			for (int i = 0; i< (m_nCols * m_nRow); i++)
			{
				myStingArray.Add(wxString(m_Result[i+1], wxConvUTF8));
			}
			sqlite3_free_table(m_Result);
		}
		
	}
	return myStingArray;
}


wxString DataBase::DatabaseGetVersion()
{
	wxString myVersionString;
	myVersionString = wxString::FromAscii(SQLITE_VERSION);
	return myVersionString;
}



wxArrayString DataBase::DatabaseListFields(wxString sTable)
{
	wxArrayString myStingArray;
	wxString sSentence = wxString::Format(_T("PRAGMA table_info(`%s`)"), sTable.c_str());
	int iName = 7;
	
	if (DataBaseQuery(sSentence))
	{
		if (DataBaseHasResult())
		{
		// do not take into account the first item from the array (column name)
		for (int i = 0; i< (m_nRow); i++)
		{
			myStingArray.Add(wxString(m_Result[iName], wxConvUTF8));
			iName = iName + 6;
		}
		sqlite3_free_table(m_Result);
		}
	}
	return myStingArray;
}

bool DataBase::DataBaseGetAllTableContent(wxString sTable)
{
	wxString sSentence = wxString::Format(_T("SELECT * FROM `%s`"), sTable.c_str());
	  
	if (DataBaseQuery(sSentence))
	{
		if (DataBaseHasResult())
		{
			m_resultNumber = 0;
			return TRUE;
		}
	
	}	
	return FALSE;
}


wxArrayString DataBase::DataBaseGetNextResult()
{
//	MYSQL_ROW record;
	wxArrayString myRowResult;
	
	// get the rows of data one by one 
	// and clear results when returning the last line
	if (m_resultNumber < (m_nCols * m_nRow))
	{
		// skip the first row (introduction of data)
		m_resultNumber = m_resultNumber + m_nCols;		
		for (int i=0; i < m_nCols; i++)
		{
			myRowResult.Add(wxString(m_Result[i+m_resultNumber], wxConvUTF8));
		}

	}
	else
	{
		sqlite3_free_table(m_Result);
	}

	return myRowResult;
}



bool DataBase::DataBaseTableExist(const wxString & tableName)
{
//	MYSQL_ROW record;
//	// look for an existing table
//	wxString sSentence = wxString::Format (_T("SHOW TABLES  LIKE  '%s'"), tableName.c_str());
//	
//
//	if (DataBaseQuery(sSentence))
//	{
//		// if the query has passed...
//		// then we check the results
//		record = mysql_fetch_row(pResults);
//		if(record != NULL)
//		{
//			return TRUE;
//		}
//	}
	return FALSE;
	
	
}






int DataBase::DataBaseGetResultAsInt()
{
//	MYSQL_ROW record;
	int iReturnedValue = -1;
	
//	if (m_resultNumber > 0 && pResults != NULL)
//	{
//		record = mysql_fetch_row(pResults);
//		if(record != NULL)
//		{
//			 iReturnedValue =  atoi(record[0]);
//		}
//		else 
//		{
//			// clean
//			m_resultNumber=0;
//			mysql_free_result(pResults);
//		}		
//	}
	
	return iReturnedValue;

}


bool DataBase::DataBaseIsTableEmpty(const wxString & tableName)
{
//	wxString sSentence = wxString::Format(_T("SELECT * FROM %s"), tableName.c_str());
//	
//	// return TRUE if the sentence was OK and
//	// return no results (table is empty)
//	if (DataBaseQuery(sSentence))
//		if(DataBaseHasResult() == FALSE)
//			return TRUE;
//	
//	// table is not empty
//	wxLogDebug (_T("Table [%s] is not empty or request error"), tableName.c_str());
	return FALSE;
}



bool DataBase::DataBaseQueryNoResult(wxString myQuery)
{
//	MYSQL_RES *results;
//	int iRetour = mysql_query(pMySQL, (const char*)myQuery.mb_str(wxConvUTF8) );
//	results = mysql_store_result(pMySQL);
//	mysql_free_result(results);
//	
//	if (iRetour == 0)
//		return TRUE;
//	
	return FALSE;
}

bool DataBase::DataBaseQuery(const wxString & myQuery)
{
	int iRetour = 0;
	char * zErrMsg = 0;
	
	// m_pDB,  myQuery.mb_str(wxMBConvUTF8),NULL,NULL,&zErrMsg
	iRetour = sqlite3_get_table(m_pDB, (const char*) myQuery.mb_str(wxConvUTF8),
								&m_Result, &m_nRow, &m_nCols, &zErrMsg);
	//iRetour =  sqlite3_exec(m_pDB,(const char*) myQuery.mb_str(wxConvUTF8),NULL, NULL, &zErrMsg);
	if (iRetour == SQLITE_OK)
	{
		wxLogDebug(_T("Query passed OK"));
		m_resultNumber = 0;
		return TRUE;
	}
	
	wxLogDebug(_T("Error during query. Error number is [%d], message is %s"), iRetour, zErrMsg);
	sqlite3_free(zErrMsg);
	return FALSE;
//	pResults = NULL;
//	int iRetour = mysql_query(pMySQL, (const char*)myQuery.mb_str(wxConvUTF8) );
//	if (iRetour == 0) 
//	{
//		pResults = mysql_store_result(pMySQL);
//		m_resultNumber = mysql_field_count(pMySQL);
//		return TRUE;
//	}
}


bool DataBase::DataBaseHasResult ()
{

	if (m_nCols > 0 || m_nRow > 0)
	{
		return TRUE;
	}
	return FALSE;
}


int DataBase::DataBaseQueryMultiple (const wxString & myQuery)
{
	int iRetour = 0;
	char * zErrMsg = 0;
	wxString sError = _T("");
	
	// pass the query to the database
	iRetour =  sqlite3_exec(m_pDB,(const char*) myQuery.mb_str(wxConvUTF8),NULL, NULL, &zErrMsg);
	if (iRetour == SQLITE_OK)
	{
		wxLogDebug(_T("Query passed OK"));
		return iRetour;
	}
	
	wxLogDebug(_T("Error during query"));
	sError = wxString::FromAscii(zErrMsg);
	//wxLogDebug(_T("Error during query. Error number is [%d], message is %s"), iRetour, zErrMsg);
	wxLogDebug(_T("Error during query. Error number is [%d], message was : %s"), iRetour, sError.c_str());
	
	sqlite3_free(zErrMsg);
	return iRetour;
}


int DataBase::DataBaseQueryReal (wxString myQuery)
{
//	MYSQL_RES *results;
//	//const char * mySentence = myQuery.c_str(); //mb_str(wxConvUTF8);
//
//	int iRetour = mysql_query(pMySQL,(const char*)myQuery.mb_str(wxConvUTF8));
//	results = mysql_store_result(pMySQL);
//	mysql_free_result(results);
//	return iRetour;
	return 0;

}

bool DataBase::DataBaseConvertFullPath(wxString fullpath)
{
	wxFileName myFileName (fullpath);
	
	// init private variables
	m_DBPath = myFileName.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
	m_DBName = myFileName.GetName();
	
	if (m_DBPath.IsEmpty() || m_DBName.IsEmpty())
	{
		return FALSE;
	}
	return TRUE;
}


wxString DataBase::DatabaseGetCharacterSet()
{
	// MY_CHARSET_INFO cs;
	// mysql_get_character_set_info(pMySQL,&cs);
	 
	// wxString sCharName(cs.csname, wxConvUTF8);
	 
//	 // compatibility with mysql 4...
//	 wxString sCharName(mysql_character_set_name (pMySQL), wxConvUTF8);
//	 return sCharName;
	return _T("");

}

wxString DataBase::DataBaseGetName()
{
	return m_DBName;
}

wxString DataBase::DataBaseGetPath()
{
	return m_DBPath;
}

bool DataBase::DataBaseCreateNew(wxString DataBasePath, wxString DataBaseName,enum Lang_Flag Flag)
{
	wxFileName sDBPathName (DataBasePath, DataBaseName, DATABASE_EXTENSION_STRING);	
	wxString myTempName = sDBPathName.GetFullPath();
	
	// init private variables
	m_DBPath = sDBPathName.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
	m_DBName = sDBPathName.GetName();
	
	
	int iRetour = sqlite3_open((const char*)myTempName.mb_str(wxConvUTF8), &m_pDB);
	// publish return code if != 0
	if (iRetour != 0)
	{
		IsDatabaseOpen = FALSE;
		wxLogError(_T("Error creating the database. Error code is [%d]"), iRetour);
		return FALSE;
	}
	IsDatabaseOpen = TRUE;
	return TRUE;
}


wxArrayString DataBase::DataBaseCutRequest (wxString theRequest)
{
	wxArrayString myArrayRequest;
	myArrayRequest = wxStringTokenize (theRequest,_T(";"));
	return myArrayRequest;
}

wxString DataBase::DataBaseConvertMYSQLPath(wxString originalPath)
{
//	wxArrayString myNewName;
	wxString myReturnPath;
//	wxFileName myOriginalName = wxFileName(originalPath,wxEmptyString);
//	
//	// get the separator
//	wxString mySeparator = myOriginalName.GetPathSeparator();
//	
//	// if separator != '/' we process the filename
//	if ( mySeparator != _T("/") )
//	{
//		myNewName = wxStringTokenize(originalPath,_T("\\"));
//		for (int i=0; i < (int)myNewName.Count(); i++)
//		{
//		myReturnPath += myNewName.Item(i);
//		myReturnPath += _T("/");	
//		}
//		
//	}
//	else 
//	{
//		return originalPath;
//	}

	return myReturnPath;
}


wxString DataBase::DataBaseGetSize (int iPrecision)
{
	
	wxFileName myDBPathName (m_DBPath, m_DBName, DATABASE_EXTENSION_STRING);
	wxLogDebug(_T("database name is %s"), myDBPathName.GetFullPath().c_str());
	wxString myDBSize = myDBPathName.GetHumanReadableSize();
	return wxString::Format(_("Database size is : %s"), myDBSize.c_str());
	
}

bool DataBase::DataBaseSetCharacterSet (enum Lang_Flag myFlag)
{
//	wxString myRequest;
//
//	switch(myFlag)
//	{
//
//	case LANG_LATIN1:
//		myRequest = _T("SET CHARACTER SET 'latin1'");
//		break;
//
//	default:
//	case LANG_UTF8:
//		myRequest = _T("SET CHARACTER SET 'utf8'");
//		break;
//	};
//
//	if(mysql_query(pMySQL,(const char*)myRequest.mb_str(wxConvUTF8))==0)
//	{
//		return TRUE;
//	}
//

	return FALSE;
}

