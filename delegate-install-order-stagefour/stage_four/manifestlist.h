#ifndef MANIFESTLIST_H
#define MANIFESTLIST_H

#include <iostream>
#include <fstream>
#include "dependency.cpp"
#include <vector>
#include "textfile.cpp"
#include <tuple>
#include "installorder.cpp"

class manifestList
{
public:
  manifestList();

  void initialize(std::string setDirectoryOfDependencies, std::string setPackageHeadTextFilename);
  void stepone_convertManifestTextToObjects();
  void steptwo_linkPrerequisitesToTheirRespectiveDependencies();
  void stepthree_determineHeadDependencies();
  dependency* getDependencyByHeadIndex(int index);
  dependency* getDependencyById(int uniqueId);


  dependency* getDependencyObjectByName(std::string dependencyName);
  bool previouslyInstalled(int uniqueId);
  void appendVirtuallyInstalled(int uniqueId);

  int totalHeads();

private:
  std::string directoryOfDependencies;
  std::string packageHeadTextFilename;

  std::vector<dependency*>* dependencies;
  int nextAvailableUniqueId;

  std::vector<int>* headDependencyIds;

  std::vector<int>* previouslyVirtuallyInstalled;

  bool stringMatches(std::string string1, std::string string2, size_t finiteLimit);

};

#endif // MANIFESTLIST_H
