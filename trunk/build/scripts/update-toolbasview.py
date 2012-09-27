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

def GetCmakeListPath():
    myFileName = os.path.split(__file__)
    myCmakePath = os.path.dirname(myFileName[0])
    return myCmakePath


def BuildMacPro():
    print ("Configuring Mac Pro (UNIL)")
    builddir = "/Users/lucien/Documents/PRJ/TOOLBASVIEW/bin"
    try:
        p = Popen("cmake -GXcode " + GetCmakeListPath() + "  -DCMAKE_OSX_ARCHITECTURES:TEXT=x86_64 -DCMAKE_OSX_DEPLOYMENT_TARGET:TEXT=10.6 -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE=/Users/lucien/Documents/PROGRAMMATION/64/_LIBWXSVN/bin/wx-config -DMYSQL_MAIN_DIR:PATH=/Users/lucien/Documents/PROGRAMMATION/64/_LIBMYSQL -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GDAL_LIB_PATH:PATH=/Users/lucien/Documents/PROGRAMMATION/64/_LIBGIS -DSEARCH_GEOS_LIB_PATH:PATH=/Users/lucien/Documents/PROGRAMMATION/64/_LIBGIS", shell=True, cwd=builddir)
        p.wait()
    except:
        print("Error creating makefile")


def BuildMacBook():
    print ("Configuring MacBook")
    builddir = "/Users/lucien/DATA/PROGRAMATION/toolbasview/bin"
    try:
        p = Popen("cmake -GXcode " + GetCmakeListPath() + "  -DCMAKE_OSX_ARCHITECTURES:TEXT=x86_64 -DCMAKE_OSX_DEPLOYMENT_TARGET:TEXT=10.6 -DCMAKE_WXWINDOWS_WXCONFIG_EXECUTABLE:FILE=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBWXSVN/bin/wx-config -DMYSQL_MAIN_DIR:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBMYSQL -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GDAL_LIB_PATH:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBGIS -DSEARCH_GEOS_LIB_PATH:PATH=/Users/lucien/DATA/PROGRAMATION/_LIB/64/_LIBGIS", shell=True, cwd=builddir)
    except:
        print("Error creating makefile")



def BuildWindows7():
    print ("Configuring Windows")
    builddir = "D:\\PROGRAMMATION\\ToolBasView\\bin"
    try:
        p = Popen("cmake -G\"Visual Studio 10\" " + GetCmakeListPath() + " -DwxWIDGETS_USING_SVN:BOOL=1  -DwxWIDGETS_PATH_SVN:PATH=D:\\LIB\\wxWIDGETS-SVN -DSEARCH_GDAL:BOOL=1 -DSEARCH_GEOS:BOOL=1 -DSEARCH_GDAL_LIB_PATH:PATH=D:\\LIB\\LIB_GDAL  -DSEARCH_GEOS_LIB_PATH:PATH=D:\\LIB\\geos-3.3.4 -DSQLITE_PATH:PATH=D:\\LIB\\LIB_SQLITE -DUSE_MT_LIBRARY:BOOL=1 -DMYSQL_MAIN_DIR:PATH=D:\\LIB\\LIB_MYSQL", shell=True, cwd=builddir)
        p.wait()
    except:
        print("Error creating makefile")

if __name__ == '__main__':

    root = Tk()
    myContainer1 = Frame(root)
    myContainer1.pack()

    label = Label(myContainer1)

    button2 = Button(myContainer1, text="Configure MacBook", command=BuildMacBook)
    button2.pack()

    button1 = Button(myContainer1, text="Configure Mac Pro (UNIL)", command=BuildMacPro)
    button1.pack()

    button3 = Button(myContainer1, text= "Configure Windows 7", command=BuildWindows7)
    button3.pack()

    root.mainloop()

