#include "installorderqueue.h"

installOrderQueue::installOrderQueue()
{

}


void installOrderQueue::initialize(){ installOrder = new std::vector<std::pair<int, int>>(); }

void installOrderQueue::appendDependency(int dependencyId, int level)
{
  std::pair<int, int> nextInstallOrder(dependencyId, level);
  installOrder->push_back(nextInstallOrder);
}

int installOrderQueue::getTailId()
{
  int normalizedArrayLength = (installOrder->size()-1 <= 0) ? 0 : installOrder->size()-1;
  std::cout << "getTailId = " << std::get<0>(installOrder->at(normalizedArrayLength)) << "\n";
  return std::get<0>(installOrder->at(normalizedArrayLength));
}


void installOrderQueue::printQueueMetadata(manifestList* manifest)
{
  int normalizedArrayLength = (installOrder->size()-1 <= 0) ? 0 : installOrder->size()-1;
  for(int a = 0; a <= normalizedArrayLength; a++)
  {
    std::pair<int, int> idAndLevel = installOrder->at(a);
    std::cout << "id: " << std::get<0>(idAndLevel) << " Level:" << std::get<1>(idAndLevel) << "\n";
  }
}
