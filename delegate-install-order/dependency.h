#ifndef DEPENDENCY_H
#define DEPENDENCY_H
class dependency
{
public:
    explicit dependency();
    
    void initialize();
    
    void setDependencyName(std::string nameToSetAs);
    void setIsHead(bool newHeadState);
    
private:
    //Depedency Information
    std::string name;
    bool isHead;
    
    //Prerequisites associated with this depdendency.
    bool hasPrerequisites;
    unsigned int totalPrerequisites;
    dependency* dependencies;
    
    
};
#endif
