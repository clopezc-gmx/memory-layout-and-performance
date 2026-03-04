#include "utils.hpp"

#include <cassert>
#include <iostream>
#include <new>

#include "lyra/args.hpp"
#include "lyra/arguments.hpp"
#include "lyra/cli.hpp"
#include "lyra/opt.hpp"
#include "lyra/parser.hpp"

ReturnCode ParseArguments(int argc, char** argv, Config& config) {
  auto cli =
      lyra::cli() |
      lyra::opt(config.size_in_bytes, "bytes")["--size"]("Size in bytes") |
      lyra::opt(config.use_random_access,
                "bool")["--random-access"]("Use random access pattern") |
      lyra::opt(config.use_for_loop,
                "bool")["--for-loop"]("Use for-loop implementation") |
      lyra::opt(config.seed, "int")["--seed"]("Random seed");

  auto result = cli.parse({argc, argv});
  if (!result) {
    std::cerr << result.message() << "\n";
    return ReturnCode::kFailed;
  }

  assert(config.size_in_bytes % sizeof(size_t) == 0);  // exact multiple
  auto N = config.size_in_bytes / sizeof(size_t);      // exact element count
  assert(N > 0 && N <= kMaxN);                         // bounded
  config.N = N;

  config.cache_line_size = std::hardware_destructive_interference_size;

  //
  return ReturnCode::kSuccess;
}
