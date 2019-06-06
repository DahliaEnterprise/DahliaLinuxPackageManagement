#ifndef INSTALLORDERQUEUEGENERATOR_H
#define INSTALLORDERQUEUEGENERATOR_H

#include <vector>
#include "installorderqueue.cpp"
#include "entiredependencylist.cpp"

class installOrderQueueGenerator
{
public:
  installOrderQueueGenerator();

  void becomeAwareOfVirtuallyInstalledDependencies(std::vector<int>* setInstalledDependencies);
  void becomeAwareOfManifest(entireDependencyList* setManifest);
  installOrderQueue* generateHeadInstallOrderQueue(int index);
  installOrderQueue* generateNextQueue(installOrderQueue* previousInstallOrderQueue);

  bool installedDependenciesContains(int uniqueId);

private:
  //Out of this scope objects and variables.
  entireDependencyList* manifest;
  std::vector<int>* installedDependencies;
};

#endif // INSTALLORDERQUEUEGENERATOR_H
