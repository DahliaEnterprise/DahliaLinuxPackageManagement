#include "ghostQueue.h"
ghostqueue::ghostqueue()
{
    isNull = false;
}

ghostqueue::~ghostqueue()
{
    
}


void ghostqueue::appendToEnd(int globalId, int level)
{
    headToTailGlobalIdentifiers.push_back(globalId);
    headToTailLevels.push_back(level);
    
    
    //this->managePotentialDuplicate(globalId, level);
}

bool ghostqueue::contains(int globalId)
{
    bool output = false;
    bool duplicateDetected = false;
    for(int a = 0; a < headToTailGlobalIdentifiers.size()-1; a++)
    {
        if(headToTailGlobalIdentifiers[a] == globalId)
        {
            duplicateDetected = true;
            a = headToTailGlobalIdentifiers.size();
        }
    }
    return output;
}
void ghostqueue::managePotentialDuplicate(int globalId, int level)
{
    //Detect if this global id has been included before.
    
    
    //
}
