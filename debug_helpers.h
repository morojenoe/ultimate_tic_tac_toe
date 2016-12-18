#ifndef STRATEGY_DEBUG_HELPERS_H
#define STRATEGY_DEBUG_HELPERS_H

#include <iostream>

#define MY_DEBUG

#ifdef MY_DEBUG
#define dbgx(x) {cerr << #x << " = " << x << endl;}
#define dbg(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}
#else
#define dbgx(x) {}
#define dbg(...) {}
#endif


#endif //STRATEGY_DEBUG_HELPERS_H
