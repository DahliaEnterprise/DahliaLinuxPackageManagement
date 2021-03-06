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
  void assignPrerequisites(std::string directoryOfPackageInformation);
  void determineAndFlagHeadDependencies(std::string fileLocation);

  int getHeadDependencyAt(int index);
  dependency* getDependencyByUniqueId(int uniqueId);

private:
  std::vector<std::pair<int,std::string>>* manifestList;
  int nextAvailableManifestListDependencyId;
  int getNextAvailableManifestListDependencyId();

  std::vector<dependency*>* dependencyList;
  void createDependencyObject(int dependencyId, std::string dependencyName);

  std::vector<int>* headDependencyList;

  int getUniqueIdByDependencyName(std::string dependencyName);


  //Convience Assistance
  int normalizedArrayLength(int length);
};

#endif // ENTIREDEPENDENCYLIST_H
