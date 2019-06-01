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

#Define initial breadcrumb depth
continueDefiningBreadcrumbDepth=true
breadcrumbDepthIndex=0
currentPrerequisiteLevelFirstLine=""
while $continueDefiningBreadcrumbDepth;do
	#Entry point get special treatment
	if [[ breadcrumbDepthIndex -eq 0 ]]; then
		currentPrerequisiteLevelFirstLine=$(head -n 1 $fileDirectoryEntryBuildOrder)
	fi

	#Non-Entry point
	if [[ breadcrumbDepthIndex -gt 0 ]]; then
		fileLocation=$debianPackageDirectoryLocation$currentPrerequisiteLevelFirstLine".txt"
		#echo $fileLocation	
		currentPrerequisiteLevelFirstLine=$(head -n 1 $fileLocation)
	fi
	
	echo $currentPrerequisiteLevelFirstLine

	stringLength=${#currentPrerequisiteLevelFirstLine}
	if [[ $stringLength -eq 0 ]]; then
		#End while loop if currentPrerequisiteLevelFirstLine is empty/blank
		continueDefiningBreadcrumbDepth=false
	else
		breadcrumbDepth[$breadcrumDepthIndex]=0
		#Increment breadcrumb depth index
		((breadcrumbDepthIndex = breadcrumbDepthIndex+1))
	fi
done


#Tumble the breadcrumbs!



echo "FINISHED"


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

