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
}

dependenc::~dependency()
{
    name.clear();
    isHead = false;
    hasPrerequisites = false;
    totalPrerequisites = 0;
    if(dependenciesMemorySize > 0){ dependencies = (dependency*) calloc(100, sizeof(dependency)); free(dependencies); }
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
    //TODO: open file containing prerequisities for this dependency.
    //TODO: line-by-line get prerequisities
    //TODO: append prerequisites to "dependencies" array
    //TODO: execute determine prerequisites per appended prerequisite.
}


/*
    // //                                      \\ \\
    || ||  Primal Conviences, Set Information   || ||
    \\ \\                                      // //
*/
void dependency::setDependencyName(std::string nameToSetAs){ name.clear(); name.append(nameToSetAs); }
void dependency::setIsHead(bool newHeadState){ isHead = newHeadState; }
