#ifndef MANIFESTLIST_H
#define MANIFESTLIST_H

#include <iostream>
#include <fstream>
#include "dependency.cpp"
#include <vector>
#include "textfile.cpp"
#include <tuple>

class manifestList
{
public:
  manifestList();

  void initialize(std::string setDirectoryOfDependencies, std::string setPackageHeadTextFilename);
  void stepone_convertManifestTextToObjects();
  void steptwo_linkPrerequisitesToTheirRespectiveDependencies();

  dependency* getDependencyObjectByName(std::string dependencyName);

private:
  std::string directoryOfDependencies;
  std::string packageHeadTextFilename;

  std::vector<dependency*>* dependencies;

  int nextAvailableUniqueId;

  bool stringMatches(std::string string1, std::string string2, size_t finiteLimit);
};

#endif // MANIFESTLIST_H
