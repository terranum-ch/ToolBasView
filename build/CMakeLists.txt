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


# WXWIDGETS
# DEFINE ALL INCLUDES AND SO ON
 INCLUDE ("cmake/Use_wxWindows.cmake")


#ASK FOR MYSQL LIBRARY HEADERS
SET(MYSQL_LIB_HEADERS "D:/LS/PROGRAMATION/LIB/mysql-4.1.22-win32/include" CACHE STRING
	"MYSQL include directory")
INCLUDE_DIRECTORIES (${MYSQL_LIB_HEADERS})

#ASK FOR THE MYSQL LIBRARY
SET (MYSQL_LIB "D:/LS/PROGRAMATION/LIB/mysql-4.1.22-win32/Embedded/static/release/mysqlserver.lib" CACHE STRING
	"MYSQL Library, under unix path to the mysql-config tool")


 
# ADD ALSO HEADERS NOT REALY NEEDED JUST FOR VS
# COMPILING

IF (WIN32)

	SOURCE_GROUP (resource FILES ../src/ToolBasView.rc)
 	ADD_EXECUTABLE (ToolBasView WIN32 ${SRC_FILES} ${HEAD_FILES} ../src/ToolBasView.rc)
 	TARGET_LINK_LIBRARIES (ToolBasView ${WXWINDOWS_LIBS} ${MYSQL_LIB})

ELSE (WIN32)
 
 	ADD_EXECUTABLE (ToolBasView ${SRC_FILES} ${HEAD_FILES} )
       TARGET_LINK_LIBRARIES (ToolBasView `${MYSQL_LIB}mysql_config --libmysqld-libs`) 
        
        #TARGET_LINK_LIBRARIES (ToolBasView ${WXAUI_THE_LIB} `${GDAL_LIB}/gdal-config --libs` `${GEOS_LIB}/geos-config --libs`)

ENDIF (WIN32)




# ASK FOR GDAL LIB HEADERS
#SET(GDAL_LIB_HEADERS "D:/PROGRAMATION/LIB/gdal-cvs-2006.08.21" CACHE STRING 
#	"GDAL-OGR library headers directory,root directory")
#SET (GDAL_LIB_HEADERS 
#	${GDAL_LIB_HEADERS}/port 
#	${GDAL_LIB_HEADERS}/ogr 
#	${GDAL_LIB_HEADERS}/ogr/ogrsf_frmts 
#	${GDAL_LIB_HEADERS}/gcore)
#INCLUDE_DIRECTORIES(${GDAL_LIB_HEADERS})

#ASK FOR GDAL LIB
#SET(GDAL_LIB "D:/PROGRAMATION/LIB/gdal-cvs-2006.08.21/build/mswd/gdal_i.lib" CACHE STRING 
#"GDAL-OGR library under unix system path to the gdal-config --libs program")


# ASK FOR GEOS LIB HEADERS
#SET(GEOS_LIB_HEADERS "D:/PROGRAMATION/LIB/geos_3_svn03/capi" CACHE STRING 
#	"GEOS C library headers directory,root directory")
#INCLUDE_DIRECTORIES(${GEOS_LIB_HEADERS})

#ASK FOR GEOS LIB
#SET(GEOS_LIB "D:/PROGRAMATION/LIB/geos_3_svn03/build/msvMT/geos_c.lib" CACHE STRING 
#"GEOS-OGR library under unix system path to the GEOS-config --libs program")