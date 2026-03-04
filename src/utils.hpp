#include <cstddef>
#include <limits>

namespace detail {
// Compute the maximum number of elements in a vector such that the sum still
// fits in size_t. It uses a constexpr binary search with a safe upper bound and
// an overflow-free predicate to evaluate the triangular inequality.
constexpr size_t GetMaxN() {
  constexpr size_t M = std::numeric_limits<size_t>::max();
  size_t low = 0;
  size_t high = size_t{1} << 33ULL;  // > 6e9

  constexpr auto fits = [](size_t n, size_t max) {
    return (n % 2 == 0) ? (n / 2) <= max / (n + 1) : n <= max / ((n + 1) / 2);
  };

  while (low < high) {
    size_t mid = low + ((high - low + 1) / 2);
    if (fits(mid, M)) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }
  return low;
}
}  // namespace detail

constexpr size_t kMaxN = detail::GetMaxN();

enum class ReturnCode {
  kFailed = 1,
  kSuccess = 0,
};

// Configuration
struct Config {
  size_t N = {0};
  size_t cache_line_size = {0};
  size_t size_in_bytes = {0};
  bool use_random_access = {false};
  bool use_for_loop = {false};
  size_t seed = {999};
};

ReturnCode ParseArguments(int argc, char** argv, Config& config);
