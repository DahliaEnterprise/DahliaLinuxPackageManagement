#ifndef INSTALLORDERQUEUEGENERATOR_H
#define INSTALLORDERQUEUEGENERATOR_H

#include "manifestlist.cpp"
#include "installorderqueue.cpp"

class installOrderQueueGenerator
{
public:
  installOrderQueueGenerator();
  void initialize(manifestList* setManifestAs);

  installOrderQueue* generateFirstQueueUsingHeadDependency(int headDependencyId);

private:

  //Out of scope variables
  manifestList* manifest;
};

#endif // INSTALLORDERQUEUEGENERATOR_H
