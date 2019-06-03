#ifndef DEPENDENCY_H
#define DEPENDENCY_H
class dependency
{
public:
    explicit dependency();
    ~dependency();
    
    void initialize();
    void initializeAsNull();
    
    void appendPrerequisite(int prerequisiteGlobalId);
    void setGlobalIdentifier(int identifier);
    void setDependencyName(char* nameToSetAs);
    
    bool getIsNull();
    char* getDependencyName();
    int getGlobalIdentifier();
    int getTotalPrerequisites();
    int getPrerequisiteGlobalIdentifierByLevel(int level);
    bool containsPrerequisite(int prerequisiteGlobalIdentifier);
    std::pair<int, int> getDependencyAtDepth(int depth);
    
private:
    bool isNull;
    
    //Dependency Information
    char* name;
    int id;
    
    //Prerequisite Information
    int totalPrerequisites;
    int prerequisiteGlobalIdentifier[100];
    
};
#endif
