#include <numeric>
#include <cassert>
#include <cstdio>
#include <ios>
#include <fstream>
#include <sstream>

#include "ApproximateQAgent.h"
#include "UltimateTicTacToeGame.h"

ApproximateQAgent::ApproximateQAgent() {
  std::ifstream file("/home/dima/Projects/theaigames/tictactoe/rl/weights.txt", std::ios::in);
  char buf[5000];
  std::stringstream ss;
  while (file.getline(buf, 5000)) {
    ss.clear();
    ss << buf;
  }
  this->weights.clear();
  double weight;
  while (ss >> weight) {
    this->weights.push_back(weight);
  }

  file.close();
}

double ApproximateQAgent::GetQValue(
        const std::shared_ptr<UltimateTicTacToeGame> &environment, const pos &action) {
  auto features = this->feature_extractor.GetFeatures(environment);
  return std::inner_product(this->weights.begin(), this->weights.end(),
                            features.begin(),
                            0.0);
}

void ApproximateQAgent::UpdateQValues(const std::shared_ptr<UltimateTicTacToeGame> &environment,
                                      const pos &action,
                                      const std::shared_ptr<UltimateTicTacToeGame> &next_environment,
                                      double reward) {
  auto features = this->feature_extractor.GetFeatures(environment);
  if (this->weights.size() == 0) {
    this->weights.resize(features.size());
  }
  for (size_t i = 0; i < features.size(); ++i) {
    double difference = 0;
    if (next_environment->IsTerminal()) {
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

pos ApproximateQAgent::GetBestAction(const std::shared_ptr<UltimateTicTacToeGame> &environment) {
  pos best_action(-1, -1);
  double best_q_value = -1e20;

  auto possible_actions = environment->GetPossibleActions();
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

pos ApproximateQAgent::GetAction(const std::shared_ptr<UltimateTicTacToeGame> &environment) {
  if (this->rng.NextDouble() < this->exploration_rate) {
    auto possible_actions = environment->GetPossibleActions();
    if (possible_actions.empty())
      assert("The state is terminal. No action exists.");
    return possible_actions[rng.NextInt(0, (int)possible_actions.size() - 1)];
  } else {
    return this->GetBestAction(environment);
  }
}

void ApproximateQAgent::dumpWeights() {
  std::ofstream file("/home/dima/Projects/theaigames/tictactoe/rl/weights.txt", std::ios::app);
  for (size_t i = 0; i < this->weights.size(); ++i) {
    file << this->weights[i];
    if (i + 1 == this->weights.size())
      file << "\n";
    else
      file << " ";
  }
  file.close();
}
