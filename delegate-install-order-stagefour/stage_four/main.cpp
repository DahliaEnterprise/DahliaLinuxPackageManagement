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
  installOrder* headQueue = new installOrder();
  headQueue->initalize();
  headQueue->appendId(manifest->getDependencyByHeadIndex(0)->getId(), 0);

  bool keep_generating = true;
  while(keep_generating == true)
  {
    //Went deeper? (if goes deeper we want to loop while back around to going deeper until stops)
    bool wentDeeper = false;
    dependency* tail = manifest->getDependencyById(headQueue->tailId());
    if(tail->hasPrerequisites() == true)
    {
      int totalPrerequisites = tail->totalPrerequisites();
      for(int a = 0; a < totalPrerequisites; a++)
      {
        int prerequisiteId = tail->getPrerequisiteIdByPrerquisiteListLevel(a);
        if(manifest->previouslyInstalled(prerequisiteId) == false)
        {
          if(headQueue->isIdOnQueue(prerequisiteId) == false)
          {
            wentDeeper = true;
            headQueue->appendId(prerequisiteId, a);
            a = totalPrerequisites;//stop for(a) loop
          }
        }
      }
    }

    if(wentDeeper == false)
    {
      //Max depth found
      printQueue(headQueue->printOrder(), manifest);
      //std::cout << "no more deepness\n";

      std::cout << "installing " << manifest->getDependencyById(headQueue->tailId())->getName() << "\n";
      manifest->appendVirtuallyInstalled(headQueue->tailId());
      headQueue->removeTail();
    }
  }

  //Generate to all level zeros deep
  bool keep_depthing = true;
  while(keep_depthing == true)
  {
    if(manifest->getDependencyById(headQueue->tailId())->hasPrerequisites() == true)
    {
      int prerquisiteId = manifest->getDependencyById(headQueue->tailId())->getPrerequisiteIdByPrerquisiteListLevel(0);
      if(manifest->previouslyInstalled(prerquisiteId) == false)
      {
        if(headQueue->isIdOnQueue(prerquisiteId) == false)
        {
          headQueue->appendId(prerquisiteId, 0);
        }else{ keep_depthing = false; }
      }else{ keep_depthing = false; }
    }else{ keep_depthing = false; }
  }

  //Consume
  bool keep_consuming = true;
  while(keep_consuming == true)
  {
    //Consume tail
    std::cout << " install " << manifest->getDependencyById(headQueue->tailId())->getName() << "\n";
    int tailLevel = headQueue->tailLevel();
    headQueue->removeTail();

    //Can tail go down a level?
    dependency* tailDep = manifest->getDependencyById(headQueue->tailId());
    std::cout << tailDep->totalPrerequisites()-1 << " >= " << tailLevel+1 << "\n";
    if(tailDep->totalPrerequisites()-1 >= tailLevel+1)
    {
      dependency* newTail = manifest->getDependencyById(tailDep->getPrerequisiteIdByPrerquisiteListLevel(tailLevel+1));
      std::cout << newTail->getName() << "\n";
      keep_consuming = false;
    }
  }

  printQueue(headQueue->printOrder(), manifest);

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
