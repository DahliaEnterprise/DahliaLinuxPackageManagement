#include <iostream>
#include "entiredependencylist.cpp"
#include "installorderqueue.cpp"
#include "installorderqueuegenerator.cpp"
int main(int argc, char *argv[])
{
    //Directory and file locations
    std::string directoryOfPackageInformation = std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/");
    std::string manifestLocation = std::string(); manifestLocation.append(directoryOfPackageInformation); manifestLocation.append("manifest.txt");
    std::string packageHeadDependencyListFilename = std::string("BuildEssential_amd64.txt");
    std::string completeLocationToPackageHead = std::string(); completeLocationToPackageHead.append(directoryOfPackageInformation); completeLocationToPackageHead.append(packageHeadDependencyListFilename);

    //Convert manifest text file into list of objects(with id and dependency names)
    entireDependencyList* manifest = new entireDependencyList();
    manifest->initialize();
    manifest->forEveryLineInManifest_thenAppendToArrayWithUniqueId(manifestLocation);
    manifest->assignPrerequisites(directoryOfPackageInformation);

    //Determine head dependencies using the "BuildEssentail_amd64" text file.
    manifest->determineAndFlagHeadDependencies(completeLocationToPackageHead);

    //Initialize Generator
    installOrderQueueGenerator* generator = new installOrderQueueGenerator();
    generator->becomeAwareOfManifest(manifest);

    //Generate queues
    std::vector<installOrderQueue*>* installOrderQueues = new std::vector<installOrderQueue*>();
      //while loop through each head dependency,generating an install order with each depth at level zero from head to tail.
        //Generate one install order queue with each depth at level zero from head to tail.
        generator->generateHeadInstallOrderQueue(0/*i*/);

      //end while loop

    //Free
    delete manifest;

    return 0;
}
