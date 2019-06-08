#include <iostream>
#include "installorder.cpp"
#include "manifestlist.cpp"

void printQueue(std::vector<int> idInOrder, manifestList* manifest);

int main(int argc, char *argv[])
{
  /** Load Dependency and Prereuqisite Information into Program **/
  manifestList* manifest = new manifestList();
  manifest->initialize(std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/"), std::string("BuildEssential_amd64"));
  manifest->stepone_convertManifestTextToObjects();
  manifest->steptwo_linkPrerequisitesToTheirRespectiveDependencies();
  manifest->stepthree_determineHeadDependencies();

  /** Begin Generation **/
  //Create initial deepest depth all zero level prerequisites.
  installOrder* headQueue = new installOrder(); headQueue->initalize();
  headQueue->appendId(manifest->getDependencyByHeadIndex(0)->getId(), 0);

  //BEGIN WHILE LOOP HERE
  std::vector<installOrder*>* installorderqueue_history = new std::vector<installOrder*>();
  installorderqueue_history->push_back(headQueue);

  int loopLimit = 10;
  int a = 0;
  while(a < loopLimit)
  {
    installOrder* currentQueue = installorderqueue_history->at(installorderqueue_history->size()-1);

    //Has tail been installed?
    if(manifest->previouslyInstalled(currentQueue->tailId()) == false)
    {
      //Does tail have a prerequisite it can go to a deeper depth to?
      int tailTotalPrerquisites = manifest->getDependencyById(currentQueue->tailId())->totalPrerequisites();
      bool tailHasDeeperDepth = false;
      int tailPrerequisiteId = -1;
      int index = -1;
      for(int b = 0; b < tailTotalPrerquisites; b++)
      {
        tailPrerequisiteId = manifest->getDependencyById(currentQueue->tailId())->getPrerequisiteIdByPrerquisiteListLevel(b);
        //Has this been installed?
        if(manifest->previouslyInstalled(tailPrerequisiteId) == false)
        {
          //Is it on the current queue?
          if(currentQueue->isIdOnQueue(tailPrerequisiteId) == false)
          {
            tailHasDeeperDepth = true; b = tailTotalPrerquisites;
          }
        }
      }

      if(tailHasDeeperDepth == true)
      {
        currentQueue->appendId(tailPrerequisiteId  ,index);
      }else{
        //Deepest tail for this queue.
        std::cout << "recommend install :" << manifest->getDependencyById(currentQueue->tailId())->getName() << "\n";
        manifest->appendVirtuallyInstalled(currentQueue->tailId());
        currentQueue->removeTail();
      }
    }
    printQueue(currentQueue->printOrder(), manifest);

    //Commit current queue by appending a copy for the next while loop around
    installOrder* newQueue = new installOrder(); newQueue->initalize();
    for(int b = 0; b < currentQueue->totalDepths(); b++)
    {
      std::pair<int, int> idAndLevel = currentQueue->idAndLevelAtDepth(b);
      newQueue->appendId(std::get<0>(idAndLevel), std::get<1>(idAndLevel));
    }
    installorderqueue_history->push_back(newQueue);


    // print status //
    std::vector<int> queue = currentQueue->printOrder();
    for(size_t b = 0; b < queue.size(); b++)
    {
      //std::cout << manifest->getDependencyById(queue.at(b))->getName() << " => ";
    }
    //std::cout << "\n";

    //temp loop limit
    a++;
  }


  /** Print Queues **/
  for(size_t a = 0; a < installorderqueue_history->size(); a++)
  {
    installOrder* orderToPrint = installorderqueue_history->at(a);
    std::vector<int> queue = orderToPrint->printOrder();
    for(size_t b = 0; b < queue.size(); b++)
    {
      //std::cout << manifest->getDependencyById(queue.at(b))->getName() << " => ";
    }
    //std::cout << "\n";
  }

  //Can the tail go down a level of prerequisites


  //END WHILE LOOP HERE

    //Can the parent of the tail go down a level?

  return 0;
}

void printQueue(std::vector<int> idInOrder, manifestList* manifest)
{
    for(size_t b = 0; b < idInOrder.size(); b++)
    {
      std::cout << manifest->getDependencyById(idInOrder.at(b))->getName() << " => ";
    }
    std::cout << "\n";
}
