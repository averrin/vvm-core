cmake_minimum_required(VERSION 3.10)
project(vvm-core VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/deps
)

# Source files
set(VVM_SOURCES
    src/core.cpp
    src/analyzer.cpp
    src/debug.cpp
    src/functions.cpp
    src/memory_container.cpp
    deps/format.cc
)

# Create library
add_library(vvm STATIC ${VVM_SOURCES})

# Test executable
add_executable(vvm_test test_main.cpp)
target_link_libraries(vvm_test vvm)

# Set output directory
set_target_properties(vvm_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
