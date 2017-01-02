#ifndef STRATEGY_APPROXIMATEQAGENT_H
#define STRATEGY_APPROXIMATEQAGENT_H


#include <vector>
#include <memory>

#include "IAgent.h"
#include "UltimateTicTacToeGame.h"
#include "../position.h"
#include "SimpleExtractor.h"
#include "../rng.h"

class ApproximateQAgent : public IAgent {
public:
  ApproximateQAgent();

  double GetQValue(const std::shared_ptr<IEnvironment> &environment,
                   const pos &action);
  void UpdateQValues(const std::shared_ptr<IEnvironment> &environment,
                     const pos &action,
                     const std::shared_ptr<IEnvironment> &next_environment,
                     double reward);
  pos GetAction(const std::shared_ptr<IEnvironment> &environment) override;
  pos GetBestAction(const std::shared_ptr<IEnvironment> &environment);

protected:
  RNG rng;
  std::vector<double> weights;
  SimpleExtractor feature_extractor;
  double alpha;
  double discount;
  double exploration_rate;
};


#endif //STRATEGY_APPROXIMATEQAGENT_H
