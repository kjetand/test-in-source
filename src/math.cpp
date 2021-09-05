module;

#include "test.hpp"

export module math;

namespace math {

export int add(const int a, const int b) { return a + b; }

int multiply(const int n, const int x) { return n * x; }

}  // namespace math

UNIT_TESTS(
    TEST_CASE("Two plus three equals five", "[math]") {
      REQUIRE(math::add(2, 3) == 5);
    }

    TEST_CASE("Two times three equals six", "[math]") {
      REQUIRE(math::multiply(2, 3) == 6);
    })