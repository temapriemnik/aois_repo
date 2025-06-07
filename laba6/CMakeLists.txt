cmake_minimum_required(VERSION 3.10)
project(hash_table_avl)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
# Main library
add_library(hash_table_avl 
    src/avl_tree.cpp
    src/hash_table.cpp
)

# Main executable
add_executable(hash_table_app src/main.cpp)
target_link_libraries(hash_table_app hash_table_avl)

# Tests
enable_testing()
add_subdirectory(tests)

# Coverage setup
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)

if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Setting up code coverage")
        
        # Compiler flags
        add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
        add_link_options(--coverage)
        
        # Find tools
        find_program(LCOV lcov)
        find_program(GENHTML genhtml)
        find_program(GCOVR gcovr)
        
        if(LCOV AND GENHTML AND GCOVR)
            add_custom_target(coverage
                # Reset counters
                COMMAND ${LCOV} --directory . --zerocounters
                # Run tests
                COMMAND ctest --output-on-failure
                # Capture data
                COMMAND ${LCOV} --capture --directory . --output-file lcov.info
                # Filter data
                COMMAND ${LCOV} --remove lcov.info '*/usr/*' '*/tests/*' '*/include/*' --output-file lcov-filtered.info
                # Generate HTML
                COMMAND ${GENHTML} lcov-filtered.info --output-directory coverage
                # Generate GCOVR report
                COMMAND ${GCOVR} -r ${CMAKE_SOURCE_DIR} --exclude-unreachable-branches --exclude-throw-branches --html-details -o coverage.html
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Generating coverage reports"
            )
        else()
            message(WARNING "Coverage tools not found - lcov: ${LCOV}, genhtml: ${GENHTML}, gcovr: ${GCOVR}")
        endif()
    endif()
endif()