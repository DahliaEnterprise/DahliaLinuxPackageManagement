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
    std::vector<int>* virtuallyInstalledDependencies = new std::vector<int>();
    installOrderQueueGenerator* generator = new installOrderQueueGenerator();
    generator->becomeAwareOfVirtuallyInstalledDependencies(virtuallyInstalledDependencies);
    generator->becomeAwareOfManifest(manifest);

    //Generate queues

    std::vector<installOrderQueue*>* installOrderQueues = new std::vector<installOrderQueue*>();
      //while loop through each head dependency,generating an install order with each depth at level zero from head to tail.
        //Generate one install order queue with each depth at level zero from head to tail.
        installOrderQueue* firstInstallOrderQueue = generator->generateHeadInstallOrderQueue(0/*i*/);
        installOrderQueues->push_back(firstInstallOrderQueue);
        std::cout << "first/head queue\n";
        firstInstallOrderQueue->printInstallOrderQueue(manifest);

        //Generate queues past the head-to-tail queue until all levels on every depth have been traversed.
        installOrderQueue* previousInstallOrderQueue = generator->generateNextQueue(installOrderQueues->at(0));
        installOrderQueues->push_back(previousInstallOrderQueue);
        std::cout << "\n second head queue \n";
        previousInstallOrderQueue->printInstallOrderQueue(manifest);

        int a = 1;
        while(a < 100)
        {

          int normalizedArrayLength = (installOrderQueues->size()-1 <= 0) ? 0 : installOrderQueues->size()-1;
          installOrderQueue* nextQueue = generator->generateNextQueue(installOrderQueues->at(normalizedArrayLength));
          installOrderQueues->push_back(nextQueue);
          nextQueue->printInstallOrderQueue(manifest);
          a++;
        }

        /** DEPRECATED
        installOrderQueue* nextQueue1 = generator->generateNextQueue(installOrderQueues->at(1));
        installOrderQueues->push_back(nextQueue1);
        std::cout << "\n third head queue \n";
        nextQueue1->printInstallOrderQueue(manifest);

        installOrderQueue* nextQueue2 = generator->generateNextQueue(installOrderQueues->at(2));
        installOrderQueues->push_back(nextQueue2);
        std::cout << "\n fourth head queue \n";
        nextQueue2->printInstallOrderQueue(manifest);

        installOrderQueue* nextQueue3 = generator->generateNextQueue(installOrderQueues->at(3));
        installOrderQueues->push_back(nextQueue3);
        std::cout << "\n five head queue \n";
        nextQueue3->printInstallOrderQueue(manifest);

        installOrderQueue* nextQueue4 = generator->generateNextQueue(installOrderQueues->at(4));
        installOrderQueues->push_back(nextQueue4);
        std::cout << "\n six head queue \n";
        nextQueue4->printInstallOrderQueue(manifest);
        **/

      //end while loop

    //Free
    delete manifest;

    return 0;
}
