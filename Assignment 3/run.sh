#!/bin/bash

# Check if the executable 'main' already exists and remove it
if [ -f main ]; then
    echo "Removing existing executable 'main'."
    rm main
fi

# Compile the C++ program  -fsanitize=undefined 

g++ -fsanitize=address -fsanitize=undefined -std=c++17 -o main -Iinclude -Itest main.cpp test/unit_test/graph/unit_test.cpp test/unit_test/graph/test/*.cpp -DTEST_GRAPH

# g++ -fsanitize=address -fsanitize=undefined -std=c++17 -o main -Iinclude -Itest main.cpp test/unit_test/sort_topo/unit_test.cpp test/unit_test/sort_topo/test/*.cpp  -DTEST_SORT_TOPO