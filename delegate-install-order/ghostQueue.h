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
    int getQueueLength();
    std::pair<int, int> getDependencyAtDepth(int depth);
    void removeTailEnd();
    //std::pair<int, int> getParentGlobalIdOfTailEnd();
    
private:
    bool isNull;
    std::vector<int> headToTailGlobalIdentifiers; // depth-->   
    std::vector<int> headToTailLevels;            /* levels |   
                                                           \*/
    
    std::vector< std::pair<int, std::vector< std::pair<int, std::vector<int> > > > >  duplicates;
    //   vector(      pair(depth,    vector(      pair(gId      vector(level) ) ) ) )
};
#endif
