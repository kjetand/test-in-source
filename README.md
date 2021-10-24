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

## Supported platforms

Code was successfully built and run on the following platforms:

| OS            | Compiler           |  Generator                     |
|---------------|--------------------|--------------------------------|
| Windows 10/11 | `MSVC 14.29.30133` | `CodeBlocks - NMake Makefiles` |
| Ubuntu        | `GCC 11.0.1`       | `CodeBlocks - Unix Makefiles`  |

> **WARNING:** C++20 module support is generally experimental at the time of writing.
> As a consequence, the CMake setup for this project is wired to build modules in order, one at the time.
> E.g. _ninja_ build system will not work.