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
  //New Install Order Queue
  installOrderQueue* newInstallOrderQueue = new installOrderQueue();
  newInstallOrderQueue->initialize();

  //Get Head Dependency Unique Id
  int headDependencyManifestUniqueId = manifest->getHeadDependencyAt(index);

  //Append to install order queue
  newInstallOrderQueue->appendAsDepth(headDependencyManifestUniqueId, 0);

  //Continue getting unique-id of level zero of every depth from head through tail.
  int lastDependencyUniqueId = headDependencyManifestUniqueId;
  dependency* lastDependency = manifest->getDependencyByUniqueId(lastDependencyUniqueId);
  bool keep_depthing = true;
  while(keep_depthing == true)
  {
    //With current dependency, get its zero-level prerequisite' unique id
    if(lastDependency->hasPrerequisites() == true)
    {
      //Get zero level prerequisite at this depth(dependency).
      int prerequisiteUniqueId = lastDependency->getPrerequisiteUniqueId(0);

      //Append to install order queue
      newInstallOrderQueue->appendAsDepth(prerequisiteUniqueId, 0);

      //prepare for next loop
      lastDependencyUniqueId = prerequisiteUniqueId;
      lastDependency = manifest->getDependencyByUniqueId(prerequisiteUniqueId);
    }else if(lastDependency->hasPrerequisites() == false)
    {
      keep_depthing = false;
    }
  }
}
