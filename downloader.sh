#!/bin/bash

downloadSourceDirectoryLocation="/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/DownloadSource/*"

for file in $downloadSourceDirectoryLocation
do
	#.downloadsource text file location
	#echo $file

	#read from .downloadsource textfile
	line=$(head -n 1 $file)
	echo $line
	
	#download file
	wget $line
done