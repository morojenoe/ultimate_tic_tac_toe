#include <algorithm>

#include "IBot.h"
#include "../rng.h"
#include "RandomBot.h"
#include "../debug_helpers.h"


pos RandomBot::makeMove(int time) {
  auto possible_actions = this->environment->GetPossibleActions();
  dbg("Round %d, Move %d\n", this->environment->GetRound(), this->environment->GetMove());
  for (size_t i = 0; i < possible_actions.size(); ++i) {
    dbg("%d) (%d, %d)\n", (int)i, possible_actions[i].r, possible_actions[i].c);
  }
  auto index = rng.NextInt(0, (int)possible_actions.size() - 1);
  dbg("RandomBot choses %d\n", index);
  return possible_actions[index];
}

RandomBot::RandomBot() : rng((unsigned long long)time(nullptr)) {

}
