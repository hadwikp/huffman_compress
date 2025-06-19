cmake_minimum_required(VERSION 3.10)
project(huffman-compress VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build library from source files
add_library(huffman_lib
    src/huffman.cpp
    src/io.cpp
    src/utils.cpp
)
target_include_directories(huffman_lib PUBLIC src)

# Main executable
add_executable(huffman
    src/main.cpp
)
target_link_libraries(huffman PRIVATE huffman_lib)

# Tests (using Catch2)
find_package(Catch2 REQUIRED)
add_executable(tests
    tests/test_codegen.cpp
    tests/test_roundtrip.cpp
)
# Link against Catch2's main library to provide the test runner's main()
target_link_libraries(tests PRIVATE huffman_lib Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE src)

include(CTest)
include(Catch)
catch_discover_tests(tests)
