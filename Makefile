# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

# Имя исполняемого файла
TARGET = work1

# Исходные файлы
SRCS = main.cpp ASCII_85.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Правило для компиляции .cpp файлов в .o
%.o: %.cpp ASCII_85.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Псевдоцель для предотвращения конфликтов с файлами
.PHONY: all clean
