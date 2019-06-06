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

int dependency::getId(){ return uniqueId; }
std::string dependency::getName()
{
  return name;
}

void dependency::appendPrerequisite(int prerequisiteId)
{
  prerequisiteIds->push_back(prerequisiteId);
}
