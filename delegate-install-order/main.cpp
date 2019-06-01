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
            newDependency.determinePrerequisites();
            //TODO ^^
            //Reset for next iteration of while loop
            memset(line, '\0', 100); entryPointofBuildEssentialsTextFile.getline(line, 100);
        }
    }
    entryPointofBuildEssentialsTextFile.close();
    
    
    /** DEPRECATED
    dependency entryPointofBuildEssentials = dependency(); entryPointofBuildEssentials.setIsHead(true);
        dependency dpkg_dev = dependency(); dpkg_dev.setDependencyName(std::string("dpkg-dev"));
            dependency binutils = dependency(); binutils.setDependencyName(std::String("binutils"));
                dependency libc6_dev = dependency(); libc6_dev.set
        dpkg_dev.appendPrerequisite(binutils);
            
        
        dependency gpp = dependency(); gpp.setDependencyName(std::string("g++"));
        dependency libc6_dev = dependency(); libc6_dev.setDependencyName(std::string("libc6-dev"));
    **/
    //TODO: reference depencesinces and prerequiriestes
    return 0;
}
