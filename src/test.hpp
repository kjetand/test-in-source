#pragma once

#ifdef APP_BUILD_TESTS

#include <catch2/catch.hpp>
#define UNIT_TESTS(code) code

#else

#define UNIT_TESTS(code)

#endif