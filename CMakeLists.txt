cmake_minimum_required(VERSION 3.10)

project(Compiler C)

add_executable(Compiler
    main.c
    lexer.c
)

enable_testing()

add_executable(test_process
    tests/test_process.c
    lexer.c
)

add_executable(run_lexer_tests
    tests/run_lexer_tests.c
    tests/test_lexer.c
    lexer.c
)

add_test(NAME process_test COMMAND test_process)
add_test(NAME lexer_test COMMAND run_lexer_tests)