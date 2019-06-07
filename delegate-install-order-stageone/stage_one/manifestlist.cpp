#ifndef MANIFESTLIST_CPP
#define MANIFESTLIST_CPP

#include "manifestlist.h"

manifestList::manifestList()
{

}


void manifestList::initialize(std::string setDirectoryOfDependencies, std::string setPackageHeadTextFilename)
{
  nextAvailableUniqueId = 1;
  directoryOfDependencies.append(setDirectoryOfDependencies); packageHeadTextFilename.append(setPackageHeadTextFilename); dependencies = new std::vector<dependency*>();headDependency = new std::vector<int>();dependenciesVirtuallyInstalled = new std::vector<int>();
}


void manifestList::stepone_convertManifestTextToObjects()
{
  std::string fileLocation = std::string(); fileLocation.append(directoryOfDependencies); fileLocation.append("manifest.txt");
  std::ifstream manifestTextFile; manifestTextFile.open(fileLocation, std::ifstream::in);
  if(manifestTextFile.is_open() == true)
  {
    std::string dependencyName; std::getline(manifestTextFile, dependencyName);
    while(dependencyName.empty() == false)
    {
      dependency* dep = new dependency(); dep->initialize(nextAvailableUniqueId, dependencyName);
      dependencies->push_back(dep);
      nextAvailableUniqueId += 1;
      std::cout << dep->getName() << " " << dep->getId() << "\n" ;
      //Reset for next loop iteration.
      dependencyName.clear();
      std::getline(manifestTextFile, dependencyName);
    }
  }
}

#endif
