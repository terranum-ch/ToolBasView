# CMAKE BUILD FILE FOR TOOLBASVIEW 
# (c) Copyright 2022 Terranum
cmake_minimum_required(VERSION 3.0)

## POLICY FOR WINDOWS ONLY ???
#if (COMMAND cmake_policy)
#    cmake_policy(SET CMP0003 NEW)
#endif (COMMAND cmake_policy)

PROJECT("ToolBasView")

# Use C++11
if (UNIX)
    add_definitions(-std=c++11)
endif (UNIX)

# using git version
set(${PROJECT_NAME}_MAJOR_VERSION "1")
set(${PROJECT_NAME}_MINOR_VERSION "4")
include(build/cmake/version.cmake)

# defining cmake version for installer mainly
set(CMAKE_PROJECT_VERSION_MAJOR ${${PROJECT_NAME}_MAJOR_VERSION})
set(CMAKE_PROJECT_VERSION_MINOR ${${PROJECT_NAME}_MINOR_VERSION})
set(CMAKE_PROJECT_VERSION_PATCH ${GIT_NUMBER})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#Export for sourcetrail
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#source files
FILE(GLOB SRC_FILES src/*.cpp)
FILE(GLOB_RECURSE ART_FILES_C art/*.cpp)
SET(SRC_FILES ${SRC_FILES} ${ART_FILES_C})
SOURCE_GROUP(source FILES ${SRC_FILES})

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/art/")

# osx icon
set(MACOSX_BUNDLE_ICON_FILE art/toolbasview.icns)
set(ICON_PATH "${CMAKE_SOURCE_DIR}/art/toolbasview.icns")
set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

# Create the Toolbasview binary
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}
        MACOSX_BUNDLE WIN32
        ${SRC_FILES}
        ${ICON_PATH}
        src/resource.rc
        )
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${CONAN_LIBS})


IF (APPLE)
    # Copy plist to ToolMap (should be after add executable!
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/build/custominfo.plist)
ENDIF (APPLE)

# Install step for copying *dylib into application bundle on OSX and for changing their reference from
# absolute to relative
IF (APPLE)
    # change cmake_install_prefix from /usr/local to the binary directory
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
    set(APPS ${CMAKE_INSTALL_PREFIX}/bin/${CMAKE_PROJECT_NAME}.app)  # paths to executables
    set(DIRS ${CMAKE_INSTALL_PREFIX}/bin/)  # paths to executables
    INSTALL(CODE "
   include(BundleUtilities)
   fixup_bundle(\"${APPS}\"   \"\"   \"${DIRS}\")
   " COMPONENT Runtime)
ENDIF (APPLE)


# copy libs to bundle if we are under mac...
# check is done internally.
#INCLUDE("build/cmake/installMacGISLIB.cmake")

#SOULD WE ADD THE LIBTIFF INTO BUNDLE
# ONLY FOR CERTAIN MAC WITH PPC 
# CHECK ARE DONE INTERNALLY YOU 
# CAN CALL THIS WITHOUT FEAR...
#INCLUDE("build/cmake/installMacLibTiff.cmake")

# SHOULD WE USE THE MT VERSION FOR DEFAULT 
# COMPATIBILITY WITH < WINXP
#IF (WIN32)
#    INCLUDE("build/cmake/Use_visualstudioMT.cmake")
#ENDIF (WIN32)

#SOULD WE ADD THE GDIPLUS.dll INTO project
# ONLY FOR Windows, but needed if using
# advanced graphics
# do nothing under other 
# OS. 
# CHECK ARE DONE INTERNALLY YOU 
# CAN CALL THIS WITHOUT FEAR...
#INCLUDE("build/cmake/Use_wingdiplus.cmake")
#
#INCLUDE("build/cmake/useMySQLEmbedded.cmake")
#INCLUDE("build/cmake/GDALCopyLibs.cmake")

# installer
#if (CREATE_INSTALLER)
#    INCLUDE("build/cmake/create_installer.cmake")
#else (CREATE_INSTALLER)
#    install(
#            TARGETS ${CMAKE_PROJECT_NAME}
#            BUNDLE DESTINATION .
#            RUNTIME DESTINATION bin
#    )
#endif (CREATE_INSTALLER)

# UNIT TEST PROGRAM
#SET(USE_UNITTEST CACHE BOOL "Sould we Create the Unit Test (XP) for ${CMAKE_PROJECT_NAME}")
#IF (USE_UNITTEST)
#    ADD_SUBDIRECTORY("test/build" ${PROJECT_BINARY_DIR})
#ENDIF (USE_UNITTEST)
