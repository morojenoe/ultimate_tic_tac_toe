#ifndef STRATEGY_RANDOMBOT_H
#define STRATEGY_RANDOMBOT_H

#include "../rng.h"
#include "../position.h"

class RandomBot : public IBot {
public:
  pos makeMove(int time) override;

private:
  RNG rng;
};


#endif //STRATEGY_RANDOMBOT_H
