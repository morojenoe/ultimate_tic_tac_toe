#ifndef STRATEGY_RNG_H
#define STRATEGY_RNG_H

#include <random>

class RNG {
public:
  RNG(unsigned long long seed = 1);

  void Init(unsigned long long seed);
  int NextInt();
  int NextInt(int from, int to);
  double NextDouble();

private:
  std::mt19937 rng;
};

#endif //STRATEGY_RNG_H
