#include "manifestlist.h"

manifestList::manifestList()
{

}


void manifestList::initialize(std::string setDirectoryOfDependencies, std::string setPackageHeadTextFilename)
{
  nextAvailableUniqueId = 1;
  directoryOfDependencies.append(setDirectoryOfDependencies);
  packageHeadTextFilename.append(setPackageHeadTextFilename);
  dependencies = new std::vector<dependency*>();
}


void manifestList::stepone_convertManifestTextToObjects()
{
  std::string fileLocation = std::string(); fileLocation.append(directoryOfDependencies); fileLocation.append(packageHeadTextFilename); fileLocation.append(".txt");
  std::ifstream manifestTextFile; manifestTextFile.open(fileLocation, std::ifstream::in);
  if(manifestTextFile.is_open() == true)
  {
    std::string dependencyName;
    std::getline(manifestTextFile, dependencyName);
    while(dependencyName.empty() == false)
    {
      dependency* dep = new dependency();
      dep->initialize(nextAvailableUniqueId, dependencyName);
      nextAvailableUniqueId += 1;
      dependencies->push_back(dep);

      //Reset for next loop iteration.
      dependencyName.clear();
      std::getline(manifestTextFile, dependencyName);
    }
  }
}

void manifestList::steptwo_convertPrerequisitesTextToRespectiveObjects()
{
  int normalizedArrayLenth = (dependencies->size()-1 <= 0) ? 0 : dependencies->size()-1;
  for(int a = 0; a < normalizedArrayLenth; a++)
  {
    dependency* dep = dependencies->at(a);
    std::cout << dep->getName() << "\n";
    std::string fileLocation = std::string(); fileLocation.append(directoryOfDependencies); fileLocation.append(dep->getName()); fileLocation.append(".txt");
    std::ifstream dependencysPrerequisitesTextFile; dependencysPrerequisitesTextFile.open(fileLocation, std::ifstream::in);
    if(dependencysPrerequisitesTextFile.is_open() == true)
    {
      std::string prerequisiteDependencyName;
      std::getline(dependencysPrerequisitesTextFile, prerequisiteDependencyName);
      while(prerequisiteDependencyName.empty() == false)
      {
        dependency* prerequisite = this->getDependencyUsingName(prerequisiteDependencyName);
        if(prerequisite != nullptr)
        {
          int id = prerequisite->getId();
          dep->appendPrerequisite(id);
          std::cout << " " << prerequisite->getName() << "\n";
        }

        //Reset for next loop iteration.
        prerequisiteDependencyName.clear();
        std::getline(dependencysPrerequisitesTextFile, prerequisiteDependencyName);
      }
    }
  }
}


dependency* manifestList::getDependencyUsingName(std::string dependencyName)
{
  dependency* output = nullptr;
  int normalizedArrayLenth = (dependencies->size()-1 <= 0) ? 0 : dependencies->size()-1;
  for(int a = 0; a <= normalizedArrayLenth; a++)
  {
    dependency* dep = dependencies->at(a);
    if(dep->getName().compare(dependencyName) == 0)
    {
      output = dep;
      a = normalizedArrayLenth+1;
    }
  }


  return output;
}
