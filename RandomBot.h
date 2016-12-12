//
// Created by dima on 12.12.16.
//

#ifndef STRATEGY_RANDOMBOT_H
#define STRATEGY_RANDOMBOT_H

class RandomBot : public IBot {
public:
  pos makeMove(int time) override;

private:
  RNG rng;
};


#endif //STRATEGY_RANDOMBOT_H
