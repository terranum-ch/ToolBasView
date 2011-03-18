# - Find mysqlclient
# Find the native MySQL includes and embedded library
# Modified by Lucien Schreiber from the http://www.cmake.org/Wiki
#
#  MYSQL_INCLUDE_DIR - where to find mysql.h, etc.
#  MYSQL_LIBRARIES   - List of libraries when using MySQL.
#  MYSQL_FOUND       - True if MySQL found.

IF (MYSQL_INCLUDE_DIR)
  # Already in cache, be silent
  SET(MYSQL_FIND_QUIETLY TRUE)
ENDIF (MYSQL_INCLUDE_DIR)

FIND_PATH(MYSQL_INCLUDE_DIR mysql.h
  /usr/local/include/mysql
  /usr/include/mysql
)

SET (MYSQL_IGNORE_NORMAL CACHE BOOL "Ignore Standard MySQL library ?")

# if mysql is installed in a normal directory
IF (MYSQL_INCLUDE_DIR AND NOT MYSQL_IGNORE_NORMAL)

	MESSAGE ("MYSQL Include dir defined")
	#SET(MYSQL_NAMES mysqld)
	#FIND_LIBRARY(MYSQL_LIBRARY
  	#NAMES ${MYSQL_NAMES}
  	#PATHS /usr/lib /usr/local/lib /usr/lib/mysql
	#)

	#IF (MYSQL_INCLUDE_DIR AND MYSQL_LIBRARY)
  	#	SET(MYSQL_FOUND TRUE)
  	#	SET( MYSQL_LIBRARIES ${MYSQL_LIBRARY} )
	#	MESSAGE("MySQL found and linked ${MYSQL_LIBRARY}")
	#	LINK_LIBRARIES(${MYSQL_LIBRARY})
	#ELSE (MYSQL_INCLUDE_DIR AND MYSQL_LIBRARY)
  	#	SET(MYSQL_FOUND FALSE)
  	#	SET( MYSQL_LIBRARIES )
	#ENDIF (MYSQL_INCLUDE_DIR AND MYSQL_LIBRARY)

	#IF (MYSQL_FOUND)
  	#	IF (NOT MYSQL_FIND_QUIETLY)
    	#	MESSAGE(STATUS "Found MySQL: ${MYSQL_LIBRARY}")
  	#	ENDIF (NOT MYSQL_FIND_QUIETLY)
	#ELSE (MYSQL_FOUND)
  	#	IF (MYSQL_FIND_REQUIRED)
    	#	MESSAGE(STATUS "Looked for MySQL libraries named ${MYSQL_NAMES}.")
    	#	MESSAGE(FATAL_ERROR "Could NOT find MySQL library")
  	#	ENDIF (MYSQL_FIND_REQUIRED)
	#ENDIF (MYSQL_FOUND)

	EXEC_PROGRAM("mysql_config"
        ARGS "--libmysqld-libs"
        OUTPUT_VARIABLE MYSQL_CONFIG_LIBS)
        MESSAGE("DBG: ${MYSQL_CONFIG_LIBS}")
        
        EXEC_PROGRAM("mysql_config"
        ARGS "--cflags"
        OUTPUT_VARIABLE MYSQL_CONFIG_CXFLAGS)
        MESSAGE("DBG: ${MYSQL_CONFIG_CXFLAGS}")

# if mysql is not installed in a normal
#directory, specify the main directory
ELSE (MYSQL_INCLUDE_DIR AND NOT MYSQL_IGNORE_NORMAL)
	SET (MYSQL_MAIN_DIR CACHE PATH "Path to the main MySQL directory")
	
	IF (WIN32)
		
		# include directory based on main path
		SET(MYSQL_INCLUDE_DIR "${MYSQL_MAIN_DIR}/include/")
		
		     
		     SET(MYSQL_CONFIG_LIBS ${MYSQL_CONFIG_LIBS}
		           debug "${MYSQL_MAIN_DIR}/Embedded/DLL/debug/libmysqld.lib"   optimized "${MYSQL_MAIN_DIR}/Embedded/DLL/release/libmysqld.lib")
		     
		     # path to libs
		    # IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		    #    SET(MYSQL_CONFIG_LIBS "${MYSQL_MAIN_DIR}/Embedded/DLL/debug/libmysqld.lib" )
		    #  ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		
		    #  IF(CMAKE_BUILD_TYPE STREQUAL "Release")
		    #    SET(MYSQL_CONFIG_LIBS "${MYSQL_MAIN_DIR}/Embedded/DLL/release/libmysqld.lib" )
      		    # ENDIF(CMAKE_BUILD_TYPE STREQUAL "Release")
		
		

	ELSE (WIN32)
		SET(MYSQL_INCLUDE_DIR "${MYSQL_MAIN_DIR}/include/")
		#MESSAGE ("MYSLQ_INCLUDE_DIR = ${MYSQL_INCLUDE_DIR}")
		
		SET(MYSQL_CONFIG_EXECUTABLE "${MYSQL_MAIN_DIR}/bin/mysql_config")
		
		SET(MYSQL_CONFIG_ARGS_LIBS "--libmysqld-libs")
		SET(MYSQL_CONFIG_ARGS_CXFLAGS "--cflags")
		
		EXEC_PROGRAM(${MYSQL_CONFIG_EXECUTABLE}
        ARGS ${MYSQL_CONFIG_ARGS_LIBS}
        OUTPUT_VARIABLE MYSQL_CONFIG_LIBS)
        MESSAGE("DBG: ${MYSQL_CONFIG_LIBS}")
        
        EXEC_PROGRAM(${MYSQL_CONFIG_EXECUTABLE}
        ARGS ${MYSQL_CONFIG_ARGS_CXFLAGS}
        OUTPUT_VARIABLE MYSQL_CONFIG_CXFLAGS)
        MESSAGE("DBG: ${MYSQL_CONFIG_CXFLAGS}")
		

	ENDIF(WIN32)

ENDIF (MYSQL_INCLUDE_DIR AND NOT MYSQL_IGNORE_NORMAL)



## DEFINE LOGGING OR NOT
SET (MYSQL_IS_LOGGING CACHE BOOL "Should MySQL log all commands to a text file in the document folder ?, not compatible with unit testing")

FIND_PATH(DATABASE_PROJ_SOURCE_DIR database-config.h.in
  ${PROJECT_SOURCE_DIR}/../src/database/
  ${PROJECT_SOURCE_DIR}/../../src/database/
  ${PROJECT_SOURCE_DIR}/../include
  ${PROJECT_SOURCE_DIR}
)

IF (DATABASE_PROJ_SOURCE_DIR)
	CONFIGURE_FILE("${DATABASE_PROJ_SOURCE_DIR}/database-config.h.in" 
		"${PROJECT_BINARY_DIR}/database-config.h")
		


ELSE(DATABASE_PROJ_SOURCE_DIR)
	MESSAGE(FATAL_ERROR "database-config.h.in not found, logging will not be defined")
	MESSAGE( ${PROJECT_SOURCE_DIR})
ENDIF(DATABASE_PROJ_SOURCE_DIR)



MARK_AS_ADVANCED(
  MYSQL_LIBRARY
  MYSQL_INCLUDE_DIR
  )
  
  
  ## IF PARAMETERS ARE DEFINED, USE THEM
   IF(MYSQL_INCLUDE_DIR)
    INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR})
	INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})
  ENDIF(MYSQL_INCLUDE_DIR)
 
  ###IF(WXWINDOWS_LINK_DIRECTORIES)
  ####  LINK_DIRECTORIES(${WXWINDOWS_LINK_DIRECTORIES})
  ####ENDIF(WXWINDOWS_LINK_DIRECTORIES)
  
  IF(MYSQL_CONFIG_LIBS)
    LINK_LIBRARIES(${MYSQL_CONFIG_LIBS})
  ENDIF(MYSQL_CONFIG_LIBS)
  
  IF (MYSQL_CONFIG_CXFLAGS)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYSQL_CONFIG_CXFLAGS}")
  ENDIF(MYSQL_CONFIG_CXFLAGS)
  


  
  
