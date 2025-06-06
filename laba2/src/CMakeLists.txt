cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 14)

# Укажите все исходные файлы
set(SOURCES
    Evaluator.cpp
    Lexer.cpp
    NormalFormBuilder.cpp
    ShuntingYard.cpp
    TruthTableGenerator.cpp
    main.cpp
)

# Создаём исполняемый файл
add_executable(main ${SOURCES})

