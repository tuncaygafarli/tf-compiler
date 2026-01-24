@echo off
g++ -std=c++17 main.cpp lexer/lexer.cpp parser/parser.cpp ast/ast.cpp -o tf-compiler.exe
if %errorlevel% neq 0 (
    echo Build Failed!
    pause
) else (
    echo Build Successful: tf-compiler.exe created.
)
