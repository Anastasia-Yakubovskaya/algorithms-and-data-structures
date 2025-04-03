# Компилятор
CXX = g++
# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
# Исходные файлы
SRC_DIR = ./src
TEST_DIR = ./tests

# Цели по умолчанию
all: work1 run_tests

# Сборка основной программы
work1: $(SRC_DIR)/main.cpp $(SRC_DIR)/ASCII_85.cpp
	$(CXX) $(CXXFLAGS) $^ -o work1

# Сборка тестов (если необходимо)
test: $(TEST_DIR)/test_ascii85.cpp $(SRC_DIR)/ASCII_85.cpp
	$(CXX) $(CXXFLAGS) $^ -lgtest -lgtest_main -pthread -o test

# Очистка
clean:
	rm -f work1 test

# Запуск тестов на Python
run_tests: work1  # Убедитесь, что основная программа собрана перед запуском тестов
	python3 $(TEST_DIR)/test.py

.PHONY: all clean run_tests test
