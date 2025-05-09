# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I/usr/include/eigen3

# Пути для исходников
SRC_DIR = src
TEST_DIR = tests

# Исходные файлы
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/gauss.cpp

# Имена исполняемых файлов
TARGET = gauss
TEST_TARGET = test_gauss

# Основные цели
all: $(TARGET) test

# Сборка основной программы
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

.PHONY: all clean test run run_py_tests
