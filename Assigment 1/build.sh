#!/bin/bash


if [ ! -f "src/ascii85.cpp" ] || [ ! -f "src/main.cpp" ]; then
    echo "Ошибка: исходные файлы не найдены в папке src/"
    exit 1
fi


if [ ! -f "ascii85" ] || [ "src/ascii85.cpp" -nt "ascii85" ] || [ "src/main.cpp" -nt "ascii85" ]; then
    echo "Компиляция ascii85..."
    g++ -std=c++17 -Wall -Wextra -I./src src/main.cpp src/ascii85.cpp -o ascii85
    
    if [ $? -ne 0 ]; then
        echo "Ошибка компиляции!"
        exit 1
    fi
    
    chmod +x ascii85
    echo "Программа успешно скомпилирована"
fi


./ascii85 "$@"
