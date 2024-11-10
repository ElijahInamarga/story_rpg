# Makefile for building the Text-Based RPG

CXX = g++                              # Compiler to use
CXXFLAGS = -Wall -Wextra -g -std=c++11 # Compiler flags to enable warnings and C++11

# Define the target executable
TARGET = main

# Define the object files
OBJS = main.o                          # List of object files

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile the main source file into an object file
main.o: main.cpp GameDecisionTree.h Node.h Story.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean the build files
clean:
	rm -f $(TARGET) $(OBJS)
