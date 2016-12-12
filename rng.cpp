#include <iostream>
#include "rng.h"

RNG::RNG(unsigned long long seed) {
  Init(seed);
}

void RNG::Init(unsigned long long seed) {
  this->rng.seed(seed);
}

int RNG::NextInt() {
  static std::uniform_int_distribution<int> int_distribution;
  return int_distribution(this->rng);
}

double RNG::NextDouble() {
  static std::uniform_real_distribution<double> double_distribution;
  return double_distribution(this->rng);
}

int RNG::NextInt(int from, int to) {
  static std::uniform_int_distribution<int> int_distribution(from, to);
  return int_distribution(this->rng);
}
