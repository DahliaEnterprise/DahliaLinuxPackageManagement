#include "installorderqueuegenerator.h"

installOrderQueueGenerator::installOrderQueueGenerator()
{

}

void installOrderQueueGenerator::becomeAwareOfVirtuallyInstalledDependencies(std::vector<int>* setInstalledDependencies)
{
  installedDependencies = setInstalledDependencies;
}

void installOrderQueueGenerator::becomeAwareOfManifest(entireDependencyList* setManifest)
{
  manifest = setManifest;
}


installOrderQueue* installOrderQueueGenerator::generateHeadInstallOrderQueue(int index)
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

  return newInstallOrderQueue;
}

installOrderQueue* installOrderQueueGenerator::generateNextQueue(installOrderQueue* previousInstallOrderQueue)
{
  //New Install Order Queue
  installOrderQueue* newQueue = new installOrderQueue();
  newQueue->initialize();

  //Copy previousInstallOrderQueue data to new queue.
  std::vector<std::pair<int, int>>* previousInstallOrderQueueMetadata = previousInstallOrderQueue->getInstallOrder();
  int normalizedArrayLength = (previousInstallOrderQueueMetadata->size()-1 <= 0) ? 0 : previousInstallOrderQueueMetadata->size()-1;
  for(int a = 0; a <= normalizedArrayLength; a++){ std::pair<int, int> metadata = previousInstallOrderQueueMetadata->at(a); newQueue->appendAsDepth(std::get<0>(metadata), std::get<1>(metadata)); }

  // // Begin Generation // //
  bool tailRedefined = false;
  //Get dependency of the tail of the install order queue.
  dependency* tail = manifest->getDependencyByUniqueId( previousInstallOrderQueue->dependencyUniqueIdOfTail() );
  //Determine if the tail can go down a level.
  int currentLevelOfTailIsAt = previousInstallOrderQueue->getLevelAtTailDepth();
    //Get parent dependency of tail and get total prequisites
    dependency* parentOfTail = manifest->getDependencyByUniqueId( previousInstallOrderQueue->dependencyUniqueIdOfTail() );
  int availableLevelsAtTail = parentOfTail->totalPrerequisites(); availableLevelsAtTail = (availableLevelsAtTail-1 <= 0) ? 0 : availableLevelsAtTail-1;
  int nextProposedLevelAtTail = currentLevelOfTailIsAt += 1;
  if(nextProposedLevelAtTail < availableLevelsAtTail)
  { //Can go to next proposed level at tail.
    int uniqueIdOfNextProposedLevelAtTail = parentOfTail->getPrerequisiteUniqueId(nextProposedLevelAtTail);
    //Determine if this next level dependency has already been installed.
    if(this->installedDependenciesContains(uniqueIdOfNextProposedLevelAtTail) == false)
    {
      newQueue->redefineLevelOfTail(uniqueIdOfNextProposedLevelAtTail, nextProposedLevelAtTail);
      tailRedefined = true;
    }else if(this->installedDependenciesContains(uniqueIdOfNextProposedLevelAtTail) == true)
    {
      //Keeping going down until last level reached or a dependency hasen't been virtually installed.
      bool keep_leveling = true;
      while(keep_leveling == true)
      {
        std::cout << nextProposedLevelAtTail << " " << availableLevelsAtTail << "\n";
        nextProposedLevelAtTail += 1;
        if(nextProposedLevelAtTail < availableLevelsAtTail)
        { //Can go to next proposed level at tail.
          //Determine if this next level dependency has already been installed.
          int uniqueIdOfNextProposedLevelAtTail = parentOfTail->getPrerequisiteUniqueId(nextProposedLevelAtTail);
          if(this->installedDependenciesContains(uniqueIdOfNextProposedLevelAtTail) == false)
          {
            newQueue->redefineLevelOfTail(uniqueIdOfNextProposedLevelAtTail, nextProposedLevelAtTail);
            tailRedefined = true;
            keep_leveling = false;
          }
        }else if(nextProposedLevelAtTail >= availableLevelsAtTail)
        {
          //If cannot go down a level remove tail, this dependency has been virtually installed.
          newQueue->removeDepthTail();
          if(this->installedDependenciesContains(uniqueIdOfNextProposedLevelAtTail) == false){ installedDependencies->push_back(uniqueIdOfNextProposedLevelAtTail); }
          //make new tail go down a level
          keep_leveling = false;
        }
      }
    }
  }else if(nextProposedLevelAtTail >= availableLevelsAtTail)
  {
    //If cannot go down a level remove tail, this dependency has been virtually installed.
    newQueue->removeDepthTail();
    if(this->installedDependenciesContains(tail->getUniqueId()) == false){ installedDependencies->push_back(tail->getUniqueId()); }
  }

  if(tailRedefined == true)
  {
    //Continue depthing (over zero levels) until (the new) tail or an already virtually installed dependency has been found.
    bool keep_depthing = true;
    while(keep_depthing == true)
    {
       tail = manifest->getDependencyByUniqueId( newQueue->dependencyUniqueIdOfTail() );
       if(tail->totalPrerequisites() > 0)
       {
          int tailsZeroLevelPrerequisiteUniqueId = tail->getPrerequisiteUniqueId(0);
          //Determine if this dependency has been virtually installed.
          if(this->installedDependenciesContains(tailsZeroLevelPrerequisiteUniqueId) == false)
          {
            installedDependencies->push_back(tailsZeroLevelPrerequisiteUniqueId);
            newQueue->appendAsDepth(tailsZeroLevelPrerequisiteUniqueId, 0);
          }else if(this->installedDependenciesContains(tailsZeroLevelPrerequisiteUniqueId) == true)
          {
            //Dependency virtually installed, this is the tail, no more depths to traverse.
            keep_depthing = false;
          }
       }else if(tail->totalPrerequisites() == 0)
       {
          //Tail has no prerequisites, no depth to traverse
          keep_depthing = false;
       }
    }

  }

  return newQueue;
}


bool installOrderQueueGenerator::installedDependenciesContains(int uniqueId)
{
  bool output = false;
  int normalizedLengthArray = (installedDependencies->size()-1 <= 0) ? 0 : installedDependencies->size()-1;
  for(int a = 0; a <= normalizedLengthArray; a++)
  {
    if(installedDependencies->at(a) == uniqueId){ output = true; a = normalizedLengthArray+1; }
  }
  return output;
}
