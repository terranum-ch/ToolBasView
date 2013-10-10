
install(
  TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  RUNTIME DESTINATION bin 
  )
install (
  FILES ../licence/cddl.txt DESTINATION .
  )

# TODO: TEMP CODE FOR COPYING LIBRARIES TO BIN FOLDER. SHOULD BE 
# PLACED TO SUBFILES
IF(WIN32)
#  # copy CURL 
#  install(FILES "${CURL_INCLUDE_DIR}/../lib/DLL-Release/libcurl.dll" DESTINATION bin CONFIGURATIONS Release;RelWithDebInfo)
#  install(FILES "${CURL_INCLUDE_DIR}/../lib/DLL-Debug/libcurld.dll" DESTINATION bin CONFIGURATIONS Debug)

  # copy All libs GDAL, GEOS, etc.
  install(FILES ${GDAL_DLL_NAME} DESTINATION bin)
  install(FILES ${GEOS_DLL_NAME} DESTINATION bin)
  install(FILES ${GEOS_C_DLL_NAME} DESTINATION bin)
  install(FILES ${SQLITE_DLL_NAME} DESTINATION bin)
  install(FILES ${MYSQL_DLL_NAME} DESTINATION bin)
ENDIF(WIN32)

SET (SOFT_NUMBER ${lsVERSION_SOFT_VERSION})

SET(CPACK_PACKAGE_VENDOR "crealp")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "${SOFT_NUMBER}")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ToolBasView can create and edit MySQL embedded database")

# APPLE ONLY CODE 
IF (APPLE)
  SET(CPACK_PACKAGE_VERSION "1")
  SET(CPACK_GENERATOR "DragNDrop")
  SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_r${CPACK_PACKAGE_VERSION_PATCH}")
  SET(CPACK_DMG_VOLUME_NAME "${CMAKE_PROJECT_NAME}")
  SET(CPACK_DMG_FORMAT "UDBZ")
ENDIF (APPLE)

# WINDOWS CODE ONLY (NSIS)
IF (WIN32)
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/../../licence/cddl.txt")
  SET (CPACK_GENERATOR "NSIS")
  SET (CPACK_NSIS_COMPRESSOR "lzma")
  SET(CPACK_PACKAGE_FILE_NAME "toolbasview-setup_r${CPACK_PACKAGE_VERSION_PATCH}")
  SET (CPACK_PACKAGE_INSTALL_DIRECTORY ${CMAKE_PROJECT_NAME})
  SET (CPACK_NSIS_CONTACT "Lucien Schreiber lucien.schreiber@crealp.vs.ch")
  SET (CPACK_NSIS_HELP_LINK "www.crealp.ch")
  SET (CPACK_NSIS_MUI_FINISHPAGE_RUN ${CMAKE_PROJECT_NAME})
  SET (CPACK_NSIS_URL_INFO_ABOUT "www.crealp.ch")
  SET (CPACK_NSIS_MENU_LINKS 
    "bin/${CMAKE_PROJECT_NAME}" "${CMAKE_PROJECT_NAME}" 
    "http://www.crealp.ch" "www.crealp.ch")
ENDIF(WIN32)

INCLUDE (CPACK)
