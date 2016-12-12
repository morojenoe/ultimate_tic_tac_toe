#ifndef STRATEGY_FEATURE_EXTRACTOR_H
#define STRATEGY_FEATURE_EXTRACTOR_H


#include "IFeatureExtractor.h"

class SimpleExtractor : public IFeatureExtractor {
public:
  virtual std::vector<double> GetFeatures(std::shared_ptr<IEnvironment> environtment) override;
};


#endif //STRATEGY_FEATURE_EXTRACTOR_H
