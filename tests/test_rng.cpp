#include <gtest/gtest.h>
#include <vector>

#include "../rng.h"


namespace {

TEST(RngTest, NextIntFromToTestOnlyPositive) {
  RNG rng;
  int from = 0, to = 1;
  for (int i = 0; i < 1000000; ++i) {
    auto rand_value = rng.NextInt(from, to);
    ASSERT_LE(from, rand_value);
    ASSERT_LE(rand_value, to);
    ++from;
    to += 2;
  }
}


}
