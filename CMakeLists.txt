# CMAKE BUILD FILE FOR TOOLBASVIEW 
# (c) Copyright 2022 Terranum
cmake_minimum_required(VERSION 3.0)

PROJECT("ToolBasView")

# Use C++11
if (UNIX)
    add_definitions(-std=c++11)
endif (UNIX)

# using git version
set(${PROJECT_NAME}_MAJOR_VERSION "1")
set(${PROJECT_NAME}_MINOR_VERSION "5")
include(build/cmake/version.cmake)

# defining cmake version for installer mainly
set(CMAKE_PROJECT_VERSION_MAJOR ${${PROJECT_NAME}_MAJOR_VERSION})
set(CMAKE_PROJECT_VERSION_MINOR ${${PROJECT_NAME}_MINOR_VERSION})
set(CMAKE_PROJECT_VERSION_PATCH ${GIT_NUMBER})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#Export compile commands (for sourcetrail)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#source files
SET(LIB_FILES
        "src/addspatialdata_dlg.cpp"
        "src/changecolumn_dlg.cpp"
        "src/database.cpp"
        "src/databaseoperation.cpp"
        "src/databaseresult.cpp"
        "src/deletetabledata_dlg.cpp"
        "src/dialogs.cpp"
        "src/dlg_operation.cpp"
        "src/Excel.cpp"
        "src/exportcsv_dlg.cpp"
        "src/gisdataprovider.cpp"
        "src/gridoperation.cpp"
        "src/querylisttree.cpp"
        "src/resultsframe.cpp"
        "src/searchspatialpoint_dlg.cpp"
        "src/tableexport.cpp"
        "src/frameabout.cpp"
        )

SET(SRC_FILES
        "src/toolbasapp.cpp"
        "src/toolbaseframe.cpp"
        "src/toolbarbitmaps.cpp"
        "art/toolbasview_bmp.cpp"
        )

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/art/")
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

# osx icon
set(MACOSX_BUNDLE_ICON_FILE art/toolbasview.icns)
set(ICON_PATH "${CMAKE_SOURCE_DIR}/art/toolbasview.icns")
set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

# Create a library with all sources files mainly for unit testing
ADD_LIBRARY("${CMAKE_PROJECT_NAME}_lib" STATIC ${LIB_FILES})
target_link_libraries("${CMAKE_PROJECT_NAME}_lib" ${CONAN_LIBS})

# Create the Toolbasview binary
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}
        MACOSX_BUNDLE WIN32
        ${SRC_FILES}
        ${ICON_PATH}
        src/resource.rc
        )
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} "${CMAKE_PROJECT_NAME}_lib" ${CONAN_LIBS})

# Copy plist to bundle (should be placed after add executable!
IF (APPLE)
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
SET(USE_UNITTEST CACHE BOOL "Sould we Create the Unit Test for ${CMAKE_PROJECT_NAME}")
IF (USE_UNITTEST)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(test)
ENDIF (USE_UNITTEST)

# installer
include(build/cmake/create_installer.cmake)