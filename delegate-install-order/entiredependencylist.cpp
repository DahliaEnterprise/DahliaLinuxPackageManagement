#include "entiredependencylist.h"

entireDependencyList::entireDependencyList()
{

}


void entireDependencyList::forEveryLineInManifest_thenAppendToArrayWithUniqueId(std::string fileLocation)
{
    std::ifstream manifestTextFile; manifestTextFile.open(fileLocation, std::ifstream::in);
    if(manifestTextFile.is_open() == true)
    {
        char dependencyName[100];
        memset(dependencyName, '\0', 100);
        manifestTextFile.getline(dependencyName, 100);
        while(strlen(dependencyName) > 0)
        {
            //Append dependency name from text file to this object.
            std::string dependencyNameString = std::string(dependencyName);
            int dependencyId = this->getNextAvailableManifestListDependencyId();
            manifestList.push_back(std::pair<int,std::string>(dependencyId,dependencyNameString));
            this->createDependencyObject(dependencyId, dependencyNameString);

            //Reset for next iteration of while loop
            memset(dependencyName, '\0', 100);
            manifestTextFile.getline(dependencyName, 100);
        }
    }else{ std::cout << "failed to manifestTextFileLocation()\n"; }
}

void entireDependencyList::createDependencyObject(int dependencyId, std::string dependencyName)
{
    //create dependency object, assigning id and name.
    dependency* newDep = new dependency();
    newDep->setId(dependencyId);
    newDep->setName(dependencyName);
}


int entireDependencyList::getNextAvailableManifestListDependencyId()
{
    int output = -1;
    output = nextAvailableManifestListDependencyId;
    nextAvailableManifestListDependencyId += 1;
    return output;
}
