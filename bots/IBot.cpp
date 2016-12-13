#include "../UltimateTicTacToeGame.h"
#include "IBot.h"

IBot::~IBot() {}

IBot::IBot() {
  this->environment = std::make_shared<UltimateTicTacToeGame>();
}
