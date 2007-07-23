/*!
    @file database.h
    @brief   Definition of class DataBase
	
	Class used to connect to manage the embedded MySQL server. This class need
	mysql.h and the embedded MySql Library.
*/


#ifndef __database_H__
#define __database_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "../include/database.cpp"
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "mysql.h"
#include <wx/arrstr.h> // array string
#include <wx/strconv.h> // unicode conversion

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
	virtual ~DataBase();
	/*!
    @function  
    @brief   Function used to init the MySql embedded server and to open a database
    
	This function must be called before other Database functions.
    @param      path wxString containing the directory where live the database
    @result     return true if library and connexion to the database ok
	*/
    bool DataBaseOpen(wxString path);
	
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
	bool DataBaseIsOpen() {return IsDatabaseOpen;} 

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
	wxString DatabaseGetVersion();
	
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
	
	/*!
    @function 
    @brief Used to execute a query on the database
	
	This function is mainly created to execute a query without results
    @param     myQuery the string containing the query
    @result    return 0 if the query works and the MYSQL error code otherwise.
	*/
	int DataBaseQuery(wxString myQuery);
	
	/*!
    @brief  return the path of the database
	
	This function must be called only after DataBaseOpen().
	@result return the path of the database
	*/	
	wxString DataBaseGetPath() {return m_DBPath;} 

	/*!
    @brief  return the Name of the database
	
	This function must be called only after DataBaseOpen().
	@result return the name of the database
	*/	
	wxString DataBaseGetName() {return m_DBName;}
	
	/*!
    @brief  return the character set used for the transaction
	
	This function must be called only after DataBaseOpen().
	@result return the name of the character set used.
	*/	
	wxString DatabaseGetCharacterSet();
	

	
   
    
private:
	MYSQL * pMySQL;
	
	// for storing restults 
	MYSQL_RES * pResults;
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
	
	

};


#endif
