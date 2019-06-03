#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include "dependency.cpp"
#include "queue.cpp"
#include "ghostQueue.cpp"

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

ghostqueue determineGlobalIdPerDepthEveryLevelZero(int headDependencyGlobalIdentifier)
{
    ghostqueue output; 
    
    ghostqueue newQueue;
    
    /** Define initial breadcrumb process, get first dependency of each parent dependency until it ends, count the depth length **/
    int previousDepthsPrerequisiteGlobalIdentifier = -1;//keeps state
    
    int totalPrerequisites = getDependencyByGlobalId(headDependencyGlobalIdentifier).getTotalPrerequisites();
    int normalizedTotalPrerequisites =  (totalPrerequisites-1) == 0 ? 1 : (totalPrerequisites-1);
    if(normalizedTotalPrerequisites > 0)
    {
        previousDepthsPrerequisiteGlobalIdentifier = headDependencyGlobalIdentifier;
        std::cout << previousDepthsPrerequisiteGlobalIdentifier << " " << getDependencyByGlobalId(headDependencyGlobalIdentifier).getDependencyName() << "\n";
        //ghost queue, append to queue
        newQueue.appendToEnd(headDependencyGlobalIdentifier, 0);
    }

    bool keep_looping = true;
    while(keep_looping == true)
    {
        //Is there a next depth as indicated by the existance of a first level prerequisite of the dependency.
        dependency prerequisite = getDependencyByGlobalId(previousDepthsPrerequisiteGlobalIdentifier);
        if(prerequisite.getIsNull() == false)
        {
            previousDepthsPrerequisiteGlobalIdentifier = prerequisite.getPrerequisiteGlobalIdentifierByLevel(0);
            
            int totalPrerequisites = getDependencyByGlobalId(previousDepthsPrerequisiteGlobalIdentifier).getTotalPrerequisites();
            int normalizedTotalPrerequisites =  (totalPrerequisites-1) == 0 ? 1 : (totalPrerequisites-1);
            if(normalizedTotalPrerequisites > 0)
            {
                
                //ghost queue, append to queue
                bool containsDependency = newQueue.contains(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0));
                if(containsDependency == true){ keep_looping = false; }else{
                    for(int i = 0; i < newQueue.getQueueLength(); i++)
                    {
                        std::cout << " ";
                    }
                    std::cout << prerequisite.getPrerequisiteGlobalIdentifierByLevel(0) << " " << getDependencyByGlobalId(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0)).getDependencyName() <<"\n";
                    newQueue.appendToEnd(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0), 0); }
            }else if(normalizedTotalPrerequisites == 0)
            {
                keep_looping = false;
            }
            
        }else if(prerequisite.getIsNull() == true)
        {
            keep_looping = false;
        }
    }
    
    output = newQueue;

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


/*
    // //                 \\ \\
    || ||  Load Manifest   || ||
    \\ \\                 // //
*/
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

   
/*
    // //                             \\ \\
    || ||   Detect Head Dependencies   || ||
    \\ \\                             // //
*/
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
    
/*
    // //                    \\ \\
    || ||   Generate Queues   || ||
    \\ \\                    // //
*/
ghostqueue* generatedGhostQueues = (ghostqueue*)malloc(100000 * sizeof(ghostqueue));
int ghostQueuesSize = 0;

//Generate the expected zero level queues per one head.
for(int a = 0; a < headDependenciesGlobalIdentifierSize-1; a++)
{
    ghostqueue headToTailQueue = determineGlobalIdPerDepthEveryLevelZero(headDependenciesGlobalIdentifier[a]);
    generatedGhostQueues[ghostQueuesSize] = headToTailQueue;
    ghostQueuesSize += 1;
    
    bool keep_looping = false;
    while(keep_looping == true)
    {
        ghostqueue newQueue;
        
        //Referencing the following headToTailQueue
        ghostqueue lastGeneratedQueue = generatedGhostQueues[ghostQueuesSize-1];
        
        //Initialize newQueue with lastGeneratedQueue data.
        int normalizedQueueLength = (lastGeneratedQueue.getQueueLength()-1 == 0) ? 1 : lastGeneratedQueue.getQueueLength()-1;
        for(int b = 0; b < normalizedQueueLength; b++)
        {
            //TODO iterate through lastGeneratedQueue and append to newqueue
            std::cout << std::get<0>(lastGeneratedQueue.getDependencyAtDepth(b)) << "\n";
            std::cout << std::get<1>(lastGeneratedQueue.getDependencyAtDepth(b)) << "\n\n";
        }
        
        //Get the dependency global identifier before the last depth (second to last depth).
        //std::cout << lastGeneratedQueue.getQueueLength() << "\n";
        if(lastGeneratedQueue.getQueueLength() > 3)//if second to last depth is the head dependency
        {
            int secondToLastglobalId = std::get<0>(lastGeneratedQueue.getDependencySecondToLastDepth());
            int secondToLastLevel = std::get<1>(lastGeneratedQueue.getDependencySecondToLastDepth());
            
            //if second to last dependency has a higher(number) prerequisite level than the current level then append second to last dependency' higher (number) level
            dependency secondToLastDependency = getDependencyByGlobalId(secondToLastglobalId);
            int proposedNextLevel = secondToLastLevel + 1;
            int normalizedTotalPrerequisites = (secondToLastDependency.getTotalPrerequisites()-1 == 0) ? 1 : (secondToLastDependency.getTotalPrerequisites()-1);
            if(proposedNextLevel <= normalizedTotalPrerequisites)
            {
                //loop to the deepest depth of the second to last' next level' dependency prerequisites (ignoring already virtually "installed" dependencies), appending each successive dependency global identifier per loop.
                std::cout << "next level yes\n";
                /* muted:
                int secondToLastDependency_nextLevelGlobalId = secondToLastDependency.getPrerequisiteGlobalIdentifierByLevel(proposedNextLevel);
                int previousDepthsPrerequisiteGlobalIdentifier = secondToLastDependency_nextLevelGlobalId;
                bool keep_traversing_depth = true;
                while(keep_traversing_depth == true)
                {
                    //Is there a next depth as indicated by the existance of a first level prerequisite of the dependency.
                    dependency prerequisite = getDependencyByGlobalId(previousDepthsPrerequisiteGlobalIdentifier);
                    if(prerequisite.getIsNull() == false)
                    {
                        previousDepthsPrerequisiteGlobalIdentifier = prerequisite.getPrerequisiteGlobalIdentifierByLevel(0);
                        //ghost queue, append to queue
                        bool containsDependency = newQueue.contains(headDependencyGlobalIdentifier);
                        if(containsDependency == true){ keep_traversing_depth = false; }
                        newQueue.appendToEnd(headDependencyGlobalIdentifier, 0);
                    }else if(prerequisite.getIsNull() == true)
                    {
                        keep_traversing_depth = false;
                    }
                }
                */
            }else if(proposedNextLevel > normalizedTotalPrerequisites)
            {
                std::cout << "last level\n";
                //else if second to last dependency has no level higher(number) dependency then the last ghost queue then complete this queue with a (one) removed tail end(dependency will be registered to a virtual "installed" list to prevent traversing again (infinite recursion prevention).
            }
            
        }else if(lastGeneratedQueue.getQueueLength() < 3)
        {
            //Head dependency reached (stop generating for this head)
            //TODO: ^
        }
    }
}

/* Generate successive queues by the following rules...
 *  Assumption: the last queue has ended with a tail.(finite)(tail indicates no dependencies)
 *  Get the dependency before the last depth, (2nd2Last)
 *      if   2nd2Last has a level higher(number) dependency then the last ghost queue
 *      then append 2nd2Last' next level' dependency to ghost queue
 *                loop to deepest depth of 2nd2Last' next level' dependency' prerequisites (ignoring already virtually "installed" dependencies),
 *                appending each successive depedency global identifier per loop.
 *      else if 2nd2Last has no level higher(number) dependency then the last ghost queue
 *      then complete this queue with a (one) removed tail end(dependency will be registered to a virtual "installed" listed to prevent traversing again (infinite recursion prevetion)).
 * Stop generating when the last generated ghost queue is reduced down to the head dependency.
 */



//TODO: Loop through each trail and print out its, trail of breadcrumb information.

    //end of main()
    return 0;
}
