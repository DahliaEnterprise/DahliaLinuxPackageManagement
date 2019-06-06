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

private:
  std::string directoryOfDependencies;
  std::string packageHeadTextFilename;

  std::vector<dependency*>* dependencies;

  int nextAvailableUniqueId;

  dependency* getDependencyUsingName(std::string name);
};

#endif // MANIFESTLIST_H
