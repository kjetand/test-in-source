import app;

#ifdef APP_BUILD_TESTS
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#else
int main() { return app::main(); }
#endif