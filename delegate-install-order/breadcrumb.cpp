#include "breadcrumb.h"

/*
    // //                                        \\ \\
    || ||   Constructor, Destructor, Initialize   || ||
    \\ \\                                        // //
*/

breadcrumb::breadcrumb()
{
   level = -1;
}
breadcrumb::~breadcrumb()
{
    
}

void breadcrumb::setBreadcrumb(int setDependencyGlobalIdentifier, int levelToSetAs){ dependencyGlobalIdentifier = setDependencyGlobalIdentifier; level = levelToSetAs; }
int breadcrumb::getGlobalIdentifier(){ return dependencyGlobalIdentifier; }
