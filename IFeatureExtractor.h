#ifndef STRATEGY_IFEATUREEXTRACTOR_H
#define STRATEGY_IFEATUREEXTRACTOR_H


#include <vector>
#include <bits/shared_ptr.h>
#include "IEnvironment.h"

class IFeatureExtractor {
public:
  virtual std::vector<double> GetFeatures(std::shared_ptr<IEnvironment> environtment) = 0;
};


#endif //STRATEGY_IFEATUREEXTRACTOR_H
