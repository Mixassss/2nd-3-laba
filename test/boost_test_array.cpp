#define BOOST_TEST_MODULE ArrayTest
#include <boost/test/included/unit_test.hpp>
#include "../include/arr.h"

BOOST_AUTO_TEST_CASE(Array_Test) {
    Array arr;

    arr.addToEnd("1");
    arr.addToEnd("2");
    arr.addToEnd("3");
    arr.addToEnd("4");
    BOOST_CHECK_EQUAL(arr.getSize(), 4);

    BOOST_CHECK(arr.find("1"));
    BOOST_CHECK(arr.find("2"));
    BOOST_CHECK(arr.find("3"));
    BOOST_CHECK(arr.find("4"));
    BOOST_CHECK(!arr.find("5"));

    arr.addAtIndex(0, "5");
    arr.addAtIndex(1, "6");
    arr.addAtIndex(2, "7");
    BOOST_CHECK_EQUAL(arr.getSize(), 7);

    BOOST_CHECK(arr.find("5"));
    BOOST_CHECK(arr.find("6"));
    BOOST_CHECK(arr.find("7"));
    BOOST_CHECK(!arr.find("8"));

    BOOST_CHECK_EQUAL(arr.getIndex(0), "5");
    BOOST_CHECK_EQUAL(arr.getIndex(2), "7");
    BOOST_CHECK_EQUAL(arr.getIndex(5), "3");
    BOOST_CHECK_EQUAL(arr.getIndex(6), "4");

    arr.removeAtIndex(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 6);
    BOOST_CHECK(!arr.find("5"));

    arr.removeAtIndex(3);  // Удаляем элемент с индексом 3
    BOOST_CHECK_EQUAL(arr.getSize(), 5);
    BOOST_CHECK(!arr.find("1"));

    arr.replaceAtIndex(0, "8");
    BOOST_CHECK_EQUAL(arr.getIndex(0), "8");

    BOOST_CHECK_NO_THROW(arr.getIndex(10)); // Проверка выброса исключения
    BOOST_CHECK_THROW(arr.getIndex(10), out_of_range);

    // Очистка элементов массива
    arr.removeAtIndex(0);
    arr.removeAtIndex(0);
    arr.removeAtIndex(0);
    arr.removeAtIndex(0);
    arr.removeAtIndex(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 0);

    // Тестируем повторное удаление
    BOOST_CHECK_THROW(arr.removeAtIndex(0), out_of_range);
}

BOOST_AUTO_TEST_CASE(Array_Additional_Test) {
    Array arr;

    // Проверка на удаление из пустого массива
    arr.removeAtIndex(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 0);

    // Проверка добавления за пределами
    arr.addAtIndex(0, "1");   // Добавление первого элемента
    BOOST_CHECK_EQUAL(arr.getSize(), 1);
    BOOST_CHECK_EQUAL(arr.getIndex(0), "1");

    // Проверка на добавление по индексу, который больше размера
    arr.addAtIndex(10, "2"); // Игнорируется
    BOOST_CHECK_EQUAL(arr.getSize(), 1);

    // Проверка замены на пустом массиве, потом на валидном
    arr.replaceAtIndex(0, "3");
    BOOST_CHECK_EQUAL(arr.getIndex(0), "3");
    arr.replaceAtIndex(10, "4"); // Игнорируется
    BOOST_CHECK_EQUAL(arr.getSize(), 1);
}