#ifndef INSTALLORDERQUEUE_H
#define INSTALLORDERQUEUE_H

#include <vector>
#include <utility>
#include "manifestlist.cpp"
class installOrderQueue
{
public:
  installOrderQueue();
  void initialize();
  void appendDependency(int dependencyId, int level);
  int getTailId();
  void printQueueMetadata(manifestList* manifest);

private:
  std::vector<std::pair<int, int>>* installOrder;
};

#endif // INSTALLORDERQUEUE_H
