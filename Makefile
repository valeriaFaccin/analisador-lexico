CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = slr_compiler
TEST_TARGET = test_slr
COMPLETE_TEST_TARGET = test_complete_slr
COMPILER_TARGET = compiler_main

# Source files
SOURCES = main.cpp transicoes.cpp tabela_slr.cpp
TEST_SOURCES = test_slr.cpp transicoes.cpp tabela_slr.cpp
COMPLETE_TEST_SOURCES = test_complete_slr.cpp transicoes.cpp tabela_slr.cpp
COMPILER_SOURCES = compiler_main.cpp transicoes.cpp tabela_slr.cpp symbol_table.cpp parser.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
COMPLETE_TEST_OBJECTS = $(COMPLETE_TEST_SOURCES:.cpp=.o)
COMPILER_OBJECTS = $(COMPILER_SOURCES:.cpp=.o)

# Default target
all: $(TARGET) $(TEST_TARGET) $(COMPLETE_TEST_TARGET) $(COMPILER_TARGET)

# Main target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Test target
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS)

# Complete test target
$(COMPLETE_TEST_TARGET): $(COMPLETE_TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(COMPLETE_TEST_TARGET) $(COMPLETE_TEST_OBJECTS)

# Compiler target
$(COMPILER_TARGET): $(COMPILER_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(COMPILER_TARGET) $(COMPILER_OBJECTS)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(COMPLETE_TEST_OBJECTS) $(COMPILER_OBJECTS)
	rm -f $(TARGET) $(TEST_TARGET) $(COMPLETE_TEST_TARGET) $(COMPILER_TARGET)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

test-complete: $(COMPLETE_TEST_TARGET)
	./$(COMPLETE_TEST_TARGET)

# Run compiler
run: $(COMPILER_TARGET)
	./$(COMPILER_TARGET)

# Run original main
run-original: $(TARGET)
	./$(TARGET)

# Install dependencies (if needed)
install:
	@echo "No external dependencies required for this project."

# Help
help:
	@echo "Available targets:"
	@echo "  all              - Build all targets"
	@echo "  $(TARGET)        - Build original lexical analyzer"
	@echo "  $(TEST_TARGET)   - Build SLR table test"
	@echo "  $(COMPLETE_TEST_TARGET) - Build complete SLR test"
	@echo "  $(COMPILER_TARGET) - Build full compiler"
	@echo "  test             - Run basic SLR tests"
	@echo "  test-complete    - Run complete SLR tests"
	@echo "  run              - Run the full compiler"
	@echo "  run-original     - Run original lexical analyzer"
	@echo "  clean            - Remove all build files"
	@echo "  help             - Show this help message"

# Phony targets
.PHONY: all clean test test-complete run run-original install help 