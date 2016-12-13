#include <numeric>
#include <cassert>

#include "ApproximateQAgent.h"
#include "UltimateTicTacToeGame.h"

ApproximateQAgent::ApproximateQAgent() {

}

double ApproximateQAgent::GetQValue(
        const std::shared_ptr<IEnvironment> &environment, const pos &action) {
  auto features = this->feature_extractor.GetFeatures(
          dynamic_cast<UltimateTicTacToeGame*>(environment.get()));
  return std::inner_product(this->weights.begin(), this->weights.end(),
                            features.begin(),
                            0.0);
}

void ApproximateQAgent::UpdateQValues(const std::shared_ptr<IEnvironment> &environment,
                                      const pos &action,
                                      const std::shared_ptr<IEnvironment> &next_environment,
                                      double reward) {
  auto ultimate_tictactoe_game = dynamic_cast<UltimateTicTacToeGame*>(environment.get());
  auto features = this->feature_extractor.GetFeatures(ultimate_tictactoe_game);
  for (size_t i = 0; i < features.size(); ++i) {
    double difference = 0;
    if (next_environment.get()->IsTerminal()) {
      difference = reward - this->GetQValue(environment, action);
    } else {
      auto best_next_action = this->GetBestAction(environment);
      difference = reward
                   + this->discount*this->GetQValue(next_environment, best_next_action)
                   - this->GetQValue(environment, action);
    }
    this->weights[i] += this->alpha*difference*features[i];
  }
}

pos ApproximateQAgent::GetBestAction(const std::shared_ptr<IEnvironment> &environment) {
  pos best_action(-1, -1);
  double best_q_value = -1e20;

  auto possible_actions = environment.get()->GetPossibleActions();
  if (possible_actions.empty())
    assert("The state is terminal. No action exists.");
  for (size_t i = 0; i < possible_actions.size(); ++i) {
    auto &cur_action = possible_actions[i];
    auto q_value = this->GetQValue(environment, cur_action);
    if (best_q_value < q_value) {
      best_q_value = q_value;
      best_action = cur_action;
    }
  }
  return best_action;
}

pos ApproximateQAgent::GetAction(const std::shared_ptr<IEnvironment> &environment) {
  if (this->rng.NextDouble() < this->exploration_rate) {
    auto possible_actions = environment.get()->GetPossibleActions();
    if (possible_actions.empty())
      assert("The state is terminal. No action exists.");
    return possible_actions[rng.NextInt(0, (int)possible_actions.size() - 1)];
  } else {
    return this->GetBestAction(environment);
  }
}
