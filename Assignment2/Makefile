CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I/usr/include/eigen3 -O3 -march=native -fopenmp-simd
LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
TEST_DIR = tests

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/gauss.cpp
TEST_SRCS = $(TEST_DIR)/test_gauss.cpp $(SRC_DIR)/gauss.cpp

TARGET = gauss
TEST_TARGET = test_gauss

all: $(TARGET) test

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) 

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o result.csv

memcheck: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY: all clean test run memcheck
