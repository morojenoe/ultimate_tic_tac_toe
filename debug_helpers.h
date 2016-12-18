#ifndef STRATEGY_DEBUG_HELPERS_H
#define STRATEGY_DEBUG_HELPERS_H

#include <iostream>
#include <cstdio>

#define MY_DEBUG

#ifdef MY_DEBUG
#define dbgx(x) {std::cerr << #x << " = " << x << std::endl;}
#define dbg(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}
#else
#define dbgx(x) {}
#define dbg(...) {}
#endif


#endif //STRATEGY_DEBUG_HELPERS_H
