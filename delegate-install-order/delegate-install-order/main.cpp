#include <iostream>
#include "installorderqueuegenerator.cpp"
#include "manifestlist.cpp"
int main(int argc, char *argv[])
{
  /** Load Dependency and Prereuqisite Information into Program **/
  manifestList* manifest = new manifestList();
  manifest->initialize(std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/"), std::string("BuildEssential_amd64"));
  manifest->stepone_convertManifestTextToObjects();
  manifest->steptwo_convertPrerequisitesTextToRespectiveObjects();
  //manifest->stepthree_determineHeadDependencies();

  /** Begin Generation **/
  //Initialize first generation queue with the first head.
  //installOrderQueueGenerator* generator = new installOrderQueueGenerator();
  //generator->initialize(manifest);
  //installOrderQueue* orderQueue = generator->generateFirstQueueUsingHeadDependency(manifest->getHeadDependencyIdByIndex(0));
  //orderQueue->printQueueMetadata(manifest);

  return 0;
}
