cmake_minimum_required(VERSION 3.14)
project(logic_minimizer)

set(CMAKE_CXX_STANDARD 17)

add_executable(logic_minimizer
    src/main.cpp
    src/Lexer.cpp
    src/ShuntingYard.cpp
    src/Evaluator.cpp
    src/TruthTableGenerator.cpp
    src/NormalFormBuilder.cpp
    src/QuineMcCluskey.cpp
    src/Utils.cpp
)

include_directories(src/)