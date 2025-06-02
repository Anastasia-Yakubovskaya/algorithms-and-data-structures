#!/bin/bash

g++ -std=c++17 -Wall -Wextra -I./src -I/usr/include/eigen3 -O3 -march=native \
    src/main.cpp src/gauss.cpp -o gauss -fopenmp-simd

if [ $? -eq 0 ]; then
    chmod +x gauss
else
    exit 1
fi

g++ -std=c++17 -Wall -Wextra -I./src -I/usr/include/eigen3 -O3 -march=native \
    tests/test_gauss.cpp src/gauss.cpp -o test_gauss -lgtest -lgtest_main -pthread -fopenmp-simd

if [ $? -eq 0 ]; then
    chmod +x test_gauss
else
    exit 1
fi


