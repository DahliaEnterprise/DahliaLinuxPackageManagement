#include <stdio.h>
#include <string.h>
#include <iostream>
#include "dependency.cpp"

int main()
{
    //Define Engligh UTF-8 as the locale
    const std::locale locale = std::locale("en_US.utf8");
    
    //load Entry point BuildEssential_amd64.txt file
    dependency entryPointofBuildEssentials = dependency(); entryPointofBuildEssentials.setIsHead(true);
    dependency dpkg_dev = dependency(); dpkg_dev.setDependencyName(std::string("dpkg-dev"));
    dependency gpp = dependency(); gpp.setDependencyName(std::string("g++"));
    dependency libc6_dev = dependency(); libc6_dev.setDependencyName(std::string("libc6-dev"));
    
    //TODO: reference depencesinces and prerequiriestes
    return 0;
}
