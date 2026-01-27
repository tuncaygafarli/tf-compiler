#!/bin/bash

g++ -std=c++17 -g main.cpp vyne/lexer/lexer.cpp vyne/parser/parser.cpp vyne/ast/ast.cpp -o vyne -Wall -Wextra

if [ $? -ne 0 ]; then
    echo "Build Failed!"
    exit 1
else
    echo "Build Successful: vyne created."
fi
