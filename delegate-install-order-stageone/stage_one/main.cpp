#include <iostream>
#include "manifestlist.cpp"
int main(int argc, char *argv[])
{
  /** Load Dependency and Prereuqisite Information into Program **/
  manifestList* manifest = new manifestList();
  manifest->initialize(std::string("/home/dahlia/Downloads/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/"), std::string("BuildEssential_amd64"));
  manifest->stepone_convertManifestTextToObjects();

  return 0;
}
