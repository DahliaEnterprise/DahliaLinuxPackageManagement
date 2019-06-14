#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <iostream>
#include <vector>
class dependency
{
public:
  dependency();
  void initialize(int uniqueId, std::string dependencyName);

  void appendPrerequisite(int prerequisiteId);
  int totalPrerequisites();
  bool hasPrerequisites();
  int getPrerequisiteIdByPrerquisiteListLevel(int index);

  int getId();
  std::string getName();

  void printPrerequisites();
  void setDownloadSourceFilename(std::string setDSFilename);
  void setAptName(std::string setAptgetName);
  std::string getAptgetName();

private:
  int uniqueId;
  std::string name;
  std::string downloadSourceFilename;
  std::string aptgetName;
  std::vector<int>* prerequisiteIds;
};

#endif // DEPENDENCY_H
