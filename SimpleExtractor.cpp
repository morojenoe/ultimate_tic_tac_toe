#include <vector>

#include "SimpleExtractor.h"

std::vector<double> SimpleExtractor::GetFeatures(
        std::shared_ptr<UltimateTicTacToeGame> environment) {
  std::vector<double> features;

  features.push_back(environment.get()->GetNumberOfBigSquaresIWin());

  features.push_back(environment.get()->GetNumberOfBigSquaresOpponentWin());

  return features;
}
