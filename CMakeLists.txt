cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

option(APP_BUILD_TESTS "Build tests" OFF)

if (APP_BUILD_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif ()

project(test-in-source LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if (APP_BUILD_TESTS)
    message(STATUS "Building project as unit test suite")
    add_definitions(-DAPP_BUILD_TESTS)
    find_package(Catch2 CONFIG REQUIRED)
endif ()

find_package(fmt CONFIG REQUIRED)

add_subdirectory(src)
