#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include "dependency.cpp"


dependency entireDependencyList[100];
int entireDependencyListSize = 0;
int nextAvailableGlobalIdentifier = 1;
int headDependenciesGlobalIdentifier[100];
int headDependenciesGlobalIdentifierSize = 0;

dependency getDependencyByGlobalId(int globalId)
{
    bool prerequisiteFound = false;
    for(int a = 0; a < entireDependencyListSize; a++)
    {
        if(entireDependencyList[a].getGlobalIdentifier() == globalId)
        {
            prerequisiteFound = true;
            return entireDependencyList[a];
        }
    }
    if(prerequisiteFound == false){ dependency prerequisite; prerequisite.initializeAsNull(); return prerequisite; }
}

int main()
{    
    //Initialize and Define
    for(int i = 0; i < 100; i++){ headDependenciesGlobalIdentifier[i] = -1; }
    
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
        entireDependencyList[entireDependencyListSize] = prerequisite;
        entireDependencyListSize += 1;

        //Reset for next iteration of while loop
        memset(line, '\0', 100);
        manifestTextFile.getline(line, 100);
    }
}



//Loop through each item in unlinked list, make each object aware of its prerequisite name and global identifiers.
for(int i = 0; i < entireDependencyListSize; i++)
{
    //Open file that contains list of prerequisites for this dependency.
    std::string prerequisiteListTextFileLocation = std::string(); prerequisiteListTextFileLocation.append(directoryOfPackageInformation); prerequisiteListTextFileLocation.append(entireDependencyList[i].getDependencyName()); prerequisiteListTextFileLocation.append(".txt");
    std::ifstream prerequisiteListTextFile; prerequisiteListTextFile.open(prerequisiteListTextFileLocation, std::ifstream::in);
    if(prerequisiteListTextFile.is_open() == true)
    {
        //For each text prerequisite in list, append as prerequisite to dependency object.  
        char dependencyName[100];
        memset(dependencyName, '\0', 100);
        prerequisiteListTextFile.getline(dependencyName, 100); 
        while(strlen(dependencyName) > 0)
        { 
            //Loop through entireDependencyList list in search of dependency object named the content of dependencyName.
            bool prerequisiteFound = false;
            dependency prerequisite;
            for(int a = 0; a < entireDependencyListSize; a++)
            {
                if(strcmp(dependencyName, entireDependencyList[a].getDependencyName()) == 0)
                {
                    prerequisiteFound = true;
                    prerequisite = entireDependencyList[a];
                    
                    //end loop
                    a = entireDependencyListSize;
                }
            }
            
            if(prerequisiteFound == true)
            {
                //Append prerequisite information to the dependency.
                entireDependencyList[i].appendPrerequisite(prerequisite.getGlobalIdentifier());
            }
            

            //Reset for next iteration of while loop
            memset(dependencyName, '\0', 100);
            prerequisiteListTextFile.getline(dependencyName, 100);
        }
    }
}
   

//Determine head dependencies
std::string headDependencyListTextFileLocation = std::string(); headDependencyListTextFileLocation.append(directoryOfPackageInformation); headDependencyListTextFileLocation.append(packageHeadDependencyListFilename);
std::ifstream headDependencyListTextFile; headDependencyListTextFile.open(headDependencyListTextFileLocation, std::ifstream::in);
if(headDependencyListTextFile.is_open() == true)
{
    char dependencyName[100];
    memset(dependencyName, '\0', 100);
    headDependencyListTextFile.getline(dependencyName, 100); 
    while(strlen(dependencyName) > 0)
    { 
        //Loop through entireDependencyList list in search of dependency object named the content of dependencyName.
        bool prerequisiteFound = false;
        dependency prerequisite;
        for(int a = 0; a < entireDependencyListSize; a++)
        {
            if(strcmp(dependencyName, entireDependencyList[a].getDependencyName()) == 0)
            {
                prerequisiteFound = true;
                prerequisite = entireDependencyList[a];
                
                //end loop
                a = entireDependencyListSize;
            }
        }
        
        if(prerequisiteFound == true)
        {
            headDependenciesGlobalIdentifier[headDependenciesGlobalIdentifierSize] = prerequisite.getGlobalIdentifier();
            headDependenciesGlobalIdentifierSize += 1;
            //std::cout << prerequisite.getGlobalIdentifier() << "\n";
        }
        
        //Reset for next iteration of while loop
        memset(dependencyName, '\0', 100);
        headDependencyListTextFile.getline(dependencyName, 100);
    }
}
    


//Determine the deepest depth
int deepestDepthFound = 0; //0 = root, 1 = sublevel, and so on.
int lastBreadcrumbProcessed[100]; for(int i = 0; i < 100; i++){ lastBreadcrumbProcessed[i] = -1; }
int currentBreadcrumbProcess[100]; for(int i = 0; i < 100; i++){ currentBreadcrumbProcess[i] = -1; }
int currentBreadcrumProcessDepth = -1;

/** Define initial breadcrumb process, 
    *  get first dependency of each sublevel until it ends, 
    *  count the depth length and configure currentBreadcrumbProcess with that many zeros across the array. **/
int previousDepthsPrerequisiteGlobalIdentifier = -1;
if(headDependenciesGlobalIdentifier[0] > 0)
{
    currentBreadcrumProcessDepth += 1;
    currentBreadcrumbProcess[currentBreadcrumProcessDepth] = 0;
    previousDepthsPrerequisiteGlobalIdentifier = headDependenciesGlobalIdentifier[0];
}

bool keep_looping = true;
while(keep_looping == true)
{
    std::cout << previousDepthsPrerequisiteGlobalIdentifier << "\n";
    //Is there a next depth as indicated by the existance of a first level prerequisite of the dependency.
    dependency prerequisite = getDependencyByGlobalId(previousDepthsPrerequisiteGlobalIdentifier);
    if(prerequisite.getIsNull() == false)
    {
        //Next depth exists
        currentBreadcrumProcessDepth += 1;
        currentBreadcrumbProcess[currentBreadcrumProcessDepth] = 0;
        previousDepthsPrerequisiteGlobalIdentifier = prerequisite.getPrerequisiteGlobalIdentifierByLevel(0);
        
    }else if(prerequisite.getIsNull() == true)
    {
        keep_looping = false;
    }
}
    
    
    //std::cout << "first level of every dependency has the deepest depth of: " << currentBreadcrumProcessDepth << "\n";

/** now process using breadcrumb for processing....
bool keep_looping = true;
while(keep_looping == true)
{
**/
   
/**
}
**/
   
   
   
   
   
   
   
   
   
   
   
   
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
