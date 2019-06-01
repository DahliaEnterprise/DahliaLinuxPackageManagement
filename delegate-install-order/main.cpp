#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "dependency.cpp"

int main()
{
    //Define Engligh UTF-8 as the locale
    const std::locale locale = std::locale("en_US.utf8");
    
    //load entry point BuildEssential_amd64.txt file
    std::ifstream entryPointofBuildEssentials;
    entryPointofBuildEssentials.open("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/BuildEssential_amd64.txt", std::ifstream::in);
     char c = entryPointofBuildEssentials.get();

  while (entryPointofBuildEssentials.good()) {
    std::cout << c;
    c = entryPointofBuildEssentials.get();
  }

  entryPointofBuildEssentials.close();
    
    /** DEPRECATED
    dependency entryPointofBuildEssentials = dependency(); entryPointofBuildEssentials.setIsHead(true);
        dependency dpkg_dev = dependency(); dpkg_dev.setDependencyName(std::string("dpkg-dev"));
            dependency binutils = dependency(); binutils.setDependencyName(std::String("binutils"));
                dependency libc6_dev = dependency(); libc6_dev.set
        dpkg_dev.appendPrerequisite(binutils);
            
        
        dependency gpp = dependency(); gpp.setDependencyName(std::string("g++"));
        dependency libc6_dev = dependency(); libc6_dev.setDependencyName(std::string("libc6-dev"));
    **/
    //TODO: reference depencesinces and prerequiriestes
    return 0;
}
