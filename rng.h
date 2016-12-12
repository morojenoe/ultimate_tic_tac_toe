#ifndef STRATEGY_RNG_H
#define STRATEGY_RNG_H

struct RNG {
  RNG(int seed = 1);

  void init(int seed);
  int next();
};

#endif //STRATEGY_RNG_H
