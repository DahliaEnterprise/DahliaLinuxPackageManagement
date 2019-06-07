#ifndef MANIFESTLIST_CPP
#define MANIFESTLIST_CPP

#include "manifestlist.h"

manifestList::manifestList()
{

}


void manifestList::initialize(std::string setDirectoryOfDependencies, std::string setPackageHeadTextFilename)
{
  nextAvailableUniqueId = 1;
  directoryOfDependencies.append(setDirectoryOfDependencies); packageHeadTextFilename.append(setPackageHeadTextFilename); dependencies = new std::vector<dependency*>();
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

      //Reset for next loop iteration.
      dependencyName.clear();
      std::getline(manifestTextFile, dependencyName);
    }
  }
}

void manifestList::steptwo_linkPrerequisitesToTheirRespectiveDependencies()
{
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* dep = dependencies->at(a);
    std::cout << dep->getName() << "\n";
    textFile* text = new textFile();
    std::string directoryAndFilename = std::string();
    directoryAndFilename.append(directoryOfDependencies);
    directoryAndFilename.append(dep->getName());
    directoryAndFilename.append(".txt");
    text->openTextFile(directoryAndFilename);
    bool keep_looping = true;
    while(keep_looping == true)
    {
      std::pair<std::string, bool> nextLinePair = text->getNextLine();
      (void)(std::get<1>(nextLinePair) == true ? keep_looping = false : false);
      std::string nextLine = std::get<0>(nextLinePair);
      dependency* nextPrerequisite = this->getDependencyObjectByName(nextLine);
      if(nextPrerequisite != nullptr)
      {
        dep->appendPrerequisite(nextPrerequisite->getId());
      }else if(nextPrerequisite == nullptr){ std::cout << "prerequisite " << nextLine << " not found during search(by name) as required by " << dep->getName() << "\n"; }
    }
    delete text;
  }
}

dependency* manifestList::getDependencyObjectByName(std::string dependencyName)
{
  dependency* output = nullptr;
  size_t index = 0; bool dependencyFound = false;
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* suspectDependency = dependencies->at(a);
    if(this->stringMatches(suspectDependency->getName(), dependencyName, suspectDependency->getName().size()) == true)
    {
      output = suspectDependency;
      index = a;
      dependencyFound = true;
      a = dependencies->size();
    }
  }

  if(dependencyFound == true)
  {
    output = dependencies->at(index);
  }
  return output;
}

bool manifestList::stringMatches(std::string string1, std::string string2, size_t finiteLimit)
{
  bool output = false;

  char* string1Char = (char*)malloc(2 * sizeof(char)); memset(string1Char, '\0', 2);
  char* string2Char = (char*)malloc(2 * sizeof(char)); memset(string2Char, '\0', 2);
  bool matches = true;
  bool keep_matching = true;
  size_t charactersConsumed = 0;
  while(keep_matching == true)
  {
    if(charactersConsumed < string1.size() && charactersConsumed < string2.size())
    {

      if(charactersConsumed < finiteLimit)
      {
        string1Char[0] = string1.at(charactersConsumed);
        string2Char[0] = string2.at(charactersConsumed);
        if(strncmp(string1Char, string2Char, 1) != 0)
        {
          matches = false;
          keep_matching = false;
        }
      }
    }else{ keep_matching = false; }

    charactersConsumed += 1;
    if(charactersConsumed >= finiteLimit)
    {
      keep_matching = false;
    }

  }
  free(string1Char); free(string2Char);
  output = matches;
  return output;
}

#endif
