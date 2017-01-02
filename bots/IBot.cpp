#include "../RL/UltimateTicTacToeGame.h"
#include "IBot.h"

IBot::~IBot() {}

IBot::IBot() : environment(std::make_shared<UltimateTicTacToeGame>()) {

}
