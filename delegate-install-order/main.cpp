#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include "dependency.cpp"
#include "breadcrumb.cpp"
#include "breadcrumb_trail.cpp"


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

int determineDeepestDepthOfEveryLevel(int horizontalDepthValueLevel[])
{
    
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
    

/*TODO: when the deepest depth of that level-per-depth-of-prerequisites is found,
 *      install that debian package, 
 *      store the entire breadcrumb trail as an array managed by a per class basis,
 *      append breadcrumb trail to a class that will store the history of installations (history of breadcrumbs),
 *      when moving up(or down?) a depth and or level, check the history to determine if it has been previously been installed as such, if not, install deb package, keep installing.
 *      
 */




breadcrumb_trail* breadcrumbTrails = (breadcrumb_trail*)malloc(100000 * sizeof(breadcrumb_trail));if(breadcrumbTrails == nullptr){ std::cout << "failed allocation breadcrumb trail"; }
int breadcrumbTrailsSize = 0;

//initial trail.
breadcrumb_trail initialTrail;
int deepestDepthOfLevelsZero = determineDeepestDepthOfEveryLevelAsZero();
initialTrail.appendBreadCrumb(headDependenciesGlobalIdentifier[0], 0);
dependency headDepZeroLevel = getDependencyByGlobalId(headDependenciesGlobalIdentifier[0]);
int headDepPrerequisiteGlobalId = headDepZeroLevel.getPrerequisiteGlobalIdentifierByLevel(0);
//append breadcrumbs to initial trail.
int lastPrerequisiteGlobalId = headDepPrerequisiteGlobalId;
for(int i = 1; i < deepestDepthOfLevelsZero; i++)
{
    int dependencyGlobalId = -1;
    
    //get next prerequisite (at level zero) global id.
    dependency currentPrerequisite = getDependencyByGlobalId(lastPrerequisiteGlobalId);
    if(currentPrerequisite.getTotalPrerequisites() > 0)
    {
        dependencyGlobalId = currentPrerequisite.getPrerequisiteGlobalIdentifierByLevel(0);
        //append information to breadcrumb trail.
        initialTrail.appendBreadCrumb(dependencyGlobalId, 0);
        //Setup for next iteration
        lastPrerequisiteGlobalId = dependencyGlobalId;
    }else{ i = deepestDepthOfLevelsZero; }
}
breadcrumbTrails[0] = initialTrail;
breadcrumbTrailsSize += 1;


//Continue producing next trails until end of headDependencies.
breadcrumb_trail secondTrail;
//TODO: int deepestDepthOfLevelsSecondTrail = determineDeepestDepthOfEveryLevel();

//WHILE AUTOMATION FOR REST OF TRAIL QUEUE.

//Continue producing trails until process has completed.
/************
int a = 0;
bool keep_looping = true;
while(a < 5)
{
    a++;
    
    //get current breadcrumbTrail to process from.
    breadcrumb_trail trail = breadcrumbTrails[breadcrumbTrailsSize-1];

    //determine if tail end breadcrumb can move down a level
    int breadcrumbGlobalIdentifier = trail.tailEndGlobalIdentifier();
    dependency prerequisite = getDependencyByGlobalId(breadcrumbGlobalIdentifier);
    int totalPrerequisites = prerequisite.getTotalPrerequisites();
    int currentPrerequisiteLevel = trail.tailEndCurrentLevel();
    int proposedNextPrerequisiteLevel = currentPrerequisiteLevel + 1;
    int normalizedTotalPrerequisites = (totalPrerequisites==0 ? 0 : totalPrerequisites-1);
    std::cout << proposedNextPrerequisiteLevel << " " << normalizedTotalPrerequisites << "\n";
    if(proposedNextPrerequisiteLevel == totalPrerequisites)
    {
        std::cout << "can move down\n";
        //Can move down a level, create a new trail with the modified level number.
        breadcrumb_trail newTrail;
        for(int i = 0; i < trail.totalBreadcrumbs(); i++)
        {
            //Coder-Copy breadcrumb at index position i to new trail (if last breadcrum, instead of copying use the modified level number.)
            breadcrumb* breadcrumbAtIndex = trail.getBreadcrumbByIndex(i);
            if(i < trail.totalBreadcrumbs()-1)
            {
                newTrail.appendBreadCrumb(breadcrumbAtIndex->getGlobalIdentifier(), breadcrumbAtIndex->getCurrentLevel());
            }else if(i >= trail.totalBreadcrumbs()-1)
            {
                //Last breadcrumb, use modified level number.
                if(breadcrumbAtIndex->getCurrentLevel() + 1 <= getDependencyByGlobalId(breadcrumbAtIndex->getGlobalIdentifier()).getTotalPrerequisites())
                {
                    newTrail.appendBreadCrumb(breadcrumbAtIndex->getGlobalIdentifier(), (breadcrumbAtIndex->getCurrentLevel() + 1));
                }else
                {
                    //No more levels at this depth,
                    //this breadcrumb has been completly explored.
                    //Do not append bread crumb in this case.
                }
            }
        }
        //Append trail to breadcrumbTrails
        breadcrumbTrails[breadcrumbTrailsSize] = newTrail;
        breadcrumbTrailsSize += 1;
    }else if(proposedNextPrerequisiteLevel != totalPrerequisites)
    {
        std::cout << "end of prerequisites\n";
        //End of prerequisites, create a new trail with this breadcrumb removed.
        breadcrumb_trail newTrail;
        for(int i = 0; i < trail.totalBreadcrumbs()-1; i++)
        {
            //get current breadcrumb information
            breadcrumb* currentBreadcrumbAtIndex = trail.getBreadcrumbByIndex(i);
            //create new breadcrumb intended for new trail.
            breadcrumb* newBreadcrumbAtIndexForNewTrail = new breadcrumb();
            //append breadcrumb
            newTrail.appendBreadCrumb(currentBreadcrumbAtIndex->getGlobalIdentifier(), currentBreadcrumbAtIndex->getCurrentLevel());
        }
        //Append trail to breadcrumbTrails
        breadcrumbTrails[breadcrumbTrailsSize] = newTrail;
        breadcrumbTrailsSize += 1;
    }
    
}

********/











   
   
   
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
