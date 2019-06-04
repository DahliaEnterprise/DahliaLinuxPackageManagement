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
