# CMAKE BUILD FILE FOR TOOLBASVIEW (LINUX AND WINDOWS)
# (c) Copyright 2011 Lucien Schreiber. All Rights Reserved. 

cmake_minimum_required(VERSION 2.6)
## POLICY FOR WINDOWS ONLY ???
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET (PROGNAME ToolBasView)
PROJECT (${PROGNAME})
MESSAGE("Project Name is : ${CMAKE_PROJECT_NAME}")

# SEARCH FILES --------------------------------
#search all source files
FILE (GLOB SRC_FILES ../src/*.cpp)
SOURCE_GROUP (source FILES ${SRC_FILES})

# search all headers files
FILE (GLOB HEAD_FILES "../src/*.h")
SOURCE_GROUP (header FILES ${HEAD_FILES})

#MESSAGE ("Build type is : " ${CMAKE_BUILD_TYPE}) 

# INCLUDE LIBRARIES NEEDED ----------------------
# WXWIDGETS
SET(WXWINDOWS_USE_GL 0)
INCLUDE ("cmake/FindwxWidgets.cmake")

#MYSQL EMBEDDED
INCLUDE ("cmake/findMySQLEmbedded.cmake")

#GEOS - GDAL libs
INCLUDE ("cmake/findGISLib.cmake")

# LSVERSION
INCLUDE("../plugins/lsversion/build/use_lsversion.cmake")

# FOLDBAR
INCLUDE("../lib//foldbar/build/use_foldbar.cmake")



# SPECIAL APPLE COMMAND FOR BUNDLE ---------------------
IF( APPLE )
	SET (APP_ICON "toolbasview.icns")
	#bundle variables for compilation under Mac OS
	SET(MACOSX_BUNDLE_INFO_STRING "ToolMap database Viewer")
	SET(MACOSX_BUNDLE_ICON_FILE ${APP_ICON})
	#MACOSX_BUNDLE_GUI_IDENTIFIER
	#MACOSX_BUNDLE_LONG_VERSION_STRING
	SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROGNAME}")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "Version 1.1")
	SET(MACOSX_BUNDLE_BUNDLE_VERSION "1.1")
	SET(MACOSX_BUNDLE_COPYRIGHT "Lucien Schreiber (c) CREALP 2011")
	
	# Need to copy the icon file
	set_source_files_properties( "../art/toolbasview.icns" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
	set( SRC_FILES ${SRC_FILES} "../art/toolbasview.icns")
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


# LINK LSVERSION PLUGIN
IF(USE_VERSION)
	TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${LSVERSION_NAME})
ENDIF(USE_VERSION)

# LINK FOLDBAR PLUGIN
IF(USE_FOLDBAR)
	TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${FOLDBAR_NAME})
ENDIF(USE_FOLDBAR)


#SVN NUMBERING
#INCLUDE ("cmake/use_svnnumber.cmake")

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

#SOULD WE ADD THE GDIPLUS.dll INTO project
# ONLY FOR Windows, but needed if using
# advanced graphics
# do nothing under other 
# OS. 
# CHECK ARE DONE INTERNALLY YOU 
# CAN CALL THIS WITHOUT FEAR...
INCLUDE ("cmake/Use_wingdiplus.cmake")

#Copy errmsg.sys to correct path
INCLUDE ("cmake/useMySQLEmbedded.cmake")

# UNIT TEST PROGRAM
SET (USE_UNITTEST CACHE BOOL "Sould we Create the Unit Test (XP) for ${PROGNAME}")
IF (USE_UNITTEST)
	ADD_SUBDIRECTORY("../test/build" ${PROJECT_BINARY_DIR})
ENDIF (USE_UNITTEST)
