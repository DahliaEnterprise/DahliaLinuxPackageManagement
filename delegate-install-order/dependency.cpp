#include "dependency.h"

/*
    // //                                        \\ \\
    || ||   Constructor, Destructor, Initialize   || ||
    \\ \\                                        // //
*/

dependency::dependency()
{
    name = std::string();
    isHead = false;
    hasPrerequisites = false;
    totalPrerequisites = 0;
    dependenciesMemorySize = 0;
    dependenciesAvailableIndex = 0;
}

dependency::~dependency()
{
    name.clear();
    isHead = false;
    hasPrerequisites = false;
    totalPrerequisites = 0;
    if(dependenciesMemorySize > 0){ dependencies = (dependency*) calloc(dependenciesMemorySize, sizeof(dependency)); free(dependencies); }
    dependenciesMemorySize = 0;
}

void dependency::initialize()
{
    dependencies = (dependency*) calloc(100, sizeof(dependency));
    dependenciesMemorySize = 100;
}

/*
    // //                   \\ \\
    || ||  Class Modifiers   || ||
    \\ \\                   // //
*/
void dependency::determinePrerequisites(std::string directoryOfPrerequisiteInformation)
{    
    //open file containing prerequisities for this dependency.
    std::string filenameAndDirectory = std::string(); filenameAndDirectory.append(directoryOfPrerequisiteInformation); filenameAndDirectory.append(name); filenameAndDirectory.append(".txt");
    std::ifstream prerequisitesForThisDependency; prerequisitesForThisDependency.open(filenameAndDirectory, std::ifstream::in);
    if(prerequisitesForThisDependency.is_open() == true)
    {
        //line-by-line get prerequisities
        char line[100]; memset(line, '\0', 100); 
        prerequisitesForThisDependency.getline(line, 100); 
        while(strlen(line) > 0)
        {
            //Text representation to Object (dependency) representation.
            dependency* prerequisite = new dependency();
            prerequisite->initialize();
            prerequisite->setDependencyName(std::string(line));
            
            //Instruct prerequisite to collect its prerequisites.
            prerequisite->determinePrerequisites(directoryOfPrerequisiteInformation);
            
            //Append prerequisite to "dependencies" array for this dependency.
            dependencies[dependenciesAvailableIndex] = *prerequisite;
            dependenciesAvailableIndex++;
            
            //Reset for next iteration of while loop
            memset(line, '\0', 100); prerequisitesForThisDependency.getline(line, 100);
        }
    }
}


/*
    // //                                      \\ \\
    || ||  Primal Conviences, Set Information   || ||
    \\ \\                                      // //
*/
void dependency::setDependencyName(std::string nameToSetAs){ name.clear(); name.append(nameToSetAs); }
void dependency::setIsHead(bool newHeadState){ isHead = newHeadState; }
