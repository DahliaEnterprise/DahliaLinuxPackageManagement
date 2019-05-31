#!/bin/bash
debianPackageDirectoryLocation="/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/"
entryBuildOrder="BuildEssential_amd64.txt"

fileDirectoryEntryBuildOrder=$debianPackageDirectoryLocation$entryBuildOrder

#Entry Build Order Loop
readarray buildOrderItems < $fileDirectoryEntryBuildOrder                                         
filetype=".txt"
for buildOrderItem in "${buildOrderItems[@]}";do
	trimmedBuildOrderItem=$(echo $buildOrderItem | xargs)
	buildOrderItemPrerequisite="${debianPackageDirectoryLocation}${trimmedBuildOrderItem}${filetype}"
	#echo $buildOrderItemPrerequisite	
	line=$(head -n 1 $buildOrderItemPrerequisite)
	echo $line
done 

