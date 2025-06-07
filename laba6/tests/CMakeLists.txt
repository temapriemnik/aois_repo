# Добавьте в начало файла
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests
)

add_executable(test_avl_tree test_avl_tree.cpp)
target_link_libraries(test_avl_tree hash_table_avl gtest gtest_main)

add_executable(test_hash_table test_hash_table.cpp)
target_link_libraries(test_hash_table hash_table_avl gtest gtest_main)