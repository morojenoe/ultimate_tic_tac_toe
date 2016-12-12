#include <iostream>
#include "rng.h"

RNG::RNG(int seed) {
  init(seed);
}

void RNG::init(int seed) {
  srand((unsigned int)seed);
}

int RNG::next() {
  return rand();
}
