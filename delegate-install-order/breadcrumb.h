#ifndef BREADCRUMB_H
#define BREADCRUMB_H
class breadcrumb
{
public:
    explicit breadcrumb();
    ~breadcrumb();
    
    void setBreadcrumb(int dependencyGlobalIdentifier, int levelToSetAs);
    int getGlobalIdentifier();
    int getCurrentLevel();
    
private:
    int level;
    int dependencyGlobalIdentifier;
    
};
#endif
