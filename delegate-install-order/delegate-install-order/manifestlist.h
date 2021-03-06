#ifndef MANIFESTLIST_H
#define MANIFESTLIST_H

#include <iostream>
#include <fstream>
#include "dependency.cpp"
#include <vector>
class manifestList
{
public:
  manifestList();

  void initialize(std::string setDirectoryOfDependencies, std::string setPackageHeadTextFilename);
  void stepone_convertManifestTextToObjects();
  void steptwo_convertPrerequisitesTextToRespectiveObjects();
  void stepthree_determineHeadDependencies();
  int  getHeadDependencyIdByIndex(int index);
  dependency* getDependencyUsingId(int uniqueId);
  bool isDependencyInstalled(int dependencyId);

private:
  std::string directoryOfDependencies;
  std::string packageHeadTextFilename;

  std::vector<dependency*>* dependencies;

  int nextAvailableUniqueId;

  std::vector<int>* headDependency;

  std::vector<int>* dependenciesVirtuallyInstalled;

  dependency* getDependencyUsingName(std::string name);
};

#endif // MANIFESTLIST_H
