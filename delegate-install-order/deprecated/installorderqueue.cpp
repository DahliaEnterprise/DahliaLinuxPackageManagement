#ifndef INSTALLORDERQUEUE_CPP
#define INSTALLORDERQUEUE_CPP

#include "installorderqueue.h"

installOrderQueue::installOrderQueue()
{

}

void installOrderQueue::initialize()
{
  installOrder = new std::vector<std::pair<int, int>>();
}

void installOrderQueue::appendAsDepth(int dependencyUniqueId, int zeroBasedLevel)
{
 std::pair<int, int> newDepth(dependencyUniqueId, zeroBasedLevel);
 installOrder->push_back(newDepth);
}

int installOrderQueue::dependencyUniqueIdOfTail()
{
  int output = -1;
  int normalizedInstallOrderSize = (installOrder->size()-1 <= 0) ? 0 : (installOrder->size()-1);
  int dependencyUniqueId = -1;
  dependencyUniqueId = std::get<0>(installOrder->at(normalizedInstallOrderSize));
  output = dependencyUniqueId;
  return output;
}

int installOrderQueue::getLevelAtTailDepth()
{
  int output = -1;
  int normalizedInstallOrderSize = (installOrder->size()-1 <= 0) ? 0 : (installOrder->size()-1);
  int level = -1;
  level = std::get<1>(installOrder->at(normalizedInstallOrderSize));
  output = level;
  return output;
}



std::vector<std::pair<int, int>>* installOrderQueue::getInstallOrder()
{
  return installOrder;
}

void installOrderQueue::redefineLevelOfTail(int uniqueIdToSetAs, int levelToSetAs)
{
  installOrder->pop_back();
  installOrder->push_back(std::pair<int,int>(uniqueIdToSetAs, levelToSetAs));
}

void installOrderQueue::removeDepthTail()
{
  //prevent head from being removed
  if(installOrder->size() > 1){
    //remove tail
    installOrder->pop_back();
  }
}

void installOrderQueue::printInstallOrderQueue(entireDependencyList* manifest)
{
  int normalizedArrayLength = (installOrder->size()-1 <= 0) ? 0 : installOrder->size()-1;
  for(int a = 0; a <= normalizedArrayLength; a++)
  {
    dependency* dep = manifest->getDependencyByUniqueId(std::get<0>(installOrder->at(a)));
    std::cout << std::get<0>(installOrder->at(a)) << " " << std::get<1>(installOrder->at(a)) << " " << dep->getName() <<  "\n";
  }

  std::cout << "\n";
}

#endif
