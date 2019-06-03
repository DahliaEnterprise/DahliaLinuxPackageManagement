#ifndef QUEUE_H
#define QUEUE_H
class queue
{
public:
    explicit queue();
    ~queue();
    
    void defineFromVectorHeadToTailAllZeroLevels(std::vector<int> GlobalIdsfromHeadToTailAllZeroLevels);
    
private:
    std::vector<int> headToTailGlobalIdentifiers;
    std::vector<int> headToTailLevels;
    
};
#endif
