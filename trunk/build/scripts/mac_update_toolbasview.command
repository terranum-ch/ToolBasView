#! /bin/sh

# Script for updating ToolBasview
# (c) Lucien Schreiber CREALP 2010
#PARAMETERS

# works only for Mac
# Do not modify for your paths but copy outside the 
# trunk and edit for your paths


# 1) Update the svn repositories
# 2) Run cmake to update the Xcode solution
# 3) Run (manually) the vroomGIS compilation
# 4) Launch the binary


TRUNKDIR=/Users/lucien/DATA/PROGRAMATION/toolbasview/trunk
BINDIR=/Users/lucien/DATA/PROGRAMATION/toolbasview/bin

# PARAMETERS
PARAMGISPATH=/Users/lucien/DATA/PROGRAMATION/_LIB/32/_LIBGIS
PARAMWXPATH=/Users/lucien/DATA/PROGRAMATION/_LIB/32/_LIBWX
PARAMMYSQLPATH=/Users/lucien/DATA/PROGRAMATION/_LIB/32/_LIBMYSQL


VARLINE="----------------------------------"


echo "----------------------------------------"
echo "         UPDATE TOOLBASVIEW " 
echo  "    (c) Lucien Schreiber CREALP"
echo "----------------------------------------"
echo "1) Updating SVN ..."

cd $TRUNKDIR
svn update
VARSVNNUMBER=`svnversion -n`
echo '1) Updating SVN .... DONE (\c'
echo  $VARSVNNUMBER ')'	
echo $VARLINE


echo "3) configuring ..."
cd $BINDIR
[ -d 32-dbg ] || mkdir 32-dbg
cd $BINDIR/32-dbg

cmake -GXcode $TRUNKDIR/build -DCMAKE_OSX_ARCHITECTURES:TEXT="i386" -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GIS_LIB_PATH:PATH=$PARAMGISPATH -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE="$PARAMWXPATH/bin/wx-config" -DMYSQL_MAIN_DIR:PATH=$PARAMMYSQLPATH -DMYSQL_IS_LOGGING:BOOL=1 -DSVN_DURING_BUILD:BOOL=1 -DCMAKE_BUILD_TYPE:TEXT="Debug"

echo $VARLINE
echo "4) Making DEBUG"
xcodebuild -configuration Debug
echo "4) Making DEBUG ... DONE"

echo -n "Build release version (y/n) ?"
read value

if [ "$value" == "n" ]  
then 
exit 0 
fi

echo "3) configuring ..."
cd $BINDIR
[ -d 32-rel ] || mkdir 32-rel
cd $BINDIR/32-rel

cmake -GXcode $TRUNKDIR/build -DCMAKE_OSX_ARCHITECTURES:TEXT="i386" -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GIS_LIB_PATH:PATH=$PARAMGISPATH -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE="$PARAMWXPATH/bin/wx-config" -DMYSQL_MAIN_DIR:PATH=$PARAMMYSQLPATH -DMYSQL_IS_LOGGING:BOOL=1 -DSVN_DURING_BUILD:BOOL=1 -DCMAKE_BUILD_TYPE:TEXT="Release"


echo $VARLINE
echo "4) Making RELEASE"
xcodebuild -configuration Release
echo "4) Making RELEASE ... DONE"

echo $VARLINE
echo "Starting Debug ToolBasView"
open $BINDIR/32-dbg/Debug/ToolBasView.app
