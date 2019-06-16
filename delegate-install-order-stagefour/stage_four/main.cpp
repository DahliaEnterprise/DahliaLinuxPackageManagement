#include <iostream>
#include "installorder.cpp"
#include "manifestlist.cpp"

void printQueue(std::vector<int> idInOrder, manifestList* manifest);

int main(int argc, char *argv[])
{
  /** Load Dependency and Prereuqisite Information into Program **/
  manifestList* manifest = new manifestList();
  manifest->initialize(std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/OpenGL/amd64/"), std::string("OpenGL_amd64"));
  manifest->stepone_convertManifestTextToObjects();
  manifest->steptwo_linkPrerequisitesToTheirRespectiveDependencies();
  manifest->stepthree_determineHeadDependencies();
  manifest->stepfour_determineDownloadFilenames();

  /** Begin Generation **/
  std::string installationOrder = "";
  std::vector<int>* installationOrderById = new std::vector<int>();
  installOrder* headQueue = new installOrder();
  headQueue->initalize();
  headQueue->appendId(manifest->getDependencyByHeadIndex(2)->getId(), 0);
  std::cout << "HEADER:" << manifest->getDependencyById(manifest->getDependencyByHeadIndex(1)->getId())->getName() << "\n";
 //std::cout << manifest->getDependencyById(headQueue->tailId())->getName() << "\n";
  bool keep_generating = true;
  int iterations = 0;
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
        iterations += 1;
      }
    }

    if(wentDeeper == false)
    {
      //Max depth found
      std::cout << manifest->getDependencyById(headQueue->tailId())->getName() << "\n";
      //printQueue(headQueue->printOrder(), manifest);
      installationOrder.append(manifest->getDependencyById(headQueue->tailId())->getName());
      installationOrder.append("\n");
      if(manifest->previouslyInstalled(headQueue->tailId()) == false)
      {
        installationOrderById->push_back(headQueue->tailId());
      }
      manifest->appendVirtuallyInstalled(headQueue->tailId());
      headQueue->removeTail();
      if(headQueue->totalDepths() <= 0)
      {
        keep_generating = false;
      }
    }
    iterations += 1;
  }
  std::cout << iterations << "\n";
  //std::cout << manifest->getDependencyById(headQueue->tailId())->getName() << "\n";
  //std::cout << "\n\n" << installationOrder << "\n\n";
  std::cout << "apt-get install ";
  for(size_t a = 0; a < installationOrderById->size(); a++)
  {
    std::cout << "" << manifest->getDependencyById(installationOrderById->at(a))->getName() << " ";
  }
  std::cout << "\n\n";
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
