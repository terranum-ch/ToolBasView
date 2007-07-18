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
	
   
    
private:
	MYSQL * pMySQL;
	bool IsDatabaseOpen;

};


#endif
