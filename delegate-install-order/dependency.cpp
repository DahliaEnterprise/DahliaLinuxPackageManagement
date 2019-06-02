#include "dependency.h"

/*
    // //                                        \\ \\
    || ||   Constructor, Destructor, Initialize   || ||
    \\ \\                                        // //
*/

dependency::dependency()
{
    id = -1;
    totalPrerequisites = -1;
}
dependency::~dependency()
{
    id = 0;
    totalPrerequisites = -1;
}


void dependency::initialize()
{
    name = (char*)malloc(100 * sizeof(char*));
    memset(name, '\0', 100);
}

/*
    // //                                         \\ \\
    || ||  Primal Conviences, Append Information   || ||
    \\ \\                                         // //
*/
void dependency::appendPrerequisite(int prerequisiteGlobalId){ 
    totalPrerequisites++; 
    prerequisiteGlobalIdentifier[totalPrerequisites] = prerequisiteGlobalId; }

/*
    // //                                      \\ \\
    || ||  Primal Conviences, Set Information   || ||
    \\ \\                                      // //
*/
void dependency::setGlobalIdentifier(int identifier){ id = identifier; }
void dependency::setDependencyName(char* nameToSetAs)
{
    strcpy(name, nameToSetAs);
}


/*
    // //                                      \\ \\
    || ||  Primal Conviences, Get Information   || ||
    \\ \\                                      // //
*/
char* dependency::getDependencyName(){ return name; }
int dependency::getGlobalIdentifier(){ return id; }
