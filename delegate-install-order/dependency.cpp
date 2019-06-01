#include "dependency.h"
dependency::dependency()
{
    name = std::string();
    isHead = false;
    hasPrerequisites = false;
    totalPrerequisites = 0;
}

void dependency::initialize()
{
    dependencies = (dependency*) calloc(100, sizeof(dependency));
}

/** Primal Conviences, Set Information **/
void dependency::setDependencyName(std::string nameToSetAs){ name.clear(); name.append(nameToSetAs); }
void dependency::setIsHead(bool newHeadState){ isHead = newHeadState; }
