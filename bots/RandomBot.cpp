#include <algorithm>

#include "IBot.h"
#include "../rng.h"
#include "RandomBot.h"
#include "../debug_helpers.h"


pos RandomBot::makeMove(int time) {
  auto possible_actions = this->environment->GetPossibleActions();
  auto index = rng.NextInt(0, (int)possible_actions.size() - 1);
  return possible_actions[index];
}

RandomBot::RandomBot() : rng((unsigned long long)time(nullptr)) {

}
