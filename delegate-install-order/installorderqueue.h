#ifndef INSTALLORDERQUEUE_H
#define INSTALLORDERQUEUE_H

#include <vector>
#include <utility>

class installOrderQueue
{
public:
  installOrderQueue();
  void initialize();
  void appendAsDepth(int dependencyUniqueId, int zeroBasedLevel);

private:
  std::vector<std::pair<int, int>>* installOrder;
};

#endif // INSTALLORDERQUEUE_H
