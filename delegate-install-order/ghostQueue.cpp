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
    for(int a = 0; a < headToTailGlobalIdentifiers.size(); a++)
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


std::pair<int, int> ghostqueue::getDependencyAtDepth(int depth)
{
    std::pair<int, int> output(headToTailGlobalIdentifiers[depth], headToTailLevels[depth]);
    return output;
}

void ghostqueue::removeTailEnd()
{
    headToTailGlobalIdentifiers.pop_back();
    headToTailLevels.pop_back();
}

void ghostqueue::setLevelAtDepth(int setGlobalIdAs, int setLevelAs, int depth)
{
    headToTailGlobalIdentifiers[depth] = setGlobalIdAs;
    headToTailLevels[depth] = setLevelAs;
}

void ghostqueue::removeDependencyAtDepth(int depth)
{
    headToTailGlobalIdentifiers.erase(headToTailGlobalIdentifiers.begin()+depth);
    headToTailLevels.erase(headToTailLevels.begin()+depth);
}
