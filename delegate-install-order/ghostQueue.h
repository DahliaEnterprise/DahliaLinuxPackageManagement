#ifndef GHOSTQUEUE_H
#define GHOSTQUEUE_H

#include <vector>
#include <utility>
class ghostqueue
{
public:
    explicit ghostqueue();
    ~ghostqueue();

    void appendToEnd(int globalId, int level);
    bool contains(int globalId);
    
private:
    bool isNull;
    std::vector<int> headToTailGlobalIdentifiers;
    std::vector<int> headToTailLevels;
    
    std::vector< std::pair<int, std::vector< std::pair<int, std::vector<int> > > > >  duplicates;
    //   vector(      pair(depth,    vector(      pair(gId      vector(level) ) ) ) )
    
    
    void managePotentialDuplicate(int globalId, int level);
};
#endif
