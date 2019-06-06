#ifndef INSTALLORDERQUEUE_H
#define INSTALLORDERQUEUE_H

#include <vector>
#include <utility>
#include "entiredependencylist.cpp"
#include "dependency.cpp"
class installOrderQueue
{
public:
  installOrderQueue();
  void initialize();

  void appendAsDepth(int dependencyUniqueId, int zeroBasedLevel);
  int dependencyUniqueIdOfTail();
  int getLevelAtTailDepth();
  std::vector<std::pair<int, int>>* getInstallOrder();
  void redefineLevelOfTail(int uniqueIdToSetAs, int levelToSetAs);
  void removeDepthTail();

  void printInstallOrderQueue(entireDependencyList* manifest);

private:
  std::vector<std::pair<int, int>>* installOrder;
};

#endif // INSTALLORDERQUEUE_H
