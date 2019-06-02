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
    breadcrumb* tailEndBreadcrumb = breadcrumbs[breadcrumbsSize];
    int tailEndBreadcrumbGlobalIdentifier = tailEndBreadcrumb.getGlobalIdentifier();
    
    return output;
}

int breadcrumb_trail::tailEndCurrentLevel()
{
    int output = -1;
    
    breadcrumb* tailEndBreadcrumb = breadcrumbs[breadcrumbsSize];
    int tailEndBreadcrumbCurrentLevel = tailEndBreadcrumb.getGlobalIdentifier();
    output = tailEndBreadcrumbCurrentLevel;
    
    return output;
}
