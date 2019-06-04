#include "entiredependencylist.h"

entireDependencyList::entireDependencyList()
{

}

entireDependencyList::~entireDependencyList()
{

}

void entireDependencyList::initialize()
{
  manifestList = new std::vector<std::pair<int,std::string>>();
  dependencyList = new std::vector<dependency*>();
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
  std::ifstream manifestTextFile; manifestTextFile.open(fileLocation, std::ifstream::in);
  if(manifestTextFile.is_open() == true)
  {
    char dependencyName[100];
    memset(dependencyName, '\0', 100);
    manifestTextFile.getline(dependencyName, 100);
    while(strlen(dependencyName) > 0)
    {
      //
      std::cout << this->getUniqueIdByDependencyName(std::string(dependencyName));
      //Reset for next iteration of while loop
      memset(dependencyName, '\0', 100);
      manifestTextFile.getline(dependencyName, 100);
    }
  }
}

int entireDependencyList::getUniqueIdByDependencyName(std::string dependencyName)
{
  int output = -1;

  for(unsigned int a = 0; a < manifestList->size(); a++)
  {
    std::pair<int, std::string> dependencyMetadata = manifestList->at(a);
    if(std::get<1>(dependencyMetadata).compare(dependencyName) == 0)
    {
      output = std::get<0>(dependencyMetadata);
    }
  }
  return output;
}
