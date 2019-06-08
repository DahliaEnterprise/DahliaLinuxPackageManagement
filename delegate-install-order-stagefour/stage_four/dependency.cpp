#ifndef DEPENDENCY_CPP
#define DEPENDENCY_CPP

#include "dependency.h"

dependency::dependency()
{

}

void dependency::initialize(int setUniqueId, std::string setDependencyName)
{
  uniqueId = setUniqueId;
  name.append(setDependencyName);
  prerequisiteIds = new std::vector<int>();
}

int dependency::getId()
{
  return uniqueId;
}
std::string dependency::getName()
{
  return name;
}

void dependency::appendPrerequisite(int prerequisiteId)
{
  prerequisiteIds->push_back(prerequisiteId);
}

int dependency::totalPrerequisites()
{
  return prerequisiteIds->size();
}
bool dependency::hasPrerequisites()
{
  return (prerequisiteIds->size() > 0 ? true : false);
}

int dependency::getPrerequisiteIdByPrerquisiteListLevel(int index)
{
  return prerequisiteIds->at(index);
}

void dependency::printPrerequisites()
{
  for(size_t a = 0; a < prerequisiteIds->size(); a++)
  {
    std::cout << prerequisiteIds->at(a) << "\n";
  }
}
#endif
