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
int ghostqueue::getQueueLength()
{
    return headToTailGlobalIdentifiers.size();
}

std::pair<int, int> ghostqueue::getDependencySecondToLastDepth()
{
    int globalId = headToTailGlobalIdentifiers.at(headToTailGlobalIdentifiers.size()-2);
    int level = headToTailLevels.at(headToTailLevels.size()-2);
    return std::pair<int, int>(globalId, level);
}

std::pair<int, int> ghostqueue::getDependencyAtDepth(int depth)
{
    std::pair<int, int> output(headToTailGlobalIdentifiers[depth], headToTailLevels[depth]);
    return output;
}
