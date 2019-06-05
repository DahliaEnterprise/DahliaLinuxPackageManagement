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

#endif
