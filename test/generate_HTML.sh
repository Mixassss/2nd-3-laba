#!/bin/bash

# Компилируем тесты с поддержкой покрытия
g++ -g -O0 --coverage -o boost_test_array boost_test_array.cpp
g++ -g -O0 --coverage -o boost_test_list boost_test_list.cpp
g++ -g -O0 --coverage -o boost_test_stack boost_test_stack.cpp
g++ -g -O0 --coverage -o boost_test_queue boost_test_queue.cpp
g++ -g -O0 --coverage -o boost_test_hash boost_test_hash.cpp
g++ -g -O0 --coverage -o boost_test_tree boost_test_tree.cpp

# Запускаем тесты
./boost_test_array
./boost_test_list
./boost_test_stack
./boost_test_queue
./boost_test_hash
./boost_test_tree


# Генерируем отчет о покрытии
lcov --capture --directory . --output-file coverage.info --rc geninfo_unexecuted_blocks=1 --ignore-errors inconsistent

# Генерируем HTML-отчет
genhtml coverage.info --output-directory coverage_html

# Удаляем лишнее
rm coverage.info
rm boost_test_array boost_test_array.gcda boost_test_array.gcno
rm boost_test_list boost_test_list.gcda boost_test_list.gcno
rm boost_test_stack boost_test_stack.gcda boost_test_stack.gcno
rm boost_test_queue boost_test_queue.gcda boost_test_queue.gcno
rm boost_test_hash boost_test_hash.gcda boost_test_hash.gcno
rm boost_test_tree boost_test_tree.gcda boost_test_tree.gcno

# Открываем отчет
xdg-open coverage_html/index.html