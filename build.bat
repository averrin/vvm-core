@echo off
REM Build script for VVM Core on Windows

echo VVM Core Build Script
echo =====================
echo.

REM Check for CMake
where cmake.exe >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Found CMake, using CMake build...
    if not exist build mkdir build
    cd build
    cmake ..
    cmake --build .
    cd ..
    echo.
    echo Build complete! Executable: build\Debug\vvm_test.exe or build\vvm_test.exe
    goto :end
)

REM Check for g++
where g++.exe >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Found g++, using Makefile...
    make
    echo.
    echo Build complete! Executable: vvm_test.exe
    goto :end
)

REM Check for MSVC (cl.exe)
where cl.exe >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Found MSVC, compiling manually...
    cl.exe /EHsc /std:c++17 /Iinclude /Ideps test_main.cpp src\core.cpp src\analyzer.cpp src\debug.cpp src\functions.cpp src\memory_container.cpp deps\format.cc /Fe:vvm_test.exe
    echo.
    echo Build complete! Executable: vvm_test.exe
    goto :end
)

echo ERROR: No C++ compiler found!
echo.
echo Please install one of the following:
echo   1. MinGW-w64 (includes g++)
echo   2. Visual Studio (includes MSVC)
echo   3. CMake with a compiler
echo.
echo You can install MinGW-w64 from: https://www.mingw-w64.org/
echo Or install Visual Studio Community from: https://visualstudio.microsoft.com/
echo.

:end
