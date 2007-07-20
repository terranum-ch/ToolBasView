/*!
@header database.cpp
 @abstract   (description)
 @discussion (description)
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
}

DataBase::~DataBase()
{
}



bool DataBase::DataBaseOpen (wxString path)
{
	// conversion from path
	DataBaseConvertFullPath(path);
	wxString datadir = _T("--datadir=") + m_DBPath;
	
	static char *server_args[] = {
		"this_program",       /* this string is not used */
		(char*) datadir.c_str(),
		"--language=./share/english",
		"--skip-innodb",
		"--port=3309",
		"--character-sets-dir=./share/charsets", 
		//"--default-charcater-set=latin1"
		
		// "--datadir=/Users/Lucien/DATA/PRJ/TOOLMAP/TestBDD/BDD/data"
		
	};
	static char *server_groups[] = {
		"embedded",
		"server",
		"this_program_SERVER",
		(char *)NULL
	};
	
	int num_elements = (sizeof(server_args) / sizeof(char *));
	
	
	
	if(mysql_server_init(num_elements, server_args, server_groups)==0)
	{
		pMySQL = mysql_init(NULL);
		
		if(mysql_real_connect(pMySQL,NULL,NULL,NULL,m_DBName,3309,NULL,0))
		{
			IsDatabaseOpen = TRUE;
			return TRUE;
		}	
		
	}
	
	
	// if something goes wrong
	return FALSE;
	
	
	
	
}

bool DataBase::DataBaseClose()
{
	mysql_server_end();
	IsDatabaseOpen = FALSE;
}



wxArrayString DataBase::DataBaseListTables()
{
	MYSQL_RES *results;
	MYSQL_ROW record;
	wxArrayString myStingArray;
	
	if(mysql_query(pMySQL,_T("SHOW TABLES;"))==0)
	{
		results = mysql_store_result(pMySQL);
		
		while((record = mysql_fetch_row(results)))
		{
			myStingArray.Add(record[0]);
		}
		
		// clean
		mysql_free_result(results);
		
	}
	return myStingArray;
}


wxString DataBase::DatabaseGetVersion()
{
	wxString myVersionString;
	myVersionString.Printf(_T("%s"),mysql_get_client_info());
	return myVersionString;
}



wxArrayString DataBase::DatabaseListFields(wxString sTable)
{
	MYSQL_RES *results;
	MYSQL_ROW record;
	wxArrayString myStingArray;
	
	if(mysql_query(pMySQL,_T("SHOW COLUMNS FROM ") + sTable)==0)
	{
		results = mysql_store_result(pMySQL);
		while((record = mysql_fetch_row(results)))
		{
			myStingArray.Add(record[0]);
		}
		
		
		
		// clean
		mysql_free_result(results);
		
	}
	return myStingArray;

}

bool DataBase::DataBaseGetAllTableContent(wxString sTable)
{
	m_resultNumber = 0;
	if (mysql_query(pMySQL,_T("SELECT * FROM ") + sTable)==0) 
	{
		pResults = mysql_store_result(pMySQL);
		m_resultNumber = mysql_field_count(pMySQL);
		return TRUE;
	}
	return FALSE;
}


wxArrayString DataBase::DataBaseGetNextResult()
{
	MYSQL_ROW record;
	wxArrayString myRowResult;
	
	if (m_resultNumber > 0 && pResults != NULL); 
	{
		if(record = mysql_fetch_row(pResults))
		{
			for (int i = 0; i<m_resultNumber; i++) 
			{
				myRowResult.Add(record[i]);
			}
		}
		else 
		{
			// clean
			m_resultNumber=0;
			mysql_free_result(pResults);
		}
		
	}
	
	return myRowResult;

}


int DataBase::DataBaseQuery(wxString myQuery)
{
	MYSQL_RES *results;
	int iRetour = mysql_query(pMySQL,myQuery);
	results = mysql_store_result(pMySQL);
	mysql_free_result(results);
	return iRetour;
}


bool DataBase::DataBaseConvertFullPath(wxString fullpath)
{
	wxArrayString myDirArray;
	
	wxFileName dirname = wxFileName(fullpath,wxEmptyString);
	
	int iNumDir = dirname.GetDirCount();
	myDirArray = dirname.GetDirs();
	m_DBName = myDirArray.Last();
	dirname.RemoveLastDir(); 
	m_DBPath = dirname.GetPath();
	
	if (m_DBPath.IsEmpty() || m_DBName.IsEmpty())
	{
		return FALSE;
	}
	return TRUE;
}

