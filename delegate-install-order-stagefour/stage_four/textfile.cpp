#include "textfile.h"

textFile::textFile()
{

}

void textFile::openTextFile(std::string setDirectoryAndFilename)
{
  directoryAndFilename.append(setDirectoryAndFilename);
  file = new std::fstream();
  file->open(directoryAndFilename);
}

std::pair<std::string, bool> textFile::getNextLine()
{
  std::pair<std::string, bool> output;
  std::string outputString;
  char* nextLineChar = (char*)malloc(2 * sizeof(char));

  int totalCharactersExpected = this->fileLength();
  int totalCharactersConsumed = 0;
  bool isCharacter = true;
  bool keep_looping = true;
  while(keep_looping == true)
  {
    memset(nextLineChar, '\0', 2);
    file->read(nextLineChar, 1);

    if(strncmp(nextLineChar, "\n", 1) == 0){ isCharacter = false; }
    if(strlen(nextLineChar) == 0){ isCharacter = false; }

    if(isCharacter == true)
    {
      outputString.append(nextLineChar, 1);
    }else if(isCharacter == false)
    {
      keep_looping = false;
    }
    totalCharactersConsumed += 1;
    if(totalCharactersConsumed >= totalCharactersExpected){ keep_looping = false;/*infinite loop prevention*/ }
  }
  bool endOfFileReached = false;
  if(file->tellg() >= totalCharactersExpected){ endOfFileReached = true; }
  output = std::make_pair(outputString, endOfFileReached);
  free(nextLineChar);
  return output;
}

int textFile::fileLength()
{
  int output = -1;

  int savePosition = file->tellg();
  file->seekg(0, file->end);
  int textFileTotalCharacters = file->tellg();
  file->seekg(savePosition, file->beg);
  output = textFileTotalCharacters;

  return output;
}
