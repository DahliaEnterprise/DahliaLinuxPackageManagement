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
  //Get dependency of the tail of the install order queue.
  dependency* tail = manifest->getDependencyByUniqueId( previousInstallOrderQueue->dependencyUniqueIdOfTail() );
  //Determine if the tail can go down a level.
  int currentLevelOfTailIsAt = previousInstallOrderQueue->getLevelAtTailDepth();
    //Get parent dependency of tail and get total prequisites
    dependency* parentOfTail = manifest->getDependencyByUniqueId( previousInstallOrderQueue->dependencyUniqueIdOfTail() );
  int availableLevelsAtTail = parentOfTail->totalPrerequisites(); (availableLevelsAtTail-1 <= 0) ? 0 : availableLevelsAtTail-1;
  int nextProposedLevelAtTail = currentLevelOfTailIsAt += 1;
  if(nextProposedLevelAtTail < availableLevelsAtTail)
  { //Can go to next proposed level at tail.
    //Determine if this next level dependency has already been installed.
    if(this->installedDependenciesContains(tail->getUniqueId()) == false)
    {
      int uniqueIdOfNextProposedLevelAtTail = parentOfTail->getPrerequisiteUniqueId(nextProposedLevelAtTail);
      newQueue->redefineLevelOfTail(uniqueIdOfNextProposedLevelAtTail, nextProposedLevelAtTail);
    }else if(this->installedDependenciesContains(tail->getUniqueId()) == true)
    {
      //Keeping going down until last level reached or a dependency hasen't been virtually installed.

    }
  }else if(nextProposedLevelAtTail >= availableLevelsAtTail)
  {
    //If cannot go down a level remove tail, this dependency has been virtually installed.
    newQueue->removeDepthTail();
    if(this->installedDependenciesContains(tail->getUniqueId()) == false){ installedDependencies->push_back(tail->getUniqueId()); }
  }


  /*
  //Get dependency of the tail
  dependency* tailDependency = manifest->getDependencyByUniqueId(previousInstallOrderQueue->dependencyUniqueIdOfTail());

  //Get level(prerequisite index) of tail depth from previous install order queue.
  int levelOfTailFromPreviousInstallOrderQueue = previousInstallOrderQueue->getLevelAtTailDepth();

  //Determine if the next proposed level(prerequisite index) exists.
  int proposedNextLevel = levelOfTailFromPreviousInstallOrderQueue + 1;
  bool nextLevelExists = false;
  if(tailDependency->totalPrerequisites() > 0)
  {
    int zeroBasedTotalPrerequisites = (tailDependency->totalPrerequisites()-1 <= 0) ? 0 : tailDependency->totalPrerequisites()-1;
    std::cout << proposedNextLevel << " <= " << zeroBasedTotalPrerequisites << " | " << tailDependency->totalPrerequisites() << "\n";
    if(proposedNextLevel <= zeroBasedTotalPrerequisites)
    {
      nextLevelExists = true;
    }
  }
  
  //if next level exist, redefine level at that depth
  if(nextLevelExists == true)
  {
    //redefine level at this (parent of tail)depth.
    //get unique id for dependency of the next level.
    int uniqueIdOfTheNextLevel = tailDependency->getPrerequisiteUniqueId(proposedNextLevel);
    newQueue->redefineLevelOfTail(uniqueIdOfTheNextLevel, proposedNextLevel);
    std::cout << "redefined level\n";

    //check this levels dependency has prereqiqisites, if yes, continue down the deepest-depth as level zeros.
    dependency* nextLevelPrerequisite = manifest->getDependencyByUniqueId(uniqueIdOfTheNextLevel);
    if(nextLevelPrerequisite->hasPrerequisites() == true)
    {
      //Continue down proceeding depths (at zero level per depth).
      bool keep_depthing = true;
      while(keep_depthing == true)
      {
        int uniqueId = nextLevelPrerequisite->getPrerequisiteUniqueId(0);
        nextLevelPrerequisite = manifest->getDependencyByUniqueId(uniqueId);
        if(nextLevelPrerequisite->hasPrerequisites() == true)
        {
          newQueue->appendAsDepth(uniqueId, 0);
        }else{
          keep_depthing = false;
        }
      }
    }
  }else if(nextLevelExists == false)
  {
    //this is the end of this queue, since the last queue already processed the (prerequisites) of the tail, remove the tail.
    newQueue->removeDepthTail();
    //std::cout << "removed tail\n";
  }
  */

  return newQueue;
}


bool installOrderQueue::installedDependenciesContains(int uniqueId)
{
  bool output = false;
  int normalizedLengthArray = (installedDependencies->size()-1 <= 0) ? 0 : installedDependencies->size()-1;
  for(int a = 0; a <= normalizedLengthArray; a++)
  {
    if(installedDependencies->at(a) == uniqueId){ output = true; a = normalizedLengthArray+1; }
  }
  return output;
}
