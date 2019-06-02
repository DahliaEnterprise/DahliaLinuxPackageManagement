#ifndef DEPENDENCY_H
#define DEPENDENCY_H
class dependency
{
public:
    explicit dependency();
    ~dependency();
    
    void initialize();
    
    void setGlobalIdentifier(int identifier);
    void setDependencyName(char* nameToSetAs);
    char* getDependencyName();
    
private:
    //Depedency Information
    char* name;
    int id;
    
};
#endif
