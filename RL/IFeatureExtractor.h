#ifndef STRATEGY_IFEATUREEXTRACTOR_H
#define STRATEGY_IFEATUREEXTRACTOR_H


#include <vector>
#include <memory>
#include "UltimateTicTacToeGame.h"

class IFeatureExtractor {
public:
  virtual std::vector<double> GetFeatures(
          const std::shared_ptr<UltimateTicTacToeGame> &environment) = 0;
};


#endif //STRATEGY_IFEATUREEXTRACTOR_H
