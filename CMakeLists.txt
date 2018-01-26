# CMAKE BUILD FILE FOR TOOLBASVIEW 
# (c) Copyright 2011 Lucien Schreiber. All Rights Reserved. 
cmake_minimum_required(VERSION 2.6)
## POLICY FOR WINDOWS ONLY ???
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET (PROGNAME ToolBasView)
PROJECT (${PROGNAME})
MESSAGE("Project Name is : ${CMAKE_PROJECT_NAME}")

IF(APPLE)
  # add no optimization level to Debug version. Otherwise debugging didn't work correctly
  SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
  SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0") 
  MESSAGE(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
  MESSAGE(STATUS "CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
ENDIF(APPLE)

# SEARCH FILES --------------------------------
#search all source files
FILE (GLOB SRC_FILES src/*.cpp)
FILE (GLOB_RECURSE ART_FILES_C art/*.cpp)
SET(SRC_FILES ${SRC_FILES} ${ART_FILES_C})
SOURCE_GROUP (source FILES ${SRC_FILES})

# search all headers files
FILE (GLOB HEAD_FILES "src/*.h")
FILE (GLOB_RECURSE ART_FILES_H art/*.h)
SET(HEAD_FILES ${HEAD_FILES} ${ART_FILES_H})
SOURCE_GROUP (header FILES ${HEAD_FILES})

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/art/")

# INCLUDE LIBRARIES NEEDED ----------------------
# WXWIDGETS
SET(WXWINDOWS_USE_GL 0)
INCLUDE ("build/cmake/FindwxWidgets.cmake")
INCLUDE ("build/cmake/findMySQLEmbedded.cmake")
INCLUDE ("build/cmake/findGISLib.cmake")

# SPECIAL APPLE COMMAND FOR BUNDLE ---------------------
IF( APPLE )
  # Need to copy the icon file
  set_source_files_properties( "art/toolbasview.icns" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  set( SRC_FILES ${SRC_FILES} "art/toolbasview.icns")
ENDIF (APPLE)

# ADD ALSO HEADERS NOT REALY NEEDED JUST FOR VS
# COMPILING
IF (WIN32)
  SOURCE_GROUP (resource FILES src/ToolBasView.rc)
  ADD_EXECUTABLE (${PROGNAME} WIN32 ${SRC_FILES} ${HEAD_FILES} src/ToolBasView.rc)
  TARGET_LINK_LIBRARIES (${PROGNAME} ${WXWINDOWS_LIBS})
ELSE (WIN32)
  ADD_EXECUTABLE (${PROGNAME} MACOSX_BUNDLE ${SRC_FILES} ${HEAD_FILES} ) 
ENDIF (WIN32)

IF (APPLE)
  # Copy plist to ToolMap (should be after add executable!
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/custominfo.plist)
ENDIF(APPLE)

# copy libs to bundle if we are under mac...
# check is done internally.
INCLUDE ("build/cmake/installMacGISLIB.cmake")

#SOULD WE ADD THE LIBTIFF INTO BUNDLE
# ONLY FOR CERTAIN MAC WITH PPC 
# CHECK ARE DONE INTERNALLY YOU 
# CAN CALL THIS WITHOUT FEAR...
INCLUDE ("build/cmake/installMacLibTiff.cmake")

# SHOULD WE USE THE MT VERSION FOR DEFAULT 
# COMPATIBILITY WITH < WINXP
IF (WIN32)
  INCLUDE ("build/cmake/Use_visualstudioMT.cmake")
ENDIF (WIN32)

#SOULD WE ADD THE GDIPLUS.dll INTO project
# ONLY FOR Windows, but needed if using
# advanced graphics
# do nothing under other 
# OS. 
# CHECK ARE DONE INTERNALLY YOU 
# CAN CALL THIS WITHOUT FEAR...
INCLUDE ("build/cmake/Use_wingdiplus.cmake")

INCLUDE ("build/cmake/useMySQLEmbedded.cmake")
INCLUDE("build/cmake/GDALCopyLibs.cmake")

# installer
if (CREATE_INSTALLER)
  INCLUDE("build/cmake/create_installer.cmake")
endif (CREATE_INSTALLER)

# UNIT TEST PROGRAM
SET (USE_UNITTEST CACHE BOOL "Sould we Create the Unit Test (XP) for ${PROGNAME}")
IF (USE_UNITTEST)
  ADD_SUBDIRECTORY("test/build" ${PROJECT_BINARY_DIR})
ENDIF (USE_UNITTEST)
