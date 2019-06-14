#ifndef MANIFESTLIST_CPP
#define MANIFESTLIST_CPP

#include "manifestlist.h"

manifestList::manifestList()
{

}


void manifestList::initialize(std::string setDirectoryOfDependencies, std::string setPackageHeadTextFilename)
{
  nextAvailableUniqueId = 1;
  directoryOfDependencies.append(setDirectoryOfDependencies); packageHeadTextFilename.append(setPackageHeadTextFilename); dependencies = new std::vector<dependency*>(); headDependencyIds = new std::vector<int>(); previouslyVirtuallyInstalled = new std::vector<int>();
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
      //std::cout << dependencyName << "\n";
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
    //std::cout << "Dependency " << dep->getName() << "\n";
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
      std::string nextLine = std::get<0>(nextLinePair);
      //std::cout << "  " << nextLine << "\n";
      bool endOfLine = std::get<1>(nextLinePair);
      if(nextLine.size() > 0)//Has another prerequisite?
      {
        dependency* nextPrerequisite = this->getDependencyObjectByName(nextLine);
        if(nextPrerequisite != nullptr)
        {
          //std::cout << "              " << nextPrerequisite->getName() << "\n";
          dep->appendPrerequisite(nextPrerequisite->getId());
        }else if(nextPrerequisite == nullptr){ std::cout << "prerequisite " << nextLine << " not found during search(by name) as required by " << dep->getName() << "\n"; }
      }
      if(endOfLine == true){ keep_looping = false; }
    }
    delete text;
  }
}

void manifestList::stepthree_determineHeadDependencies()
{
  textFile* text = new textFile();
  std::string directoryAndFilename = std::string();
  directoryAndFilename.append(directoryOfDependencies);
  directoryAndFilename.append("BuildEssential_amd64.txt");
  text->openTextFile(directoryAndFilename);
  bool keep_looping = true;
  while(keep_looping == true)
  {
    std::pair<std::string, bool> nextLinePair = text->getNextLine();
    std::string nextLine = std::get<0>(nextLinePair);
    bool endOfLine = std::get<1>(nextLinePair);
    if(nextLine.size() > 0)
    {
      dependency* nextHeadDependency = this->getDependencyObjectByName(nextLine);
      headDependencyIds->push_back(nextHeadDependency->getId());
    }
    if(endOfLine == true){ keep_looping = false; }
  }
  delete text;
}

void manifestList::stepfour_determineDownloadFilenames()
{
  std::string downloadSourceDirectory = std::string();
  downloadSourceDirectory.append(directoryOfDependencies);
  downloadSourceDirectory.append(std::string("DownloadSource/"));
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* dep = dependencies->at(a);
    std::string dependencyDownloadFilename = std::string();
    std::string downloadSourceTextFileLocation = std::string();
    downloadSourceTextFileLocation.append(downloadSourceDirectory);
    downloadSourceTextFileLocation.append(dep->getName());
    downloadSourceTextFileLocation.append(std::string(".downloadsource.txt"));
    textFile* text = new textFile();
    text->openTextFile(downloadSourceTextFileLocation);
    std::pair<std::string, bool> nextLinePair = text->getNextLine();
    std::string nextLine = std::get<0>(nextLinePair);
    if(nextLine.size() > 0)
    {
      int filenameStartsAtIndex = -1;
      for(int a = nextLine.size()-1; a > 0; a--)
      {
        char c = nextLine.at(a);
        std::string character = std::string();character.append(1, c);
        if(character.compare("/") == 0)
        {
          filenameStartsAtIndex = a;
          a = 0;
        }
      }

      if(filenameStartsAtIndex > 0)
      {
        for(int a = filenameStartsAtIndex+1; a < (int)nextLine.size(); a++)
        {
          dependencyDownloadFilename.append(1, nextLine.at(a) );
        }
      }
    }else{ std::cout << "failed to open download source .txt file " << dep->getName() << "\n"; }

    if(dependencyDownloadFilename.size() > 0)
    {
      dep->setDownloadSourceFilename(dependencyDownloadFilename);
    }

    nextLinePair = text->getNextLine();
    if(nextLine.size() > 0)
    {
      std::string aptGetName = std::get<0>(nextLinePair);
      dep->setAptName(aptGetName);
    }
  }
}

dependency* manifestList::getDependencyByHeadIndex(int index)
{
  return this->getDependencyById(headDependencyIds->at(index));
}

dependency* manifestList::getDependencyById(int uniqueId)
{
  dependency* output = nullptr;
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* suspectDependency = dependencies->at(a);
    if(suspectDependency->getId() == uniqueId)
    {
      output = suspectDependency;
      a = dependencies->size();
    }
  }
  return output;
}


dependency* manifestList::getDependencyObjectByName(std::string dependencyName)
{
  dependency* output = nullptr;
  int index = 0;
  bool dependencyFound = false;
  for(size_t a = 0; a < dependencies->size(); a++)
  {
    dependency* suspectDependency = dependencies->at((int)a);
    if(strncmp(suspectDependency->getName().c_str(), dependencyName.c_str(), suspectDependency->getName().size())  == 0)
    {
      output = suspectDependency;
      index = (int)a;
      dependencyFound = true;
      a = (int)dependencies->size();
    }
  }

  if(dependencyFound == true)
  {
    output = dependencies->at(index);
  }
  return output;
}


bool manifestList::previouslyInstalled(int uniqueId)
{
  bool output = false;
  for(size_t a = 0; a < previouslyVirtuallyInstalled->size(); a++)
  {
    if(previouslyVirtuallyInstalled->at((int)a) == uniqueId)
    {
      output = true;
      a = (int)previouslyVirtuallyInstalled->size();
    }
  }
  return output;
}

void manifestList::appendVirtuallyInstalled(int uniqueId)
{
  previouslyVirtuallyInstalled->push_back(uniqueId);
}

int manifestList::totalHeads()
{
  return headDependencyIds->size();
}

#endif
