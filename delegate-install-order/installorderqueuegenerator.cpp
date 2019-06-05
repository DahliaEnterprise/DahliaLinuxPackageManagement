#include "installorderqueuegenerator.h"

installOrderQueueGenerator::installOrderQueueGenerator()
{

}


void installOrderQueueGenerator::becomeAwareOfManifest(entireDependencyList* setManifest)
{
  manifest = setManifest;
}


void installOrderQueueGenerator::generateHeadInstallOrderQueue(int index)
{
  //Get Head Dependency Unique Id
  int headDependencyManifestUniqueId = manifest->getHeadDependencyAt(index);

  //Continue getting unique-id of level zero of every depth from head through tail.
  int lastDependencyUniqueId = headDependencyManifestUniqueId;
  int currentDepth = 0;
  bool keep_depthing = true;
  while(keep_depthing == true)
  {
    //With current dependency, get its zero-level prerequisite' unique id
    //dependency* lastDependency = manifest->getDependencyByUniqueId(lastDependencyUniqueId);
    keep_depthing = false;
  }
}
