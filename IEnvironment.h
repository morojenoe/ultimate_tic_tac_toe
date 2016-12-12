#ifndef STRATEGY_IENVIRONMENT_H
#define STRATEGY_IENVIRONMENT_H

#include <vector>

#include "position.h"

class IEnvironment {
public:
  IEnvironment() {}
  virtual ~IEnvironment() {}

  virtual void Init();
  virtual void DoAction(pos action, double &reward) = 0;
  virtual std::vector<pos> GetPossibleActions() = 0;
  virtual bool IsTerminal();
};


#endif //STRATEGY_IENVIRONMENT_H
