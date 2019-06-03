#include "dependency.h"

/*
    // //                                        \\ \\
    || ||   Constructor, Destructor, Initialize   || ||
    \\ \\                                        // //
*/

dependency::dependency()
{
    isNull = false;
    id = -1;
    totalPrerequisites = 0;
}
dependency::~dependency()
{
    isNull = false;
    id = 0;
    totalPrerequisites = 0;
}


void dependency::initialize()
{
    name = (char*)malloc(100 * sizeof(char*));
    memset(name, '\0', 100);
    for(int i = 0; i < 100; i++){ prerequisiteGlobalIdentifier[i] = -1; }
}

void dependency::initializeAsNull(){ isNull = true; }

/*
    // //                                         \\ \\
    || ||  Primal Conviences, Append Information   || ||
    \\ \\                                         // //
*/
void dependency::appendPrerequisite(int prerequisiteGlobalId)
{ 
    prerequisiteGlobalIdentifier[totalPrerequisites] = prerequisiteGlobalId;
    totalPrerequisites++;
}

/*
    // //                                      \\ \\
    || ||  Primal Conviences, Set Information   || ||
    \\ \\                                      // //
*/
void dependency::setGlobalIdentifier(int identifier){ id = identifier; }
void dependency::setDependencyName(char* nameToSetAs){ strcpy(name, nameToSetAs); }


/*
    // //                                      \\ \\
    || ||  Primal Conviences, Get Information   || ||
    \\ \\                                      // //
*/
bool dependency::getIsNull(){ return isNull; }
char* dependency::getDependencyName(){ return name; }
int dependency::getGlobalIdentifier(){ return id; }
int dependency::getTotalPrerequisites(){ return totalPrerequisites; }
int dependency::getPrerequisiteGlobalIdentifierByLevel(int level){ return prerequisiteGlobalIdentifier[level]; }
bool dependency::containsPrerequisite(int suspectPrerequisiteGlobalIdentifier)
{
    bool output = false;
    for(int i = 0; i < totalPrerequisites-1; i++)
    {
        if(prerequisiteGlobalIdentifier[i] == suspectPrerequisiteGlobalIdentifier)
        {
            output = true;
            
            //end for loop
            i = totalPrerequisites;
        }
    }
    return output;
}
