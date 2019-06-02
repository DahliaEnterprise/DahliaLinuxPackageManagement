#ifndef BREADCRUMB_TRAIL_H
#define BREADCRUMB_TRAIL_H

class breadcrumb_trail
{
public:
    explicit breadcrumb_trail();
    ~breadcrumb_trail();
    
    void appendBreadCrumb(int dependencyGlobalIdentifier, int breadCrumbLevel);
    int tailEndGlobalIdentifier();
    int tailEndCurrentLevel();
    
private:
    breadcrumb* breadcrumbs[1000];
    int breadcrumbsSize;
};
#endif
