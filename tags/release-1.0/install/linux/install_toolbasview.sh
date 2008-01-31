#!/bin/bash
# script for installing ToolBasView under linux

# CONFIGURE THIS....
MY_PROG_NAME="ToolBasView"
echo $MY_PROG_NAME "installation script"

echo "This will install ToolBasView into your computer"
echo "Continue ? [Y], [N]" 
read action

if [ $action = "y" -o $action = "Y" ]
then
	echo "Installing..."
else
	echo "Quitting"
	exit
fi


#getting the sudo pwd
