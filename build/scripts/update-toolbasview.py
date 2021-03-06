#!/usr/bin/env python
# encoding: utf-8
"""
update-toolbasview.py

Created by Lucien Schreiber on 2012-08-14.
Copyright (c) 2012 . All rights reserved.
"""

import os
try:
  from Tkinter import *
except :
  from tkinter import *
from subprocess import *
from ttk import *
import platform
import shutil

def GetCmakeDirName():
  pathname = os.path.dirname(sys.argv[0])        
  return os.path.join(os.path.abspath(pathname), "..")
  
def updateSVN():
  myPath = os.path.normpath(os.path.join(GetCmakeDirName(), ".."))
  print ("Updating subversion in: {}".format(myPath))
  try:
    p = Popen("svn update", shell=True, cwd = myPath)
    p.wait()
  except:
    print ("Error updating subversion in: {}".format(myPath))

  # print version number
  try:
    p = Popen("svnversion", shell=True, cwd=myPath, stdout=PIPE, stderr=PIPE)
    information = p.communicate()
    myVersion = str(information[0])
    #myVersionAlone = myVersion[myVersion.find("'")+1:-3] 
    print ("Updated version is: {}".format(myVersion))
  except:
    print("Error getting version for {}".format(GetCmakeDirName()))


def BuildMacPro():
  print ("Configuring Mac Pro (UNIL)")
  builddir = "/Users/lucien/Documents/PRJ/TOOLBASVIEW/bin"
  try:
    p = Popen("cmake -GXcode " + GetCmakeDirName() + "  -DCMAKE_OSX_ARCHITECTURES:TEXT=x86_64 -DCMAKE_OSX_DEPLOYMENT_TARGET:TEXT=10.6 -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE=/Users/lucien/Documents/PROGRAMMATION/64/_LIBWXSVN/bin/wx-config -DwxWIDGETS_USING_SVN:BOOL=1 -DMYSQL_MAIN_DIR:PATH=/Users/lucien/Documents/PROGRAMMATION/64/_LIBMYSQL -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GIS_LIB_PATH:PATH=/Users/lucien/Documents/PROGRAMMATION/64/_LIBGIS", shell=True, cwd=builddir)
    p.wait()
  except:
    print("Error creating makefile")


def BuildMacBookDeploy():
  print ("Configuring MacBook (deployement)")
  builddir = "/Users/lucien/DATA/PROGRAMATION/toolbasview/bin"

  try:
    p = Popen("cmake -GXcode " + GetCmakeDirName() + "  -DCMAKE_OSX_ARCHITECTURES:TEXT=x86_64 -DCMAKE_OSX_DEPLOYMENT_TARGET:TEXT=10.6 -DCMAKE_OSX_SYSROOT:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/SDKs/MacOSX10.6.sdk -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBWXSVN/bin/wx-config -DwxWIDGETS_USING_SVN:BOOL=1 -DwxWIDGETS_PATH_SVN:STRING=/Users/lucien/DATA/PROGRAMATION/_LIB/64/wxWidgets-svn -DMYSQL_MAIN_DIR:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBMYSQL -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GIS_LIB_PATH:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBGIS -DMYSQL_IS_LOGGING:BOOL=1 -DSEARCH_CURL_LIB_PATH:STRING=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBCURL", shell=True, cwd=builddir)
  except:
    print("Error creating makefile")



def BuildMacBook():
  print ("Configuring MacBook (developpement)")
  builddir = "/Users/lucien/DATA/PROGRAMATION/toolbasview/bin"

  try:
    p = Popen("cmake -GXcode " + GetCmakeDirName() + "  -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBWXSVN/bin/wx-config -DwxWIDGETS_USING_SVN:BOOL=1 -DwxWIDGETS_PATH_SVN:STRING=/Users/lucien/DATA/PROGRAMATION/_LIB/64/wxWidgets-svn -DMYSQL_MAIN_DIR:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBMYSQL -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GIS_LIB_PATH:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBGIS -DMYSQL_IS_LOGGING:BOOL=1 -DSEARCH_CURL_LIB_PATH:STRING=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBCURL", shell=True, cwd=builddir)
  except:
    print("Error creating makefile")



def BuildWindows7():
  print ("Configuring Windows")
  builddir = "D:\\PROGRAMMATION\\ToolBasView\\bin"
  try:
    p = Popen("cmake -G\"Visual Studio 10\" " + GetCmakeDirName() + " -DwxWIDGETS_USING_SVN:BOOL=1  -DwxWIDGETS_PATH_SVN:PATH=D:\\LIB\\wxWIDGETS-SVN -DSEARCH_GDAL:BOOL=1 -DwxWIDGETS_USING_SVN:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GIS_LIB_PATH:PATH=D:\\LIB\\LIB_GDAL  -DSEARCH_GEOS_LIB_PATH:PATH=D:\\LIB\\geos-3.4.2 -DUSE_MT_LIBRARY:BOOL=1 -DMYSQL_IS_LOGGING:BOOL=1 -DMYSQL_MAIN_DIR:PATH=D:\\LIB\\LIB_MYSQL", shell=True, cwd=builddir)
    p.wait()
  except:
    print("Error creating makefile")


def BuildLinuxHome():
  print("Configuring Linux")
  builddir = "/home/lucien/programmation/ToolBasView/bin"
  try:
    p = Popen("cmake -G\"CodeBlocks - Unix Makefiles\" " + GetCmakeDirName() + " -DwxWIDGETS_USING_SVN:BOOL=1  -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE=/home/lucien/programmation/LIB/_LIBWX/bin/wx-config  -DwxWIDGETS_PATH_SVN:PATH=/home/lucien/programmation/LIB/wxWidgets-SVN  -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1", shell=True, cwd=builddir)
    #p = Popen("cmake -G\"CodeBlocks - Unix Makefiles\" " + GetCmakeDirName() + " -DwxWIDGETS_USING_SVN:BOOL=1  -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE=/home/lucien/programmation/LIB/_LIBWX/bin/wx-config  -DwxWIDGETS_PATH_SVN:PATH=/home/lucien/programmation/LIB/wxWidgets-SVN -DMYSQL_IGNORE_NORMAL:BOOL=1 -DMYSQL_MAIN_DIR:PATH=/home/lucien/programmation/LIB/_LIBMYSQL -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GDAL_LIB_PATH:PATH=/home/lucien/programmation/LIB/_LIBGIS -DSEARCH_GEOS_LIB_PATH:PATH=/home/lucien/programmation/LIB/_LIBGIS", shell=True, cwd=builddir)
    p.wait()
  except:
    print("Error creating makefile")



def RunBuildMac():
  builddir =  myPath = os.path.normpath(os.path.join(GetCmakeDirName(), "..", "..",  "bin"))
  print (builddir)
  
  try:
    p = Popen("xcodebuild -configuration Debug", shell=True, cwd=builddir)
    p.wait()
  except:
    print ("Error building in", builddir)
    return

  try:
    p = Popen("xcodebuild -configuration Debug", shell=True, cwd=builddir)
    p.wait()
  except:
    print ("Error building in", builddir)
    return

def RunBuildWindows(solutionname):
  builddir =  myPath = os.path.normpath(os.path.join(GetCmakeDirName(), "..", "..",  "bin"))
  print (builddir)
  mycommand = "msbuild {}.sln /p:Configuration={}" 
  
  try:
    p = Popen(mycommand.format(solutionname, "Debug"), shell=True, cwd=builddir)
    p.wait()
  except:
    print ("Error building in", builddir)
    return

  try:
    p = Popen(mycommand.format(solutionname, "RelWithDebInfo"), shell=True, cwd=builddir)
    p.wait()
  except:
    print ("Error building in", builddir)
    return 

def createInstaller():
  builddir =  myPath = os.path.normpath(os.path.join(GetCmakeDirName(), "..", "..",  "bin"))
  myCpackCommand = "cpack "
  myInstallerExtension = ".dmg"
  if (platform.system() == 'Windows'):
    myCpackCommand = myCpackCommand + " -C RelWithDebInfo"
    myInstallerExtension = ".exe"
  
  try:
    p = Popen (myCpackCommand, shell=True, cwd=builddir)
    p.wait()
  except:
    print ("Error creating installer")

  # search and move installer to install folder
  myInstallerName = ""
  for f in os.listdir(builddir):
    if(myInstallerExtension in f):
      myInstallerName = f
  
  if (myInstallerName == ""):
    print ("No installer found!")
    pass

  shutil.move (os.path.join(builddir, myInstallerName), os.path.join(builddir, "..", "install", myInstallerName))
  print ("Installer {0} moved to install folder".format(myInstallerName)) 

    
  



if __name__ == '__main__':
  root = Tk()
  myContainer1 = Frame(root)
  myContainer1.pack()

  label = Label(myContainer1, text="TOOLBASVIEW")
  label.pack()

  button3 = Button(myContainer1, text=("Update subversion"), command=updateSVN)
  button3.pack()

  orient1 = Separator(myContainer1, orient='horizontal')
  orient1.pack(fill = BOTH, expand = True, pady=5, padx=5)

  button2 = Button(myContainer1, text="Configure MacBook (dev)", command=BuildMacBook)
  button2.pack()

  button6 = Button(myContainer1, text="Configure MacBook (deploy)", command=BuildMacBookDeploy)
  button6.pack()
  
  button1 = Button(myContainer1, text="Configure Mac Pro (UNIL)", command=BuildMacPro)
  button1.pack()

  button3 = Button(myContainer1, text= "Configure Windows 7", command=BuildWindows7)
  button3.pack()

  button8 = Button(myContainer1, text="Configure Linux (Home)", command=BuildLinuxHome)
  button8.pack()
 
  orient = Separator(myContainer1, orient='horizontal')
  orient.pack(fill = BOTH, expand = True, pady=5, padx=5)
  
  button4 = Button(myContainer1, text= "Build Mac (bin)", command=RunBuildMac)
  button4.pack()

  solutionname = label.cget("text")
  button5 = Button(myContainer1, text= "Build Windows (bin)", command=lambda:RunBuildWindows(solutionname))
  button5.pack()

  orient3 = Separator(myContainer1, orient='horizontal')
  orient3.pack(fill = BOTH, expand = True, pady=5, padx=5)
  
  button7 = Button (myContainer1, text="Create installer", command=createInstaller)
  button7.pack()

  root.mainloop()


