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
    if(totalPrerequisites > 0)
    {
        previousDepthsPrerequisiteGlobalIdentifier = headDependencyGlobalIdentifier;
        //std::cout << previousDepthsPrerequisiteGlobalIdentifier << " " << getDependencyByGlobalId(headDependencyGlobalIdentifier).getDependencyName() << "\n";
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
            if(totalPrerequisites > 0)
            {
                //ghost queue, append to queue
                bool containsDependency = newQueue.contains(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0));
                if(containsDependency == true)
                {
                    keep_looping = false;
                }else if(containsDependency == false)
                { 
                    newQueue.appendToEnd(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0), 0); 
                    for(int i = 0; i < newQueue.getQueueLength(); i++)
                    {
                        //std::cout << " ";
                    }
                    //std::cout << prerequisite.getPrerequisiteGlobalIdentifierByLevel(0) << " " << getDependencyByGlobalId(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0)).getDependencyName() <<"\n";
                }
            }else if(totalPrerequisites == 0)
            {
                newQueue.appendToEnd(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0), 0); 
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
/** TEMP MUTED:
for(int a = 0; a < headDependenciesGlobalIdentifierSize-1; a++)
{
    ghostqueue headToTailQueue = determineGlobalIdPerDepthEveryLevelZero(headDependenciesGlobalIdentifier[a]);
    generatedGhostQueues[ghostQueuesSize] = headToTailQueue;
    ghostQueuesSize += 1;
    

}
*/

/* Generate successive queues by the following rules...
 *  Assumption: the last queue has ended with a tail.(finite)(tail indicates no dependencies)
 *  [1]Get the dependency parent of the tail
 *      [1-1]if   parent has a level higher(number) dependency then the level the tail is found on (determine by increase the level at the depth of the last queue)
 * 
 *           then append parent' next level' dependency to ghost queue
 *                loop to deepest depth of parent' next level' dependency' prerequisites (ignoring already virtually "installed" dependencies),
 *                appending each successive depedency global identifier per loop.
 *      [1-2]else if parent has no level higher(number) dependency
 *           then complete this queue with a (one) removed tail end(dependency will be registered to a virtual "installed" listed to prevent traversing again (infinite recursion prevetion)).
 * Stop generating when the last generated ghost queue is reduced down to the head dependency.
 */
ghostqueue headToTailQueue = determineGlobalIdPerDepthEveryLevelZero(headDependenciesGlobalIdentifier[0]);

//note: ghostqueue tail = headToTailQueue.getTail();
//[1]
int depthOfparentOfTail = (headToTailQueue.getQueueLength()-1 == 0) ? 1 : headToTailQueue.getQueueLength()-1;
std::cout << depthOfparentOfTail << "\n";
std::cout << getDependencyByGlobalId( std::get<0>(headToTailQueue.getDependencyAtDepth(depthOfparentOfTail)) ).getDependencyName() << "\n";
depthOfparentOfTail = (depthOfparentOfTail-1 == 0) ? 1 : depthOfparentOfTail-1;
std::cout << depthOfparentOfTail << "\n";
std::cout << getDependencyByGlobalId( std::get<0>(headToTailQueue.getDependencyAtDepth(depthOfparentOfTail)) ).getDependencyName() << "\n";
//dependency parentOfTail = getDependencyByGlobalId(std::get<0>());
    //[1-1]
    /*get last processed dependency level at depth of parent-of-tail*/
  //  int current_secondToLastDepth = std::get<0>(headToTailQueue.getDependencySecondToLastDepth());
   // int suspectExistance_secondToLastDepth = current_secondToLastDepth + 1;
   // std::cout << current_secondToLastDepth << " " << suspectExistance_secondToLastDepth << "\n";


//TODO: Loop through each trail and print out its, trail of breadcrumb information.

    //end of main()
    return 0;
}







/************ NOTE CODE ***********************
 *     bool keep_looping = true;
    while(keep_looping == true)
    {
        /** NEW QUEUE **
        ghostqueue newQueue;
        
        //Referencing the following headToTailQueue
        ghostqueue lastGeneratedQueue = generatedGhostQueues[ghostQueuesSize-1];
        
        //Initialize newQueue with lastGeneratedQueue data.
        int normalizedQueueLength = (lastGeneratedQueue.getQueueLength()-1 == 0) ? 1 : lastGeneratedQueue.getQueueLength()-1;
        for(int b = 0; b < normalizedQueueLength; b++){ newQueue.appendToEnd(std::get<0>(lastGeneratedQueue.getDependencyAtDepth(b)), std::get<1>(lastGeneratedQueue.getDependencyAtDepth(b))); }
        
        
        //Get the dependency global identifier before the last depth (second to last depth).
        if(newQueue.getQueueLength() >= 3)
        {
            int secondToLastglobalId = std::get<0>(newQueue.getDependencySecondToLastDepth());
            int secondToLastLevel = std::get<1>(newQueue.getDependencySecondToLastDepth());
            
            //if second to last dependency has a higher(number) prerequisite level than the current level then append second to last dependency' higher (number) level
            dependency secondToLastDependency = getDependencyByGlobalId(secondToLastglobalId);
            std::cout << secondToLastglobalId << " " << secondToLastLevel << " " << secondToLastDependency.getDependencyName() << "\n";
            int proposedNextLevel = secondToLastLevel + 1;
            int normalizedTotalPrerequisites = (secondToLastDependency.getTotalPrerequisites()-1 == 0) ? 1 : secondToLastDependency.getTotalPrerequisites()-1;
            std::cout << proposedNextLevel << " " << normalizedTotalPrerequisites << "\n";
            if(proposedNextLevel < normalizedTotalPrerequisites)
            {
                //loop to the deepest depth of the second to last' next level' dependency prerequisites (ignoring already virtually "installed" dependencies), appending each successive dependency global identifier per loop.
                //std::cout << "next level yes\n";
                int previousDepthsPrerequisiteGlobalIdentifier = secondToLastDependency.getPrerequisiteGlobalIdentifierByLevel(proposedNextLevel);
                std::cout << "second to last dep global id: " << previousDepthsPrerequisiteGlobalIdentifier << "\n";
                bool keep_traversing_depth = true;
                while(keep_traversing_depth == true)
                {
                    std::cout << "traversing depth, prev global id is:" << previousDepthsPrerequisiteGlobalIdentifier << "\n"; 
                    //Is there a next depth as indicated by the existance of a first level prerequisite of the dependency.
                    dependency prerequisite = getDependencyByGlobalId(previousDepthsPrerequisiteGlobalIdentifier);
                    if(prerequisite.getIsNull() == false)
                    {//Next depth exists, get next depth global id and append to ghost queue.
                        if(prerequisite.getTotalPrerequisites() > 0)
                        {
                            //This next depth has dependencies.
                            previousDepthsPrerequisiteGlobalIdentifier = prerequisite.getPrerequisiteGlobalIdentifierByLevel(0);
                            std::cout << "next depth global id:" <<  previousDepthsPrerequisiteGlobalIdentifier << "\n";
                            //ghost queue, append to queue
                            bool containsDependency = newQueue.contains(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0));
                            if(containsDependency == true)
                            {
                                keep_traversing_depth = false;
                            }
                            newQueue.appendToEnd(prerequisite.getPrerequisiteGlobalIdentifierByLevel(0), 0);
                        }else if(prerequisite.getTotalPrerequisites() == 0)
                        {
                            //This next depth has no dependencies.
                            keep_traversing_depth = false;
                        }
                        
                    }else if(prerequisite.getIsNull() == true)
                    {
                        keep_traversing_depth = false;
                    }
                }
            }else if(proposedNextLevel >= normalizedTotalPrerequisites)
            {
                std::cout << "no more prerequisites, this is the tail for this new ghost queue\n";
                newQueue.removeTailEnd();
            }            
        }else if(newQueue.getQueueLength() < 3)
        {
            std::cout << "detected to stop generating\n";
            //Head dependency reached (stop generating for this head)
            //TODO: ^
        }
        ** END OF NEW QUEUE **
        
        //temp
        keep_looping = false;
    }
************/
