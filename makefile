# Compiler
CXX = g++

# Qt tools
QMAKE = qmake
UIC = uic
MOC = moc
RCC = rcc

# Qt5 settings
QT_INCPATH = /usr/include/x86_64-linux-gnu/qt5
QT_LIBPATH = /usr/lib/x86_64-linux-gnu
QT_LIBS = -lQt5Widgets -lQt5Gui -lQt5Core

# Project name
TARGET = tree
TEST_TARGET = test

# Sources and headers
SOURCES = $(filter-out test.cpp, $(wildcard *.cpp))
HEADERS = $(wildcard *.hpp)

#Sources for test
TEST_SOURCES = $(wildcard *.cpp)

# Output directory
BUILD_DIR = build

# Output binary
BINARY = $(BUILD_DIR)/$(TARGET)
TEST_BINARY = $(BUILD_DIR)/$(TEST_TARGET)

# Compiler flags
CXXFLAGS = -I$(QT_INCPATH) -I$(QT_INCPATH)/QtWidgets -I$(QT_INCPATH)/QtGui -I$(QT_INCPATH)/QtCore -std=c++14 -fPIC -Wall -Wextra
LDFLAGS = -L$(QT_LIBPATH) $(QT_LIBS)

# Default target
all: $(BUILD_DIR) $(BINARY)

# Create build directory if it does not exist
$(BUILD_DIR):
	 mkdir -p $(BUILD_DIR)

# Rule to create object files
OBJS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

# Rule to create object files for test
TEST_OBJS = $(TEST_SOURCES:%.cpp=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build the project
$(BINARY): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY) $(LDFLAGS)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Run the program
tree1: all
	./$(BINARY) tree1

tree2: all
	./$(BINARY) tree2

tree3: all
	./$(BINARY) tree3

complex: all
	./$(BINARY) complex

# Build and run the test binary
test: $(TEST_BINARY)
	./$(TEST_BINARY)

$(TEST_BINARY): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST_BINARY) $(LDFLAGS)

.PHONY: all clean tree complex test