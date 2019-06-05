#include "dependency.h"

dependency::dependency()
{

}


void dependency::setId(int idToSetAs)
{
    uniqueId = idToSetAs;
}

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
