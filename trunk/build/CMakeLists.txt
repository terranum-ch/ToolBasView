# CMAKE BUILD FILE FOR TOOLBASVIEW (LINUX AND WINDOWS)
# USE WXIDGETS AND MYSQL
# (c) LUCIEN SCHREIBER CREALP 2007


PROJECT (ToolBasView)

#search all source files
FILE (GLOB SRC_FILES ../src/*.cpp)
SOURCE_GROUP (source FILES ${SRC_FILES})

# search all headers files
FILE (GLOB HEAD_FILES "../include/*.h")
SOURCE_GROUP (header FILES ${HEAD_FILES})


SET(TRUNK_PATH ${PROJECT_SOURCE_DIR}/.. CACHE PATH "Path to the trunk" )


# WXWIDGETS
# DEFINE ALL INCLUDES AND SO ON
INCLUDE ("cmake/Use_wxWindows.cmake")


#SQLite EMBEDDED
 INCLUDE ("cmake/findSQLite.cmake")


# Getting the subversion number and
# generating a file called svn_version.h
IF (WIN32)
	EXECUTE_PROCESS(
		COMMAND version_svn_win.bat
		WORKING_DIRECTORY ${TRUNK_PATH}/build/
	)
ELSE (WIN32)
	EXECUTE_PROCESS(
		COMMAND sh version_svn_unix.sh
		WORKING_DIRECTORY ${TRUNK_PATH}/build/
	)
ENDIF(WIN32)



#bundle variables for compilation under Mac OS
SET(MACOSX_BUNDLE_INFO_STRING "Look into MySQL database")
SET(MACOSX_BUNDLE_ICON_FILE ${TRUNK_PATH}/art/fish.icns)
#MACOSX_BUNDLE_GUI_IDENTIFIER
#MACOSX_BUNDLE_LONG_VERSION_STRING
SET(MACOSX_BUNDLE_BUNDLE_NAME "ToolBasView")
SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "Version 1.1")
SET(MACOSX_BUNDLE_BUNDLE_VERSION "1.1")
SET(MACOSX_BUNDLE_COPYRIGHT "Lucien Schreiber (c) CREALP 2008")


 
# ADD ALSO HEADERS NOT REALY NEEDED JUST FOR VS
# COMPILING

IF (WIN32)

	SOURCE_GROUP (resource FILES ../src/ToolBasView.rc)
 	ADD_EXECUTABLE (ToolBasView WIN32 ${SRC_FILES} ${HEAD_FILES} ../src/ToolBasView.rc)
 	TARGET_LINK_LIBRARIES (ToolBasView ${WXWINDOWS_LIBS})

ELSE (WIN32)
 	ADD_EXECUTABLE (ToolBasView MACOSX_BUNDLE ${SRC_FILES} ${HEAD_FILES} ) 
 
ENDIF (WIN32)
