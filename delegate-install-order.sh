#!/bin/bash
debianPackageDirectoryLocation="/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/"
entryBuildOrder="BuildEssential_amd64.txt"

fileDirectoryEntryBuildOrder=$debianPackageDirectoryLocation$entryBuildOrder

#Entry Build Order Loop
readarray buildOrderItem < $fileDirectoryEntryBuildOrder                                         

for row in "${buildOrderItem[@]}";do                                                      
  row_array=(${row})                                                            
  first=${row_array[0]}                                                         
  echo ${first}                                                                 
done 

