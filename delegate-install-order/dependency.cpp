#include "dependency.h"

/*
    // //                                        \\ \\
    || ||   Constructor, Destructor, Initialize   || ||
    \\ \\                                        // //
*/

dependency::dependency()
{
    id = -1;
}
dependency::~dependency()
{
    id = 0;
}


void dependency::initialize()
{
    name = (char*)malloc(100 * sizeof(char*));
    memset(name, '\0', 100);
}

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


char* dependency::getDependencyName(){ return name; }
