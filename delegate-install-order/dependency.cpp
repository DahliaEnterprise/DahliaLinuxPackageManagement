#include "dependency.h"

dependency::dependency()
{
  uniqueId = -1;
}

void dependency::initialize()
{
  prerequisiteList = new std::vector<int>();
}

void dependency::setId(int idToSetAs)
{
    uniqueId = idToSetAs;
}

int dependency::getUniqueId(){ return uniqueId; }

void dependency::setName(std::string nameToSetAs)
{
    name.clear();
    name.append(nameToSetAs);
}

std::string dependency::getName(){ return name; }


void dependency::appendPrerequisite(int prerequisiteUniqueId)
{
  prerequisiteList->push_back(prerequisiteUniqueId);
}

bool dependency::hasPrerequisites()
{
  bool output = false;
  if(prerequisiteList->size() > 0){ output = true; }
  return output;
}

int dependency::getPrerequisiteUniqueId(int zeroBasedLevel)
{
  int output = -1;
  int prerequisiteUniqueId = -1;
  prerequisiteUniqueId = prerequisiteList->at(zeroBasedLevel);
  output = prerequisiteUniqueId;
  return output;
}
