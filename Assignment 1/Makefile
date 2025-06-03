CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

SRC_DIR = src
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/ascii85.cpp

TARGET = ascii85

all: $(TARGET) run_tests

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

TEST_DIR = tests
TEST_TARGET = test_ascii85
TEST_SRCS = $(TEST_DIR)/test_ascii85.cpp $(SRC_DIR)/ascii85.cpp

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $^ -lgtest -lgtest_main -pthread -o $@


run_tests: $(TARGET)
	python3 $(TEST_DIR)/test.py


clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all clean run_tests test
