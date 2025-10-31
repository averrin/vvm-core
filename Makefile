# Makefile for vvm-core test executable

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ideps
LDFLAGS =

# Source files
VVM_SOURCES = src/core.cpp src/analyzer.cpp src/debug.cpp src/functions.cpp src/memory_container.cpp deps/format.cc
VVM_OBJECTS = $(VVM_SOURCES:.cpp=.o)
VVM_OBJECTS := $(VVM_OBJECTS:.cc=.o)

# Target executable
TARGET = vvm_test

.PHONY: all clean run

all: $(TARGET)

$(TARGET): test_main.o $(VVM_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) test_main.o $(VVM_OBJECTS)

run: $(TARGET)
	./$(TARGET)
