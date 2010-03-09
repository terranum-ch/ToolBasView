@ECHO OFF 
REM script for updating ToolBasView app under windows
REM works only for windows
REM 1) Update the svn repositories
REM 2) Run cmake to create/update the Visual studio solution
REM 3) Run (manually) the vroomGIS compilation
REM 4) Launch the app


@SET TRUNKDIR=D:\LS\PROGRAMATION\ToolBasView\trunk
@SET BINDIR=D:\LS\PROGRAMATION\ToolBasView\bin
@SET VSDIR=C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE


@SET PARAMGIS=D:\LS\PROGRAMATION\LIB\LIB_GDAL
@SET PARAMGEOS=D:\LS\PROGRAMATION\LIB\geos-3.2.0
@SET PARAMMYSQL=D:\LS\PROGRAMATION\LIB\mysql-5.1.42-VS2008
@SET PARAMMYSQL_LOGGING=1


ECHO ----------------------------------------
ECHO         UPDATE TOOLBASVIEW APP
ECHO     (c) Lucien Schreiber CREALP
ECHO ----------------------------------------
ECHO 1) Updating repositories ...

D:
cd %trunkdir%
svn update

REM GETTING SUBVERSION NUMBER
FOR /F "usebackq" %%s IN (`svnversion .`) DO @SET REV=%%s
REM ECHO  #define SVN_VERSION _T(^"%REV%^")

ECHO 1) Updating repositories ... DONE (version is : %REV%)




ECHO 2) Making Visual studio solution...
cd %bindir%
cmake %trunkdir%\build\ -G "Visual Studio 9 2008" -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GIS_LIB_PATH:PATH=%PARAMGIS% -DSEARCH_GEOS_LIB_PATH:PATH=%PARAMGEOS% -DUSE_MT_LIBRARY:BOOL=1 -DMYSQL_MAIN_DIR:PATH=%PARAMMYSQL% -DMYSQL_IS_LOGGING:BOOL=%PARAMMYSQL_LOGGING% -DUSE_GDIPLUS_LIBRARY:BOOL=1 -DSVN_DURING_BUILD:BOOL=1
ECHO 2) Making Visual studio solution... DONE



ECHO -----------------------------------------------
ECHO 3) BUILDING TOOLBASEVIEW APP (MAY TAKE SOME TIMES)-----
ECHO -----------------------------------------------

cd %BINDIR%
"%vsdir%\VCExpress.exe" ToolBasView.sln /Out solution.log /Build Debug
echo %ERRORLEVEL%
IF ERRORLEVEL 1 goto QuitErrorBuildScript

ECHO COPYING LIBRARY DEBUG...
xcopy %PARAMMYSQL%\Embedded\DLL\debug\libmysqld.dll %BINDIR%\Debug /Y
xcopy %PARAMGIS%\bin\*.dll %BINDIR%\Debug /Y
xcopy %PARAMGEOS%\source\geos_c.dll %BINDIR%\Debug /Y



"%vsdir%\VCExpress.exe" ToolBasView.sln /Out solution.log /Build Release
echo %ERRORLEVEL%
IF ERRORLEVEL 1 goto QuitErrorBuildScript

ECHO 4) INSTALLING LIBRARY RELEASE
xcopy %PARAMMYSQL%\Embedded\DLL\release\libmysqld.dll %BINDIR%\Release /Y
xcopy %PARAMGIS%\bin\*.dll %BINDIR%\Release /Y
xcopy %PARAMGEOS%\source\geos_c.dll %BINDIR%\Release /Y

ECHO 3) BUILDING ToolBasView APP DONE





cd %bindir%
start %bindir%\Debug\ToolBasView.exe
REM "C:\Program Files\Notepad++\notepad++.exe" %bindir%\Testing\Temporary\LastTest.log
REM notepad.exe %bindir%\Testing\Temporary\LastTest.log
goto :WaitForEnter



:WaitForEnter
  set wait=
  set /p wait=Please press ENTER to continue 
  IF NOT DEFINED wait goto :eof 
  echo Please press only the ENTER key and nothing else
  goto :WaitForEnter

REM :UserPressedENTER

:QuitErrorBuildScript
	"C:\Program Files\Notepad++\notepad++.exe" %bindir%\solution.log
	ECHO Error detected see solution.log
	goto :WaitForEnter