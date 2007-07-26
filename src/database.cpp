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
	// closing database if open...
	if (DataBaseIsOpen())
	{
		DataBaseClose();		
	}
	
	// conversion from path
	DataBaseConvertFullPath(path);
	wxString datadir = _T("--datadir=") + m_DBPath;

	// convertion const char * to char *.... no other way ?
	const char * myPath = (const char *)datadir.mb_str(wxConvUTF8);
	char temps[datadir.Length()];
	strcpy(temps,myPath);
	
	static char *server_args[] = 
	{
		"this_program",       /* this string is not used */
		temps,
		"--language=./share/english",
		"--skip-innodb",
		"--port=3309",
		"--character-sets-dir=./share/charsets"
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
		
		if(mysql_real_connect(pMySQL,NULL,NULL,NULL,(const char *)m_DBName.mb_str(wxConvUTF8),3309,NULL,0))
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
	
	if(mysql_query(pMySQL,"SHOW TABLES;")==0)
	{
		results = mysql_store_result(pMySQL);
		
		while((record = mysql_fetch_row(results)))
		{
			
			myStingArray.Add(wxString(record[0],wxConvUTF8));
		}
		
		// clean
		mysql_free_result(results);
		
	}
	return myStingArray;
}


wxString DataBase::DatabaseGetVersion()
{
	wxString myVersionString;
	myVersionString = wxString(mysql_get_client_info(),wxConvUTF8);
	return myVersionString;
}



wxArrayString DataBase::DatabaseListFields(wxString sTable)
{
	MYSQL_RES *results;
	MYSQL_ROW record;
	wxArrayString myStingArray;
	wxString myQuery = _T("SHOW COLUMNS FROM ") + sTable;
	
	if(mysql_query(pMySQL,(const char *)myQuery.mb_str(wxConvUTF8))==0)
	{
		results = mysql_store_result(pMySQL);
		while((record = mysql_fetch_row(results)))
		{
			myStingArray.Add(wxString(record[0], wxConvUTF8));
		}
		
		
		
		// clean
		mysql_free_result(results);
		
	}
	return myStingArray;

}

bool DataBase::DataBaseGetAllTableContent(wxString sTable)
{
	m_resultNumber = 0;
	wxString myQuery = _T("SELECT * FROM ") + sTable;
	
	if (mysql_query(pMySQL, (const char *)myQuery.mb_str(wxConvUTF8))==0) 
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
				myRowResult.Add(wxString ( record[i], wxConvUTF8));
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
	int iRetour = mysql_query(pMySQL, (const char*)myQuery.mb_str(wxConvUTF8) );
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


wxString DataBase::DatabaseGetCharacterSet()
{
	 MY_CHARSET_INFO cs;
	 mysql_get_character_set_info(pMySQL,&cs);
	 
	 wxString sCharName(cs.csname, wxConvUTF8);
	 
	 return sCharName;

}


bool DataBase::DataBaseCreateNew(wxString DataBasePath, wxString DataBaseName)
{
	// closing database if open...
	if (DataBaseIsOpen())
	{
		DataBaseClose();		
	}

	
	wxString datadir = _T("--datadir=") + DataBasePath;

	// convertion const char * to char *.... no other way ?
	const char * myPath = (const char *)datadir.mb_str(wxConvUTF8);
	char temps[datadir.Length()];
	strcpy(temps,myPath);
	
	static char *server_args[] = 
	{
		"this_program",       /* this string is not used */
		temps,
		"--language=./share/english",
		"--skip-innodb",
		"--port=3309",
		"--character-sets-dir=./share/charsets"
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
		
		if(mysql_real_connect(pMySQL,NULL,NULL,NULL,NULL,3309,NULL,0))
		{
			wxString myDBName (DataBaseName);
			myDBName.Prepend(_T("CREATE DATABASE "));
			
			if(mysql_query(pMySQL,(const char *)myDBName.mb_str(wxConvUTF8)) ==0)
			{
				wxLogMessage(_("Creating database ... OK"));
				
				
				mysql_close(pMySQL);
				
				// connect to the database
				if(mysql_real_connect(pMySQL,NULL,NULL,NULL,
					(const char *)DataBaseName.mb_str(wxConvUTF8),3309,NULL,0))
				{		
					m_DBPath = DataBasePath;
					m_DBName = DataBaseName;
					IsDatabaseOpen = TRUE;
					return TRUE;
				}
			}
			return FALSE;
			
		}	
		
	}
	// if something goes wrong
	return FALSE;
}


wxArrayString DataBase::DataBaseCutRequest (wxString theRequest)
{
	wxArrayString myArrayRequest;
	myArrayRequest = wxStringTokenize (theRequest,_T(";"));
	return myArrayRequest;
}


