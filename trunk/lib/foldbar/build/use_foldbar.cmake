# SCRIPT FOR BUILDING LSVersion
# INCLUDE THIS FILE FOR INCLUDING A DIALOG CONTAINING
# ALL VERSION INFORMATIONS 

SET(FOLDBAR_NAME "foldbar")

#OPTIONS - PARAMETERS 
SET(USE_FOLDBAR 1 CACHE BOOL "Use component ${LSVERSION_NAME}")
IF(USE_FOLDBAR)
  #FINDING OUR PATH
  FIND_PATH(FOLDBAR_PATH "lsfoldbar.h" 
    "/plugins/foldbar/src/"
    "../plugins/foldbar/src/"
    "../../plugins/foldbar/src/"
    "../../../plugins/foldbar/src/"
    "../../../../plugins/foldbar/src/"
    "/lib/foldbar/src/"
    "../lib/foldbar/src/"
    "../../lib/foldbar/src/"
    "../../../lib/foldbar/src/"
    "../../../../lib/foldbar/src/"
    "/foldbar/src/"
    "../foldbar/src/"
    "../../foldbar/src/"
    "../../../foldbar/src/"
    "../../../../foldbar/src/"
    NO_DEFAULT_PATH)
  #
  # CREATE LIBRARY 
  #
  #search all source files
  MESSAGE(${FOLDBAR_PATH})
  FILE (GLOB FOLDBAR_SRC_FILES "${FOLDBAR_PATH}/*.cpp")
  SOURCE_GROUP(source FILES ${FOLDBAR_SRC_FILES})

  #COUNTING NUMBER OF SOURCES FOUND
  LIST(LENGTH FOLDBAR_SRC_FILES FOLDBAR_LENGTH)
  IF(NOT FOLDBAR_LENGTH)
    MESSAGE(FATAL_ERROR "${FOLDBAR_LENGTH} source found for foldbar Plugin")
  ENDIF(NOT FOLDBAR_LENGTH)

  # search all headers files
  FILE (GLOB FOLDBAR_HEAD_FILES "${FOLDBAR_PATH}/*.h")
  SOURCE_GROUP(header FILES ${FOLDBAR_HEAD_FILES})
  INCLUDE_DIRECTORIES("${FOLDBAR_PATH}")
  ADD_LIBRARY("foldbar" STATIC ${FOLDBAR_SRC_FILES} ${FOLDBAR_HEAD_FILES})


ELSE(USE_FOLDBAR)
  MESSAGE( "Not using foldbar Component")
ENDIF(USE_FOLDBAR)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

