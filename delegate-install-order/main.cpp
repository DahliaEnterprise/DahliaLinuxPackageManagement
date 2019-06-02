#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include "dependency.cpp"

int main()
{
    //Initialize
    dependency headDependencies[100];
    int headDependenciesSize = 0;
    int nextAvailableGlobalIdentifier = 1;
    
    //Define locale as English UTF-8
    const std::locale locale = std::locale("en_US.utf8");
    
    //Configuration
    std::string directoryOfPackageInformation = std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/");
    std::string manifestLocation = std::string(); manifestLocation.append(directoryOfPackageInformation); manifestLocation.append("manifest.txt");
    std::string packageHeadDependencyListFilename = std::string("BuildEssential_amd64.txt");
    std::string completeLocationToPackageHead = std::string(); completeLocationToPackageHead.append(directoryOfPackageInformation); completeLocationToPackageHead.append(packageHeadDependencyListFilename);
    
/*
    // //                 \\ \\
    || ||   Begin Script   || ||
    \\ \\                 // //
*/

//TODO: load all files
//TODO: link files with objects
//TODO: traverse links to the deepest depth
//TODO: install debian packages

//Become aware of dependencies unlinked text list represented as (dependency class) Objects.
std::ifstream manifestTextFile; manifestTextFile.open(manifestLocation, std::ifstream::in);
if(manifestTextFile.is_open() == true)
{
    
    char line[100];
    memset(line, '\0', 100);
    manifestTextFile.getline(line, 100); 
    while(strlen(line) > 0)
    { 
        dependency prerequisite;
        prerequisite.initialize();
        prerequisite.setDependencyName((char*)std::string(line).c_str());
        prerequisite.setGlobalIdentifier(nextAvailableGlobalIdentifier);
        nextAvailableGlobalIdentifier += 1;
        headDependencies[headDependenciesSize] = prerequisite;
        headDependenciesSize += 1;

        //Reset for next iteration of while loop
        memset(line, '\0', 100);
        manifestTextFile.getline(line, 100);
    }
}



//Loop through each item in unlinked list, make each object aware of its prerequisite name and global identifiers.
for(int i = 0; i < headDependenciesSize; i++)
{
    //Open file that contains list of prerequisites for this dependency.
    std::string prerequisiteListTextFileLocation = std::string(); prerequisiteListTextFileLocation.append(directoryOfPackageInformation); prerequisiteListTextFileLocation.append(headDependencies[i].getDependencyName()); prerequisiteListTextFileLocation.append(".txt");
    std::cout << prerequisiteListTextFileLocation << "\n";
    std::ifstream prerequisiteListTextFile; prerequisiteListTextFile.open(prerequisiteListTextFileLocation, std::ifstream::in);
    if(prerequisiteListTextFile.is_open() == true)
    {
        std::cout << "prereq file found\n";
    }
}
   
//TODO: Determine the deepest depth

   
   
   
   
   
   
   
   
   
   
   
    //TODO: Loop through every "head" dependency
    //          for every "head" dependency get deepest prerequisite depth
    //              create a install order by queue breadcrumb arrays
    //              breadcrumb array proposal:  0 0 0 0 0 0 0 0 0 0    (head dependency level 0,... 0)
    //                                          0 0 0 0 0 0 0 0 0 1
    //                                          0 0 0 0 0 0 0 0 0 2
    //                                                          ...
    //                                          2 0 1 0 0 0 0 0 0 0    (head dependency level 2, 0, 1)
    
    
    return 0;
}
