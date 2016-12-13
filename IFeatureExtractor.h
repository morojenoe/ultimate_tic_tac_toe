#ifndef STRATEGY_IFEATUREEXTRACTOR_H
#define STRATEGY_IFEATUREEXTRACTOR_H


#include <vector>
#include <memory>
#include "UltimateTicTacToeGame.h"

class IFeatureExtractor {
public:
  virtual std::vector<double> GetFeatures(
          std::shared_ptr<UltimateTicTacToeGame> environtment) = 0;
};


#endif //STRATEGY_IFEATUREEXTRACTOR_H
