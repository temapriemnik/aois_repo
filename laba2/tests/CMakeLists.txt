cmake_minimum_required(VERSION 3.14)
project(logic_tests)

set(CMAKE_CXX_STANDARD 17)

# Включаем флаги покрытия
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

include_directories(SYSTEM /usr/include/gtest)
link_directories(/usr/lib)

add_executable(logic_tests
    ../src/Lexer.cpp
    ../src/ShuntingYard.cpp
    ../src/Evaluator.cpp
    ../src/TruthTableGenerator.cpp
    ../src/NormalFormBuilder.cpp
    main_test.cpp
)

target_link_libraries(logic_tests gtest gtest_main pthread gcov)