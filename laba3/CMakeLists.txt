cmake_minimum_required(VERSION 3.14)
project(logic_minimizer)

set(CMAKE_CXX_STANDARD 17)

# Основной бинарник в корень
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    # Тестовый бинарник тоже в корень
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
endif()