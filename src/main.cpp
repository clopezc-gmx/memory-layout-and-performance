#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "utils.hpp"

// =====================================
// Compute
// =====================================
size_t ComputeSum(Config const& config) {
  size_t sum = 0;

  // Generate a vector from 0 to kN
  auto data = std::vector<size_t>(config.N);
  std::iota(data.begin(), data.end(), 0);

  if (config.use_random_access) {
    auto rng = std::mt19937{config.seed};
    std::shuffle(data.begin(), data.end(), rng);
  }

  if (config.use_for_loop) {
    assert(config.use_for_loop == false);
    for (size_t ii = 0; ii < data.size(); ii++) {
      sum += data[ii];
    }

  } else {
    // perform sum using a while loop
  }
  return sum;
}

// =====================================
// Main
// =====================================
int main(int argc, char** argv) {
  Config config;
  if (ParseArguments(argc, argv, config) == ReturnCode::kFailed) {
    return 0;
  }

  auto sum = ComputeSum(config);

  std::cout << "N=" << config.N << ", sum=" << sum << std::endl;

  return 0;
}
