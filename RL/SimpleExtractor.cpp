#include <vector>

#include "SimpleExtractor.h"

std::vector<double> SimpleExtractor::GetFeatures(const std::shared_ptr<UltimateTicTacToeGame> &environment) {
  std::vector<double> features;

  features.push_back(environment->GetNumberOfBigSquaresIWin());

  features.push_back(environment->GetNumberOfBigSquaresOpponentWin());

  return features;
}
