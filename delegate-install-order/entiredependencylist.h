#ifndef ENTIREDEPENDENCYLIST_H
#define ENTIREDEPENDENCYLIST_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "dependency.cpp"

class entireDependencyList
{
public:
  explicit entireDependencyList();
  ~entireDependencyList();
  void initialize();

  void forEveryLineInManifest_thenAppendToArrayWithUniqueId(std::string fileLocation);
  void determineAndFlagHeadDependencies(std::string fileLocation);


private:
  std::vector<std::pair<int,std::string>>* manifestList;
  int nextAvailableManifestListDependencyId = 1;
  int getNextAvailableManifestListDependencyId();

  std::vector<dependency*>* dependencyList;
  void createDependencyObject(int dependencyId, std::string dependencyName);

  int getUniqueIdByDependencyName(std::string dependencyName);
};

#endif // ENTIREDEPENDENCYLIST_H
