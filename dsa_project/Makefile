# Makefile for DSA Shopping Project

CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./src

SRC_DIR = src
BUILD_DIR = build
BIN = shopping_app

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(BIN)

# Link all object files into final binary
$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp file into .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN)

# Run the program
run: all
	./$(BIN)
