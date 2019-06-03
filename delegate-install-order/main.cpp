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
int tailDependenciesGlobalIdentifier[100];
int tailDependenciesGlobalIdentifierSize = 0;
int dependenciesNotYetIncluded[100];
int dependenciesNotYetIncludedSize = 0;


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

int determineDeepestDepthOfEveryLevelAsZero()
{
    int output = -1;
    
    //Determine the deepest depth
    int deepestDepthFound = 0; //0 = root, 1 = sublevel, and so on.
    int currentBreadcrumbProcessDepth = -1;

    /** Define initial breadcrumb process, get first dependency of each parent dependency until it ends, count the depth length **/
    int previousDepthsPrerequisiteGlobalIdentifier = -1;
    if(headDependenciesGlobalIdentifier[0] > 0)
    {
        currentBreadcrumbProcessDepth += 1;
        previousDepthsPrerequisiteGlobalIdentifier = headDependenciesGlobalIdentifier[0];
    }

    bool keep_looping = true;
    while(keep_looping == true)
    {
        //Is there a next depth as indicated by the existance of a first level prerequisite of the dependency.
        dependency prerequisite = getDependencyByGlobalId(previousDepthsPrerequisiteGlobalIdentifier);
        if(prerequisite.getIsNull() == false)
        {
            currentBreadcrumbProcessDepth += 1;
            previousDepthsPrerequisiteGlobalIdentifier = prerequisite.getPrerequisiteGlobalIdentifierByLevel(0);
            
        }else if(prerequisite.getIsNull() == true)
        {
            keep_looping = false;
        }
    }

    deepestDepthFound = currentBreadcrumbProcessDepth;
    output = deepestDepthFound;
    return output;
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
    
//Determine tail of dependencies
//loop through entireDependencyList, storing the global identifiers of prerequisites that have no dependencies.
for(int i = 0; i < entireDependencyListSize-1; i++)
{
    dependency prerequisite = entireDependencyList[i];
    if(prerequisite.getTotalPrerequisites() == 0)
    {
        //Is a tail end, append to tail
        tailDependenciesGlobalIdentifier[tailDependenciesGlobalIdentifierSize] = prerequisite.getGlobalIdentifier();
        tailDependenciesGlobalIdentifierSize += 1;
    }
}

//Populate dependenciesNotYetIncluded list
for(int i = 0; i < dependenciesNotYetIncludedSize; i++)
{
    dependenciesNotYetIncluded[i] = entireDependencyList[i].getGlobalIdentifier();
    dependenciesNotYetIncludedSize += 1;
}


//Trail Generation will require a class too complex for functions in main.cpp alone...
//(Trail generation will only be aware of one head dependency, this can be re-ran again later made as a function for other starting heads)
//Generate trails, prevent collisions.
//while keep looping == true

//end while

int anticipatedMaxDepth = 5;
//has 0 0 0 0 0 been done before? no? add it
//    1 1 2 3 5
//has 0 0 0 0 1 been done before? no  add it?
//    1 1 2 3 5

//main level
for(int a = 0; a < getDependencyByGlobalId(headDependenciesGlobalIdentifier[0]).getTotalPrerequisites(); a++)
{
    //second level
    dependency secondLevel = getDependencyByGlobalId( getDependencyByGlobalId(headDependenciesGlobalIdentifier[0]).getPrerequisiteGlobalIdentifierByLevel(a) );
    if(secondLevel.getTotalPrerequisites() > 0)
    {
        for(int b = 0; b < secondLevel.getTotalPrerequisites(); b++)
        {
            
            dependency thirdLevel = getDependencyByGlobalId(secondLevel.getPrerequisiteGlobalIdentifierByLevel(b));
            for(int c = 0; c < thirdLevel.getTotalPrerequisites(); c++)
            {
                dependency fourthLevel = getDependencyByGlobalId(thirdLevel.getPrerequisiteGlobalIdentifierByLevel(c));
                
                for(int d = 0; d < fourthLevel.getTotalPrerequisites(); d++)
                {
                    dependency fifthLevel = getDependencyByGlobalId(fourthLevel.getPrerequisiteGlobalIdentifierByLevel(d));
                    std::cout << a << " " << b << " " << c << " " << d << "\n";
                }
            }
        }
    }
    
    std::cout << "\n";
}





//TODO: Loop through each trail and print out its, trail of breadcrumb information.

    //end of main()
    return 0;
}
