# - Find SQLite version 3
# Find the  SQLite Library
# Created by Lucien Schreiber 
#
#  SQLITE_INCLUDE_DIR - where to find sqlite3.h, etc.
#  SQLITE_LIBRARIES   - List of libraries when using SQLite.
#  SQLITE_FOUND       - True if SQLite found.

#IF (SQLITE_INCLUDE_DIR)
  # Already in cache, be silent
 # SET(SQLITE_FIND_QUIETLY TRUE)
#ENDIF (SQLITE_INCLUDE_DIR)

# EMPTY THE include path IF EXISTS
SET (SQLITE_INCLUDE_DIR "sqlite3.h-NOTFOUND")

FIND_PATH(SQLITE_INCLUDE_DIR sqlite3.h
  /usr/local/include/sqlite
  /usr/include/sqlite
)


SET(SQLITE_NAMES sqlite3)

#allow user to specify a path
#if no path is specified we search 
# in generic path like /usr/...
SET (SQLITE_MAIN_DIR CACHE PATH "Path to the main SQLite directory, empty for searching for default")


# no search path is specified, we are
#searching in a normal path
IF (SQLITE_MAIN_DIR STREQUAL "")
	
		#MESSAGE ("SQLITE Include dir defined")
		
		# empty variables
		SET (SQLITE_LIBRARY "${SQLITE_NAMES}-NOTFOUND" )
		SET (SQLITE_INCLUDE_DIR "sqlite3.h-NOTFOUND")
		
		
		FIND_PATH(SQLITE_INCLUDE_DIR sqlite3.h
  				/usr/local/include/sqlite
				/usr/include/sqlite )
				
		FIND_LIBRARY(SQLITE_LIBRARY
	  		NAMES ${SQLITE_NAMES}
	  		PATHS /usr/lib /usr/local/lib)
	
  		
  
	
#		IF (SQLITE_INCLUDE_DIR_AUTO AND SQLITE_LIBRARY_AUTO)
#	  		SET(SQLITE_FOUND TRUE)
#	  		SET( SQLITE_LIBRARIES ${SQLITE_LIBRARY} )
#		ELSE (SQLITE_INCLUDE_DIR_AUTO AND SQLITE_LIBRARY_AUTO)
#	  		SET(SQLITE_FOUND FALSE)
#	  		SET( SQLITE_LIBRARIES )
#		ENDIF (SQLITE_INCLUDE_DIR_AUTO AND SQLITE_LIBRARY_AUTO)
#	
#		IF (SQLITE_FOUND)
#	  		IF (NOT SQLITE_FIND_QUIETLY)
#	    		MESSAGE(STATUS "Found SQLite: ${SQLITE_LIBRARY}")
#	  		ENDIF (NOT SQLITE_FIND_QUIETLY)
#		ELSE (SQLITE_FOUND)
#	  		IF (SQLITE_FIND_REQUIRED)
#	    		MESSAGE(STATUS "Looked for SQLite libraries named ${SQLITE_NAMES}.")
#	    		MESSAGE(FATAL_ERROR "Could NOT find SQLite library")
#	  		ENDIF (SQLITE_FIND_REQUIRED)
#		ENDIF (SQLITE_FOUND)



# if we are searching specific directory
ELSE (SQLITE_MAIN_DIR STREQUAL "")
	
	
	IF (WIN32)
		
		# include directory based on main path
		SET(SQLITE_INCLUDE_DIR "${SQLITE_MAIN_DIR}/include/")
		
		     
		     SET(SQLITE_CONFIG_LIBS ${SQLITE_CONFIG_LIBS}
		           debug "${SQLITE_MAIN_DIR}/Embedded/DLL/debug/libsqlited.lib"   optimized "${SQLITE_MAIN_DIR}/Embedded/DLL/release/libsqlited.lib")
		     
		     # path to libs
		    # IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		    #    SET(SQLITE_CONFIG_LIBS "${SQLITE_MAIN_DIR}/Embedded/DLL/debug/libsqlited.lib" )
		    #  ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		
		    #  IF(CMAKE_BUILD_TYPE STREQUAL "Release")
		    #    SET(SQLITE_CONFIG_LIBS "${SQLITE_MAIN_DIR}/Embedded/DLL/release/libsqlited.lib" )
      		    # ENDIF(CMAKE_BUILD_TYPE STREQUAL "Release")
		
		

	ELSE (WIN32)
		
		# empty variables
		SET (SQLITE_LIBRARY "${SQLITE_NAMES}-NOTFOUND" )
		SET (SQLITE_INCLUDE_DIR "sqlite3.h-NOTFOUND")

		
		FIND_PATH(SQLITE_INCLUDE_DIR sqlite3.h
  				${SQLITE_MAIN_DIR}/include
  				${SQLITE_MAIN_DIR}
				NO_DEFAULT_PATH)        
        
        FIND_LIBRARY(SQLITE_LIBRARY
  			NAMES ${SQLITE_NAMES}
  			PATHS ${SQLITE_MAIN_DIR}/lib ${SQLITE_MAIN_DIR}
  			NO_DEFAULT_PATH)
  			
  
	ENDIF(WIN32)

ENDIF (SQLITE_MAIN_DIR STREQUAL "")





MARK_AS_ADVANCED(
  SQLITE_LIBRARY
  SQLITE_INCLUDE_DIR
  )
  
  
  ## IF PARAMETERS ARE DEFINED, USE THEM
   IF(SQLITE_INCLUDE_DIR)
    INCLUDE_DIRECTORIES(${SQLITE_INCLUDE_DIR})
  ENDIF(SQLITE_INCLUDE_DIR)
 
 
  IF(SQLITE_LIBRARY)
    LINK_LIBRARIES(${SQLITE_LIBRARY})
  ENDIF(SQLITE_LIBRARY)
  
 # IF (SQLITE_CONFIG_CXFLAGS)
 #   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SQLITE_CONFIG_CXFLAGS}")
 # ENDIF(SQLITE_CONFIG_CXFLAGS)
  


  
  