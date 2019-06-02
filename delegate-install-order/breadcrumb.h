#ifndef BREADCRUMB_H
#define BREADCRUMB_H
class breadcrumb
{
public:
    explicit breadcrumb();
    ~breadcrumb();
    
    void setBreadcrumb(int dependencyGlobalIdentifier, int levelToSetAs);
    int getGlobalIdentifier();
    
private:
    int level;
    int dependencyGlobalIdentifier;
    
};
#endif
