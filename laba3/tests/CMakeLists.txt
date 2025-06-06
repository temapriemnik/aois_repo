cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)

add_executable(logic_tests
    main_test.cpp
    ${CMAKE_SOURCE_DIR}/src/Lexer.cpp
    ${CMAKE_SOURCE_DIR}/src/ShuntingYard.cpp
    ${CMAKE_SOURCE_DIR}/src/Evaluator.cpp
    ${CMAKE_SOURCE_DIR}/src/TruthTableGenerator.cpp
    ${CMAKE_SOURCE_DIR}/src/NormalFormBuilder.cpp
    ${CMAKE_SOURCE_DIR}/src/QuineMcCluskey.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils.cpp
)

target_link_libraries(logic_tests
    GTest::GTest
    GTest::Main
    pthread
    gcov
)

include(GoogleTest)
gtest_discover_tests(logic_tests)