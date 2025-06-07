#!/bin/bash

# Переходим в директорию проекта
cd "$(dirname "$0")" || exit

# Очищаем предыдущую сборку
echo "Очистка предыдущей сборки..."
rm -rf build
mkdir -p build
cd build || exit

# Генерируем Makefile
echo "Генерация Makefile..."
cmake .. || { echo "Ошибка CMake!"; exit 1; }

# Компилируем проект
echo "Компиляция проекта..."
make -j$(nproc) || { echo "Ошибка компиляции!"; exit 1; }

# Запускаем основное приложение (если есть)
if [ -f "hash_table_app" ]; then
    echo -e "\nЗапуск основного приложения:"
    ./hash_table_app
fi

# Запускаем тесты
echo -e "\nЗапуск тестов:"
if [ -f "tests/test_avl_tree" ] && [ -f "tests/test_hash_table" ]; then
    # Вариант 1: через ctest
    echo "Вариант 1 - через ctest:"
    ctest --output-on-failure
    
    # Вариант 2: прямое выполнение тестов
    echo -e "\nВариант 2 - прямой запуск:"
    ./tests/test_avl_tree
    ./tests/test_hash_table
else
    echo "Тестовые исполняемые файлы не найдены!"
    exit 1
fi

echo -e "\nВсе операции завершены успешно!"
exit 0