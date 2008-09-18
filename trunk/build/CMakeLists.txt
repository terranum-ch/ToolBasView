# CMAKE BUILD FILE FOR TOOLBASVIEW (LINUX AND WINDOWS)
# USE WXIDGETS AND MYSQL
# (c) LUCIEN SCHREIBER CREALP 2007
cmake_minimum_required(VERSION 2.4)

SET (PROGNAME ToolBasView)
PROJECT (${PROGNAME})

#search all source files
FILE (GLOB SRC_FILES ../src/*.cpp)
SOURCE_GROUP (source FILES ${SRC_FILES})

# search all headers files
FILE (GLOB HEAD_FILES "../include/*.h")
SOURCE_GROUP (header FILES ${HEAD_FILES})


#SET(TRUNK_PATH ${PROJECT_SOURCE_DIR}/.. CACHE PATH "Path to the trunk" )

MESSAGE ("Build type is : " ${CMAKE_BUILD_TYPE})

# WXWIDGETS
# DEFINE ALL INCLUDES AND SO ON
 SET(WXWINDOWS_USE_GL 0)
INCLUDE ("cmake/Use_wxWindows.cmake")


#SQLite EMBEDDED
# INCLUDE ("cmake/findSQLite.cmake")

#MYSQL EMBEDDED
INCLUDE ("cmake/findMySQLEmbedded.cmake")


#GEOS - GDAL libs
 INCLUDE ("cmake/findGISLib.cmake")

# Getting the subversion number and
# generating a file called svn_version.h
IF (WIN32)
	EXECUTE_PROCESS(
		COMMAND version_svn_win.bat
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../build/
	)
ELSE (WIN32)
	EXECUTE_PROCESS(
		COMMAND sh version_svn_unix.sh
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../build/
	)
ENDIF(WIN32)


IF( APPLE )
	SET (APP_ICON "fish.icns")
	#bundle variables for compilation under Mac OS
	SET(MACOSX_BUNDLE_INFO_STRING "Look into MySQL database")
	SET(MACOSX_BUNDLE_ICON_FILE ${APP_ICON})
	#MACOSX_BUNDLE_GUI_IDENTIFIER
	#MACOSX_BUNDLE_LONG_VERSION_STRING
	SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROGNAME}")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "Version 1.1")
	SET(MACOSX_BUNDLE_BUNDLE_VERSION "1.1")
	SET(MACOSX_BUNDLE_COPYRIGHT "Lucien Schreiber (c) CREALP 2008")
	
	# Need to copy the icon file
	EXEC_PROGRAM( "mkdir -p       ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ToolBasView.app/Contents/Resources")
	EXEC_PROGRAM( "cp ${PROJECT_SOURCE_DIR}/../art/${APP_ICON} ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ToolBasView.app/Contents/Resources")
	

ENDIF (APPLE)



 
# ADD ALSO HEADERS NOT REALY NEEDED JUST FOR VS
# COMPILING

IF (WIN32)

	SOURCE_GROUP (resource FILES ../src/ToolBasView.rc)
 	ADD_EXECUTABLE (${PROGNAME} WIN32 ${SRC_FILES} ${HEAD_FILES} ../src/ToolBasView.rc)
 	TARGET_LINK_LIBRARIES (${PROGNAME} ${WXWINDOWS_LIBS})

ELSE (WIN32)
 	ADD_EXECUTABLE (${PROGNAME} MACOSX_BUNDLE ${SRC_FILES} ${HEAD_FILES} ) 
 
ENDIF (WIN32)


# copy libs to bundle if we are under mac...
# check is done internally.
INCLUDE ("cmake/installMacGISLIB.cmake")

#SOULD WE ADD THE LIBTIFF INTO BUNDLE
# ONLY FOR CERTAIN MAC WITH PPC 
# CHECK ARE DONE INTERNALLY YOU 
# CAN CALL THIS WITHOUT FEAR...
INCLUDE ("cmake/installMacLibTiff.cmake")

# SHOULD WE USE THE MT VERSION FOR DEFAULT 
# COMPATIBILITY WITH < WINXP
IF (WIN32)
	INCLUDE ("cmake/Use_visualstudioMT.cmake")
ENDIF (WIN32)