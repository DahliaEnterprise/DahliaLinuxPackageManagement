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
  int dependencyManifestUniqueId = manifest->getHeadDependencyAt(index);
  //Continue getting unique-id of level zero of every depth from head through tail.

}
