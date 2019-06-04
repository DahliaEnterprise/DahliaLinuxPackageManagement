#include <iostream>
#include "entiredependencylist.cpp"
int main(int argc, char *argv[])
{
    //Directory and file locations
    std::string directoryOfPackageInformation = std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/");
    std::string manifestLocation = std::string(); manifestLocation.append(directoryOfPackageInformation); manifestLocation.append("manifest.txt");
    std::string packageHeadDependencyListFilename = std::string("BuildEssential_amd64.txt");
    std::string completeLocationToPackageHead = std::string(); completeLocationToPackageHead.append(directoryOfPackageInformation); completeLocationToPackageHead.append(packageHeadDependencyListFilename);

    //Convert manifest text file into list of objects(with id and dependency names)
    entireDependencyList* manifest = new entireDependencyList();
    manifest->forEveryLineInManifest_thenAppendToArrayWithUniqueId(manifestLocation);



    return 0;
}
