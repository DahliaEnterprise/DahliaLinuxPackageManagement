#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <iostream>
#include <vector>
class dependency
{
public:
  dependency();
  void setId(int idToSetAs);
  void setName(std::string nameToSetAs);
  std::string getName();
  void appendPrerequisite(int prerequisiteUniqueId);

private:
  int uniqueId;
  std::string name;
  std::vector<int>* prerequisiteList;
};

#endif // DEPENDENCY_H
