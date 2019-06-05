#ifndef INSTALLORDERQUEUEGENERATOR_H
#define INSTALLORDERQUEUEGENERATOR_H

#include "entiredependencylist.cpp"

class installOrderQueueGenerator
{
public:
  installOrderQueueGenerator();

  void becomeAwareOfManifest(entireDependencyList* setManifest);
  void generateHeadInstallOrderQueue(int index);

private:
  //Out of this scope objects and variables.
  entireDependencyList* manifest;
};

#endif // INSTALLORDERQUEUEGENERATOR_H
