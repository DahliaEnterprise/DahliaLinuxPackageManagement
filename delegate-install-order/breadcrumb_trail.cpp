#include "breadcrumb_trail.h"

/*
    // //                                        \\ \\
    || ||   Constructor, Destructor, Initialize   || ||
    \\ \\                                        // //
*/

breadcrumb_trail::breadcrumb_trail()
{
   breadcrumbsSize = 0;
}
breadcrumb_trail::~breadcrumb_trail()
{
    
}

void breadcrumb_trail::appendBreadCrumb(int dependencyGlobalIdentifier, int breadCrumbLevel)
{
    breadcrumb* newBreadcrumb = new breadcrumb();
    newBreadcrumb->setBreadcrumb(dependencyGlobalIdentifier, breadCrumbLevel);
    breadcrumbs[breadcrumbsSize] = newBreadcrumb;
    breadcrumbsSize += 1;
}

int breadcrumb_trail::tailEndGlobalIdentifier()
{
    int output = -1;
    breadcrumb* tailEndBreadcrumb = breadcrumbs[breadcrumbsSize-1];
    int tailEndBreadcrumbGlobalIdentifier = tailEndBreadcrumb->getGlobalIdentifier();
    output = tailEndBreadcrumbGlobalIdentifier;
    
    return output;
}

int breadcrumb_trail::tailEndCurrentLevel()
{
    int output = -1;
    
    breadcrumb* tailEndBreadcrumb = breadcrumbs[breadcrumbsSize-1];
    int tailEndBreadcrumbCurrentLevel = tailEndBreadcrumb->getCurrentLevel();
    output = tailEndBreadcrumbCurrentLevel;
    
    return output;
}

int breadcrumb_trail::totalBreadcrumbs()
{
    int output = -1;
    
    output = breadcrumbsSize;
    
    return output;
}

breadcrumb* breadcrumb_trail::getBreadcrumbByIndex(int index)
{
    
    return breadcrumbs[index];
}
