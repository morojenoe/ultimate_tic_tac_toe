#ifndef STRATEGY_RLBOT_H
#define STRATEGY_RLBOT_H


#include "IBot.h"
#include "../RL/ApproximateQAgent.h"

class RLBot : public IBot {
public:
  pos makeMove(int time) override;

protected:
  ApproximateQAgent agent;
};


#endif //STRATEGY_RLBOT_H
