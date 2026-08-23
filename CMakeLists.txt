cmake_minimum_required(VERSION 3.10)

project(Compiler C)

add_executable(Compiler
    main.c
    lexer.c
)

add_executable(LexerTest
    tests/lexer_test.c
    lexer.c
)