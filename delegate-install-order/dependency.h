#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <iostream>

class dependency
{
public:
    dependency();
    void setId(int idToSetAs);
    void setName(std::string nameToSetAs);

private:
    int uniqueId;
    std::string name;
};

#endif // DEPENDENCY_H
