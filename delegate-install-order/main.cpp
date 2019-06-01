#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "dependency.cpp"

int main()
{
    //Initialize
    dependency headDependencies[100];
    unsigned int headDependenciesCurrentIndex = 0;
    
    //Define locale as English UTF-8
    const std::locale locale = std::locale("en_US.utf8");
    
    //Configuration
    std::string directoryOfPackageInformation = std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/");
    std::string packageHeadDependencyListFilename = std::string("BuildEssential_amd64.txt");
    std::string completeLocationToPackageHead = std::string(); completeLocationToPackageHead.append(directoryOfPackageInformation); completeLocationToPackageHead.append(packageHeadDependencyListFilename);
    
/*
    // //                 \\ \\
    || ||   Begin Script   || ||
    \\ \\                 // //
*/
    
    //load entry point BuildEssential_amd64.txt file
    std::ifstream entryPointofBuildEssentialsTextFile; entryPointofBuildEssentialsTextFile.open(completeLocationToPackageHead, std::ifstream::in);
    if(entryPointofBuildEssentialsTextFile.is_open() == true)
    {
        //Each line is the name to a head dependency making up the "build-essentials" virtual package.
        char line[100]; memset(line, '\0', 100); 
        entryPointofBuildEssentialsTextFile.getline(line, 100); 
        while(strlen(line) > 0)
        {
            //Text representation to Object (dependency) representation
            dependency newDependency = dependency(); 
            newDependency.initialize(); 
            newDependency.setDependencyName(std::string(line));
            newDependency.setIsHead(true);
            headDependencies[headDependenciesCurrentIndex] = newDependency; headDependenciesCurrentIndex+=1;
            
            //Instruct dependency to collect its prerequisites.
            newDependency.determinePrerequisites(directoryOfPackageInformation);
            
            //Reset for next iteration of while loop
            memset(line, '\0', 100); entryPointofBuildEssentialsTextFile.getline(line, 100);
        }
    }
    entryPointofBuildEssentialsTextFile.close();
    
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
