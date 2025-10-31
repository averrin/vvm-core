#!/bin/bash
# Build script for VVM Core on Unix-like systems

echo "VVM Core Build Script"
echo "====================="
echo ""

# Check for CMake
if command -v cmake &> /dev/null; then
    echo "Found CMake, using CMake build..."
    mkdir -p build
    cd build
    cmake ..
    cmake --build .
    cd ..
    echo ""
    echo "Build complete! Executable: build/vvm_test"
    exit 0
fi

# Check for g++
if command -v g++ &> /dev/null; then
    echo "Found g++, using Makefile..."
    make
    echo ""
    echo "Build complete! Executable: vvm_test"
    exit 0
fi

# Check for clang++
if command -v clang++ &> /dev/null; then
    echo "Found clang++, using Makefile with clang..."
    make CXX=clang++
    echo ""
    echo "Build complete! Executable: vvm_test"
    exit 0
fi

echo "ERROR: No C++ compiler found!"
echo ""
echo "Please install one of the following:"
echo "  - g++ (GNU C++ compiler)"
echo "  - clang++ (LLVM C++ compiler)"
echo "  - CMake with a compiler"
echo ""
exit 1
