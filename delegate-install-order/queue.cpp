#include "queue.h"
queue::queue()
{
    
}

queue::~queue()
{
    
}

void queue::defineFromVectorHeadToTailAllZeroLevels(std::vector<int> GlobalIdsfromHeadToTailAllZeroLevels)
{ 
    for(int i = 0; i < GlobalIdsfromHeadToTailAllZeroLevels.size(); i++)
    { 
        headToTailGlobalIdentifiers.push_back(GlobalIdsfromHeadToTailAllZeroLevels[i]); 
        headToTailLevels.push_back(0);//zero level.
        std::cout << GlobalIdsfromHeadToTailAllZeroLevels[i] << "\n";; 
    } 
}
