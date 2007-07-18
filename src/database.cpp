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
	static char *server_args[] = {
		"this_program",       /* this string is not used */
		"--datadir=/Users/Lucien/DATA/PRJ/TOOLMAP/TestBDD/BDD/data/",
		"--language=./share/english",
		"--skip-innodb",
		"--port=3309",
		"--character-sets-dir=./share/charsets", 
		//"--default-charcater-set=latin1"
		//"--language=french",
		//
		//"--defaults-file=/Users/Lucien/DATA/PRJ/TOOLMAP/TestBDD/BDD/my.ini"
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
		
		if(mysql_real_connect(pMySQL,NULL,NULL,NULL,_T("essai"),3309,NULL,0))
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

