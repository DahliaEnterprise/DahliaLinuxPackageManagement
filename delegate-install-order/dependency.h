#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <iostream>
#include <vector>
class dependency
{
public:
  dependency();

  void initialize();

  void setId(int idToSetAs);
  int getUniqueId();

  void setName(std::string nameToSetAs);
  std::string getName();
  void appendPrerequisite(int prerequisiteUniqueId);
  bool hasPrerequisites();
  int getPrerequisiteUniqueId(int zeroBasedLevel);

private:
  int uniqueId;
  std::string name;
  std::vector<int>* prerequisiteList;
};

#endif // DEPENDENCY_H
