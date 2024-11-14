#!/bin/bash

# Check if the executable 'main' already exists and remove it
if [ -f main ]; then
    echo "Removing existing executable 'main'."
    rm main
fi

# Compile the C++ program  -fsanitize=undefined 
g++ -fsanitize=address -std=c++17 -I "./test"  -I "./include" -I "./include/tensor" -I "./include/sformat" -I "./include/ann" -I "./demo" $(find ./src/ann/ -type f -iregex ".*.cpp") ./src/tensor/*.cpp main.cpp test/unit_test/loss/unit_test_CrossEntropy.cpp -o main -DTEST_LOSS