#include "installorderqueuegenerator.h"

installOrderQueueGenerator::installOrderQueueGenerator()
{

}

void installOrderQueueGenerator::initialize(manifestList* setManifestAs){ manifest = setManifestAs; }

installOrderQueue* installOrderQueueGenerator::generateFirstQueueUsingHeadDependency(int headDependencyId)
{
  /** Notes
      The initial queue will append every dependency at level zero starting from the head dependency.
  **/
  installOrderQueue* firstQueue = new installOrderQueue();

  //Append head dependency to the zero index of the queue.
  firstQueue->appendDependency(headDependencyId, 0);
  std::cout << manifest->getDependencyUsingId(headDependencyId)->getName() << "\n";
  manifest->getDependencyUsingId(headDependencyId)->printPrerequisites();

  //Continue down the depths (of level zeros) until the end has been found.
  bool keep_depthing = true;
  while(keep_depthing == true)
  {
    //Get last queue positions' dependency id
    int tailDependencyId = firstQueue->getTailId();
    std::cout << manifest->getDependencyUsingId(tailDependencyId)->getName() << " \n ";
    //Determine if the tail dependency has prerequisites(another depth).
    dependency* tailDependency = manifest->getDependencyUsingId(tailDependencyId);
    bool hasPrerequisites = tailDependency->hasPrerequisites();
    if(hasPrerequisites == true)
    {
      //Get the zero level of prerequisites list from tail dependency.
      int prerequisiteIdFromTailZeroLevelDependency = tailDependency->getPrerequisiteIdByPrerquisiteListLevel(0);
      firstQueue->appendDependency(prerequisiteIdFromTailZeroLevelDependency, 0);
      std::cout << manifest->getDependencyUsingId(prerequisiteIdFromTailZeroLevelDependency)->getName() << " \n";
    }else if(hasPrerequisites == false){ keep_depthing = false; }
  }

  return firstQueue;
}
