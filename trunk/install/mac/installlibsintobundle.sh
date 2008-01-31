#!/bin/bash
# script for exporting library to the bundle folder and making it right

# CONFIGURE THIS....
MY_PROG_NAME="ToolBasView"
echo "Program name = " $MY_PROG_NAME

echo "Path of the program to modify <-:" 
read MY_BUNDLE_LOC
echo "Program to be modified is : " $MY_BUNDLE_LOC

#making directories inside the application if dir exists, break;
if [ -d $MY_BUNDLE_LOC/Contents/Lib ]
then
    echo "cant continue, Lib directory exist"
    exit 1
fi

echo "Creating the lib directory"
mkdir $MY_BUNDLE_LOC"Contents/Lib"

echo "Copying library..."

MY_LIB_PATH=$MY_BUNDLE_LOC"Contents/Lib/"
echo $MY_LIB_PATH
# CONFIGURE THIS....
cp "/Users/Lucien/DATA/PROGRAMATION/LIB_MAC/LIB_SQL/lib/mysql/libmysqld.a" $MY_LIB_PATH


# to continue,... not needed for this project.