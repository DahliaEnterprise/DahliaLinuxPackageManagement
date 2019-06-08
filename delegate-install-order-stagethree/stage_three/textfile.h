#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <iostream>
#include <fstream>
#include <cstring>

class textFile
{
public:
  textFile();
  void openTextFile(std::string setDirectoryAndFilename);
  std::pair<std::string, bool> getNextLine();
  int fileLength();

private:
  std::string directoryAndFilename;
  std::fstream* file;
};

#endif // TEXTFILE_H
