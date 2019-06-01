#ifndef DEPENDENCY_H
#define DEPENDENCY_H
class dependency
{
public:
    explicit dependency();
    ~dependency();
    
    void initialize();
    
    void determinePrerequisites(std::string directoryOfPrerequisiteInformation);
    
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
    unsigned int dependenciesMemorySize;
    unsigned int dependenciesAvailableIndex;
    
    
};
#endif
