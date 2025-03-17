# Компилятор
CXX = g++
# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
# Исходные файлы
SRC_DIR = ./src
TEST_DIR = ./tests

# Цели по умолчанию
all: work1 test

# Сборка основной программы
work1: $(SRC_DIR)/main.cpp $(SRC_DIR)/ASCII_85.cpp
	$(CXX) $(CXXFLAGS) $^ -o work1

# Сборка тестов
test: $(TEST_DIR)/test_ascii85.cpp $(SRC_DIR)/ASCII_85.cpp
	$(CXX) $(CXXFLAGS) $^ -lgtest -lgtest_main -pthread -o test

# Очистка
clean:
	rm -f work1 test

# Запуск тестов
run_tests: test
	./test

.PHONY: all clean run_tests
