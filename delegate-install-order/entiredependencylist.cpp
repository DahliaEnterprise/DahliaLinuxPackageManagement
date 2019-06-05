#ifndef ENTIREDEPENDENCYLIST_CPP
#define ENTIREDEPENDENCYLIST_CPP

#include "entiredependencylist.h"

entireDependencyList::entireDependencyList()
{

}

entireDependencyList::~entireDependencyList()
{

}

void entireDependencyList::initialize()
{
  nextAvailableManifestListDependencyId = 1;
  manifestList = new std::vector<std::pair<int,std::string>>();
  dependencyList = new std::vector<dependency*>();
  headDependencyList = new std::vector<int>();
}


void entireDependencyList::forEveryLineInManifest_thenAppendToArrayWithUniqueId(std::string fileLocation)
{
  std::ifstream manifestTextFile; manifestTextFile.open(fileLocation, std::ifstream::in);
  if(manifestTextFile.is_open() == true)
  {
    char dependencyName[100];
    memset(dependencyName, '\0', 100);
    manifestTextFile.getline(dependencyName, 100);
    while(strlen(dependencyName) > 0)
    {
      //Append dependency name from text file to this object.
      std::string dependencyNameString = std::string(dependencyName);
      int dependencyId = this->getNextAvailableManifestListDependencyId();
      std::pair<int, std::string> dependencyMetadata(dependencyId, dependencyNameString);
      manifestList->push_back(dependencyMetadata);
      this->createDependencyObject(dependencyId, dependencyNameString);

      //Reset for next iteration of while loop
      memset(dependencyName, '\0', 100);
      manifestTextFile.getline(dependencyName, 100);
    }
  }else{ std::cout << "failed to manifestTextFileLocation()\n"; }
}

void entireDependencyList::createDependencyObject(int dependencyId, std::string dependencyName)
{
  //create dependency object, assigning id and name.
  dependency* newDep = new dependency();
  newDep->initialize();
  newDep->setId(dependencyId);
  newDep->setName(dependencyName);

  //append to dependencyList
  dependencyList->push_back(newDep);
}


int entireDependencyList::getNextAvailableManifestListDependencyId()
{
  int output = -1;
  output = nextAvailableManifestListDependencyId;
  nextAvailableManifestListDependencyId += 1;
  return output;
}


void entireDependencyList::determineAndFlagHeadDependencies(std::string fileLocation)
{
  std::ifstream headDependencyListTextFile; headDependencyListTextFile.open(fileLocation, std::ifstream::in);
  if(headDependencyListTextFile.is_open() == true)
  {
    char dependencyName[100];
    memset(dependencyName, '\0', 100);
    headDependencyListTextFile.getline(dependencyName, 100);
    while(strlen(dependencyName) > 0)
    {
      int uniqueId_ofDependencyNameInHead = this->getUniqueIdByDependencyName(std::string(dependencyName));
      headDependencyList->push_back(uniqueId_ofDependencyNameInHead);

      //Reset for next iteration of while loop
      memset(dependencyName, '\0', 100);
      headDependencyListTextFile.getline(dependencyName, 100);
    }
  }
}

int entireDependencyList::getUniqueIdByDependencyName(std::string dependencyName)
{
  int output = -1;

  for(size_t a = 0; a < manifestList->size(); a++)
  {
    std::pair<int, std::string> dependencyMetadata = manifestList->at(a);
    std::string suspectDependencyName = std::get<1>(dependencyMetadata);
    if(suspectDependencyName.compare(dependencyName) == 0)
    {
      output = std::get<0>(dependencyMetadata);
      a = manifestList->size();
    }
  }
  return output;
}

int entireDependencyList::getHeadDependencyAt(int index)
{
  int output = -1;
  int headDependencyUniqueId = -1;

  int normalizedHeadDependencyListLength = this->normalizedArrayLength(headDependencyList->size());
  if(index <= normalizedHeadDependencyListLength)//index out of range prevention
  {
    headDependencyUniqueId = headDependencyList->at(index);
  }
  output = headDependencyUniqueId;
  return output;
}

dependency* entireDependencyList::getDependencyByUniqueId(int uniqueId)
{
  dependency* output = nullptr;
  int normalizedDependencyLength = normalizedArrayLength(dependencyList->size());
  for(int a = 0; a < normalizedDependencyLength; a++)
  {
    dependency* suspectDependency = dependencyList->at(a);
    if(suspectDependency->getUniqueId() == uniqueId)
    {
      output = suspectDependency;
    }
  }
  return output;
}

int entireDependencyList::normalizedArrayLength(int length)
{
  int output = -1;
  int normalizedLength = -1;
  normalizedLength = (length-1 == 0) ? 1 : length-1;
  output = normalizedLength;
  return output;
}

void entireDependencyList::assignPrerequisites(std::string directoryOfPackageInformation)
{
  int normalizedManifestLength = this->normalizedArrayLength(manifestList->size());
  for(int a = 0; a < normalizedManifestLength; a++)
  {
    int dependencyId = std::get<0>(manifestList->at(a));
    std::string dependencyName = std::get<1>(manifestList->at(a));

    //Open dependency' text file containing its prerequisites
    std::string nameAndLocationOfPrerequisiteList = std::string(directoryOfPackageInformation);
    nameAndLocationOfPrerequisiteList.append(dependencyName);
    nameAndLocationOfPrerequisiteList.append(".txt");

    std::ifstream prerequisiteListTextFile; prerequisiteListTextFile.open(nameAndLocationOfPrerequisiteList, std::ifstream::in);
    if(prerequisiteListTextFile.is_open() == true)
    {
      char prerequisiteName[100];
      memset(prerequisiteName, '\0', 100);
      prerequisiteListTextFile.getline(prerequisiteName, 100);
      while(strlen(prerequisiteName) > 0)
      {
        //Get the prequisites (manifestList) unique id and append it to the respective dependency object.
        std::string prerequisiteNameAsString = std::string(prerequisiteName);
        int prerequisiteUniqueId = this->getUniqueIdByDependencyName(prerequisiteNameAsString);
        dependency* parentDependency = this->getDependencyByUniqueId(dependencyId);
        parentDependency->appendPrerequisite(prerequisiteUniqueId);

        //Reset for next iteration of while loop
        memset(prerequisiteName, '\0', 100);
        prerequisiteListTextFile.getline(prerequisiteName, 100);
      }
    }
  }
}

#endif
