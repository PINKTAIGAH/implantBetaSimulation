# Project settings
TARGET := bin/implantBetaSimulation
SRC_DIR := src
INC_DIR := include

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cxx)
OBJS := $(SRCS:$(SRC_DIR)/%.cxx=build/%.o)

# Compiler and flags
CXX := g++
CXXFLAGS := -O2 -std=c++17 -I$(INC_DIR) $(shell root-config --cflags)
LDFLAGS := $(shell root-config --libs)

# Build directory
BUILD_DIR := build

# Default target
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@$(CXX) $^ -o $@ $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cxx
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean