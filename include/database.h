/***************************************************************************
								database.h
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
    @file database.h
    @brief   Definition of class DataBase
	
	Class used to connect and manage the embedded MySQL server. This class needs
	mysql.h and the embedded MySql Library.
	@author Lucien Schreiber (c) CREALP 2007
*/


#ifndef __database_H__
#define __database_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "database.cpp"
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

//#include "mysql.h"
#include "sqlite3.h"
#include <wx/filename.h>
#include <wx/arrstr.h> // array string
#include <wx/strconv.h> // unicode conversion
#include <wx/tokenzr.h> // tokenizer of string
#include <wx/dir.h> // directory operation (size)

const wxString DATABASE_TYPE_STRING = _T("SQLite");
const wxString DATABASE_EXTENSION_STRING = _T("tmdb");

/*!
    @enumeration 
    @brief enumeration of allowed values for
	inisialisation.
	*/
enum Lang_Flag
{
	LANG_UTF8,
	LANG_LATIN1
};

//----------------------------------------------------------------------------
// DataBase
//----------------------------------------------------------------------------
/*!
    @class DataBase
    @brief    Used for connecting to an embedded MySQL Database
	
	This class used the embedded library of MySQL to open and connect to databases.
*/
class DataBase 
{
public:
    // constructors and destructors
    /*!
    @method     
    @brief   Constructor, do nothing
	*/
	DataBase();
    /*!
    @method    
	
	@brief Destructor, do nothing
	*/
	~DataBase();
	/*!
    @function  
    @brief   Function used to init the MySql embedded server and to open a database
    
	This function must be called before other Database functions.
    @param      path wxString containing the directory where live the database
    @result     return true if library and connexion to the database ok
	*/
    bool DataBaseOpen(wxString path,enum Lang_Flag flag);
	
	/*!
    @brief   Function called to close the database and free the library
    
	This function must be called before quitting the program
	@result return TRUE if the database was close correctely
	*/
	bool DataBaseClose ();
	
	/*!
    @brief  return TRUE if a database is open
	@result return TRUE if the database is open
	*/	
	bool DataBaseIsOpen();

	/*!
    @function 
    @brief   return an array of string containing all the database tables
    @result  an array of string (wxArrayString) containing all the tables names
	*/
	wxArrayString DataBaseListTables();
	
	/*!
    @function 
    @brief   Return a wxString containing the version of the embedded server
	
	This function is the only one who may be called before DataBaseOpen().
    @result  a wxString containing the version number
	*/
	static wxString DatabaseGetVersion();
	
	/*!
    @function 
    @brief Return an array containing all the selected table fields
    @param      sTable a String containing the table name
    @result     an array of string containing the fields name.
	*/
	wxArrayString DatabaseListFields(wxString sTable);
	
	/*!
    @function 
    @brief Get all data stored in a table.
	
	This function just process the request, to get the result row
	by row, call the DataBaseGetNextResult() function.
	
    @param      sTable a String containing the table name
    @result     TRUE if the request is valid.
	*/	
	bool DataBaseGetAllTableContent(wxString sTable);
	
	/*!
    @function 
    @brief Return the result of the last request.
	
    @result     An array of strings containing the values of one row.
	*/		
	wxArrayString DataBaseGetNextResult();
	
	bool DataBaseTableExist(const wxString & tableName);
	
	
	int DataBaseGetResultAsInt();
	
	bool DataBaseIsTableEmpty(const wxString & tableName);
	
	/*!
    @function 
    @brief Used to execute multiple query on the database
	
	This function is mainly created to execute multiple query without results.
	User have to split the multiple queries into unique query and loop this function
	for each queries. Splitting queries could be made with the DataBaseCutRequest()
	member function.
	
	@warning  This function process the query and then destroy the query results,
	so no results could be see using DataBaseGetNextResult().
    @param     myQuery the string containing the query
    @result    return 0 if the query works and the MYSQL error code otherwise.
	@see DataBaseCutRequest(), DataBaseQuery()
	 
	*/
	bool DataBaseQueryNoResult(wxString myQuery);
	/*!
	@function 
	@brief Used to execute one query on the database and then get the result
	
	This function works in a similar way as the DataBaseQueryNoResult() but is able
	to send back the result of a query.
	
	@param myQuery the string containing the query
	@result true if the query was successfuly made otherwise false.
	@warning User have to check the return value, and if false then one souldn't 
	call the DataBaseGetNextResult()
	@see DataBaseQueryNoResult()
	 */
	bool DataBaseQuery(const wxString & myQuery);
	
	
	bool DataBaseHasResult ();
	
	
	/*! Execute multiple query 
	 @bug NOT WORKING, CRASH WITH VERSION 5.1.23-rc (on windows and Mac)
	 */
	int DataBaseQueryMultiple (const wxString & myQuery);
	

	int DataBaseQueryReal (wxString myQuery);

	/*!
    @brief  return the path of the database
	
	This function must be called only after DataBaseOpen().
	@result return the path of the database
	*/	
	wxString DataBaseGetPath();

	/*!
    @brief  return the Name of the database
	
	This function must be called only after DataBaseOpen().
	@result return the name of the database
	*/	
	wxString DataBaseGetName();
	
	/*!
    @brief  return the character set used for the transaction
	
	This function must be called only after DataBaseOpen().
	@result return the name of the character set used.
	*/	
	wxString DatabaseGetCharacterSet();
	
	/*!
    @brief  create a new database
	
	@param DataBasePath a wxString containing the Path for the new Database
	@param DataBaseName a wxString containing the new database name.
	@param Flag a Lang_Flag used for selecting the character set, 
	allowed values are (default)LANG_UTF8, LANG_LATIN1, 
	@result return TRUE if the new database was created succesfully.
	*/	
	bool DataBaseCreateNew(wxString DataBasePath, wxString DataBaseName,enum Lang_Flag Flag=LANG_UTF8);
	
	
	/*!
    @brief  cut a big request into unique request.
	
	A big request implying multiple operations could not be proceed in one operation
	one must cut this request into multiple small operations.
	
	@param theRequest a wxString containing the full request.
	@result a wxArrayString containing a unique request for each array.
	*/	
	wxArrayString DataBaseCutRequest (wxString theRequest);
	
	/*!
    @function 
    @brief   Compute the database file size
	@param  iPrecision an integer giving the requested precision for the result 
	(default is 2 decimals after the dot) 
	@result  Return an human readable string containing the database size plus
	the unit  (MB)
	*/
	wxString DataBaseGetSize (int iPrecision=2);

	
   
    
private:
	//MYSQL * pMySQL;
	
	// handler of a sqlite db
	sqlite3  * m_pDB;
	
	// handler for results
	char ** m_Result;
	int m_nRow;
	int m_nCols;
	
	// for storing restults 
	//MYSQL_RES * pResults;
	int m_resultNumber;
	
	// storing database path and name.
	wxString m_DBPath;
	wxString m_DBName;
	
	
	bool IsDatabaseOpen;
	
	/*!
    @brief  convert the path into path and database name

	@result true if all is OK.
	*/	
	bool DataBaseConvertFullPath(wxString fullpath);
	
	/*!
    @function 
    @brief Function used in windows to convert all the '\' path separator
	into a '/' separator.
	
	If the path allready contain '/' separator, this function does nothing
    @param      originalPath a wxSting containing the path to check/change
    @result     the modified path in a wxString. This modified path may be used for
	loading the MYSQL server.
	*/
	wxString DataBaseConvertMYSQLPath(wxString originalPath);

	/*!
    @function 
    @brief Function used to set the character set used by the embedded server
	
	This function is call by DataBaseOpen(), do not call it directly.
	*/
	bool DataBaseSetCharacterSet (enum Lang_Flag myFlag);





};


#endif
