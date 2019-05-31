#!/bin/bash

#Configuration
maxExpectedPrerequisiteDepth=100
debianPackageDirectoryLocation="/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/"
entryBuildOrder="BuildEssential_amd64.txt"
fileDirectoryEntryBuildOrder=$debianPackageDirectoryLocation$entryBuildOrder

#Initalize Array(s)
for ((i = 0 ; i < $maxExpectedPrerequisiteDepth; i++)); do
	breadcrumbDepth[$i]=-1
done
breadcrumbDepth[0]=0
echo ${breadcrumbDepth[0]}

#Define initial breadcrumb depth
















###################################################################### OLD CODE TO BE CODED INTO NEW #################
#Entry Build Order Loop
#readarray buildOrderItems < $fileDirectoryEntryBuildOrder                                         
#filetype=".txt"
#for buildOrderItem in "${buildOrderItems[@]}";do
#	trimmedBuildOrderItem=$(echo $buildOrderItem | xargs)
#	buildOrderItemPrerequisite="${debianPackageDirectoryLocation}${trimmedBuildOrderItem}${filetype}"
#	echo $buildOrderItemPrerequisite
#
#	#Determine Level One Prerequisite
#	readarray levelOnePrerequisites < $buildOrderItemPrerequisite
#	for levelOnePrerequisite in "${levelOnePrerequisites[@]}";do
#		echo " "$levelOnePrerequisite
#		
#		#Determine Level Two Prerequisite
#		trimmedLevelOnePrerequisites=$(echo $levelOnePrerequisite | xargs)
#		buildOrderItemPrerequisiteLevelTwo="${debianPackageDirectoryLocation}${trimmedLevelOnePrerequisites}${filetype}"
#		readarray levelTwoPrerequisites < $buildOrderItemPrerequisiteLevelTwo
#		for levelTwoPrerequisite in "${levelTwoPrerequisites[@]}";do
#			echo "  "$levelTwoPrerequisite
#		done
#
#	done
#
#	
#	#levelOnePrerequisite=$(head -n 1 $buildOrderItemPrerequisite)
#	#echo $levelOnePrerequisite
#done 

