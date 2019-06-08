#ifndef INSTALLORDER_CPP
#define INSTALLORDER_CPP

#include "installorder.h"

installOrder::installOrder()
{

}

void installOrder::initalize()
{
  uniqueIdOrder = new std::vector<int>();
  levelPerDepth = new std::vector<int>();
}


void installOrder::appendId(int uniqueId, int level)
{
  uniqueIdOrder->push_back(uniqueId);
  levelPerDepth->push_back(level);
}

int installOrder::tailId()
{
  return uniqueIdOrder->at(uniqueIdOrder->size()-1);
}

std::pair<int, int> installOrder::idAndLevelAtDepth(int zeroIndexBasedDepth)
{
  std::pair<int, int> output(uniqueIdOrder->at(zeroIndexBasedDepth), levelPerDepth->at(zeroIndexBasedDepth));
  return output;
}

int installOrder::totalDepths()
{
  return uniqueIdOrder->size();
}

void installOrder::removeTail()
{
  uniqueIdOrder->pop_back();
  levelPerDepth->pop_back();
}

int installOrder::parentIdOfTail()
{
  return uniqueIdOrder->at(uniqueIdOrder->size()-2);
}

int installOrder::tailLevel()
{
  return levelPerDepth->at(levelPerDepth->size()-1);
}

bool installOrder::isIdOnQueue(int id)
{
  bool output = false;
  for(size_t a = 0; a < uniqueIdOrder->size(); a++)
  {
    if(uniqueIdOrder->at(a) == id)
    {
      output = true;
    }
  }
  return output;
}

std::vector<int> installOrder::printOrder()
{
  std::vector<int> output;
  for(size_t a = 0; a < uniqueIdOrder->size(); a++)
  {
    output.push_back(uniqueIdOrder->at(a));
  }
  return output;
}

#endif
