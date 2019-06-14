#!/bin/bash
workingDir=`pwd`
downloadSourceDirectoryLocation="/Base/Debian/9.9.0/BuildEssential/amd64/DownloadSource/*"
wholeDownloadSourceDirLocation=$workingDir$downloadSourceDirectoryLocation


for file in $wholeDownloadSourceDirLocation
do
	#.downloadsource text file location
	#echo $file

	#read from .downloadsource textfile
	line=$(head -n 1 $file)
	echo $line
	
	#download file
	wget $line
done
