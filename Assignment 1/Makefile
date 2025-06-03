# Компилятор
CXX = g++
# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
# Исходные файлы
SRC_DIR = src
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/ascii85.cpp
# Имя исполняемого файла
TARGET = ascii85

# Цели по умолчанию
all: $(TARGET) run_tests

# Сборка основной программы
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Сборка тестов (если используете Google Test)
TEST_DIR = tests
TEST_TARGET = test_ascii85
TEST_SRCS = $(TEST_DIR)/test_ascii85.cpp $(SRC_DIR)/ascii85.cpp

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $^ -lgtest -lgtest_main -pthread -o $@

# Запуск тестов
run_tests: $(TARGET)
	python3 $(TEST_DIR)/test.py

# Очистка
clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all clean run_tests test
