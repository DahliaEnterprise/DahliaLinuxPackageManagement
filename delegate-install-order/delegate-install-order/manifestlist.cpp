#ifndef MANIFESTLIST_CPP
#define MANIFESTLIST_CPP

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
  headDependency = new std::vector<int>();
  dependenciesVirtuallyInstalled = new std::vector<int>();
}


void manifestList::stepone_convertManifestTextToObjects()
{
  std::string fileLocation = std::string(); fileLocation.append(directoryOfDependencies); fileLocation.append("manifest.txt");
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
      std::cout << dep->getName() << "\n" ;
      //Reset for next loop iteration.
      dependencyName.clear();
      std::getline(manifestTextFile, dependencyName);
    }
  }
}

void manifestList::steptwo_convertPrerequisitesTextToRespectiveObjects()
{
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* dep = dependencies->at(a);
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
        }else{ std::cout << prerequisiteDependencyName << " not found, required by " << dep->getName() << "\n"; }

        //Reset for next loop iteration.
        prerequisiteDependencyName.clear();
        std::getline(dependencysPrerequisitesTextFile, prerequisiteDependencyName);
      }
    }
  }
}

void manifestList::stepthree_determineHeadDependencies()
{
  std::string fileLocation = std::string(); fileLocation.append(directoryOfDependencies); fileLocation.append(packageHeadTextFilename); fileLocation.append(".txt");
  std::ifstream headDependencyTextFile; headDependencyTextFile.open(fileLocation, std::ifstream::in);
  if(headDependencyTextFile.is_open() == true)
  {
    std::string dependencyName;
    std::getline(headDependencyTextFile, dependencyName);
    while(dependencyName.empty() == false)
    {
        dependency* dep = this->getDependencyUsingName(dependencyName);
        headDependency->push_back(dep->getId());

        //Reset for next loop iteration.
        dependencyName.clear();
        std::getline(headDependencyTextFile, dependencyName);
    }
  }
}


int  manifestList::getHeadDependencyIdByIndex(int index){ return headDependency->at(index); }

bool manifestList::isDependencyInstalled(int dependencyId)
{
  bool output = false;

  int normalizedArrayLength = (dependenciesVirtuallyInstalled->size()-1 <= 0) ? 0 : dependenciesVirtuallyInstalled->size()-1;
  for(int a = 0; a <= normalizedArrayLength; a++)
  {
    int dependencyIdInstalled = dependenciesVirtuallyInstalled->at(a);
    if(dependencyIdInstalled == dependencyId)
    {
      output = true;
      a = normalizedArrayLength + 1;
    }
  }

  return output;
}



dependency* manifestList::getDependencyUsingName(std::string dependencyName)
{
  dependency* output = nullptr;
  bool matches = true;
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* dep = dependencies->at(a);
    std::string suspectDependencyName = dep->getName();

    if(suspectDependencyName.size() == dependencyName.size())
    { //Same length, check characters match.
      for(size_t b = 0; b < dependencyName.size(); b++)
      {
        if(suspectDependencyName.at(b) != dependencyName.at(b))
        {//string does not match
         std::cout << "---\n";
         std::cout << suspectDependencyName.at(b) << " " << dependencyName.at(b) << "\n";
         std::cout << suspectDependencyName << " " << dependencyName << "\n";
          matches = false;
          output = dependencies->at(a);
          b = dependencyName.size();
        }
      }
    }

  }

  if(matches == false)
  {
    //std::cout << "match was not found for comparison "  << dependencyName << "\n";
  }

  return output;
}


dependency* manifestList::getDependencyUsingId(int uniqueId)
{
  dependency* output = nullptr;
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* dep = dependencies->at(a);
    if(dep->getId() == uniqueId)
    {
      output = dep;
      a = dependencies->size();
    }
  }

  return output;
}
#endif
