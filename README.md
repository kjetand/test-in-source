# test-in-source

Strategy for unit tests together with your C++ source code (using C++20 modules). See article explaining the
technique [here](https://kjetand.github.io/programming/c++20/modules/2021/10/12/test-in-source.html).

## Build instructions

```shell
# 1) Clone from git
$ git clone --recursive https://github.com/kjetand/test-in-source
$ cd test-in-source

# 2.1) Build application
$ cmake -B build
# ... or ...
# 2.2) build test suite
$ cmake -B build -DAPP_BUILD_TESTS=ON

# Build code and run code
$ cmake --build build --target run
```