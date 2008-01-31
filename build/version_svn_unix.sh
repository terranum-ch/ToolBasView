#!/bin/sh
#script for getting the last svn version number 
#works only for unix like (mac, linux)
	echo -n '#define SVN_VERSION _T("' > ../include/svn_version.h
    svnversion -n                  >> ../include/svn_version.h
    echo '")'   >> ../include/svn_version.h
    echo '' >> ../include/svn_version.h