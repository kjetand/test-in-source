module;

#include <fmt/format.h>

export module app;

import math;

namespace app {

export int main() {
  fmt::print("2 + 3 equals {}", math::add(2, 3));
  return 0;
}

}  // namespace app