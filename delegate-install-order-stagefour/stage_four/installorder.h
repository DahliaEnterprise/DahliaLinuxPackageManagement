#ifndef INSTALLORDER_H
#define INSTALLORDER_H

#include <vector>
class installOrder
{
public:
  installOrder();
  void initalize();
  void appendId(int uniqueId, int level);
  int tailId();
  std::pair<int, int> idAndLevelAtDepth(int zeroIndexBasedDepth);
  int totalDepths();
  void removeTail();
  int parentIdOfTail();
  int tailLevel();
  bool isIdOnQueue(int id);
  std::vector<int> printOrder();

private:
  std::vector<int>* uniqueIdOrder;
  std::vector<int>* levelPerDepth;
};

#endif // INSTALLORDER_H
