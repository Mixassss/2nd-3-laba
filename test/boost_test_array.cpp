#define BOOST_TEST_MODULE ArrayTest
#include <boost/test/included/unit_test.hpp>
#include "../include/arr.h"


class Timer { // Класс для измерения времени выполнения
    chrono::time_point<chrono::steady_clock> start_time; 
public:
    void start() {
        start_time = chrono::steady_clock::now(); // Запускаем таймер
    }

    double elapsed() {
        auto end_time = chrono::steady_clock::now(); // Получаем текущее время
        chrono::duration<double> duration = end_time - start_time; // Вычисляем продолжительность
        return duration.count(); // Возвращаем продолжительность в секундах
    }
};

BOOST_AUTO_TEST_CASE(Array_Test_Push) {
    Timer timer;
    timer.start();
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

    BOOST_CHECK_EQUAL(arr.getIndex(0), "1");
    BOOST_CHECK_EQUAL(arr.getIndex(1), "2");
    BOOST_CHECK_EQUAL(arr.getIndex(2), "3");
    BOOST_CHECK_EQUAL(arr.getIndex(3), "4");

    arr.removeAtIndex(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 3);
    BOOST_CHECK(!arr.find("1"));

    arr.removeAtIndex(2);
    BOOST_CHECK_EQUAL(arr.getSize(), 2);
    BOOST_CHECK(!arr.find("4"));

    arr.replaceAtIndex(0, "10");
    BOOST_CHECK_EQUAL(arr.getIndex(0), "10");

    // Очистка элементов массива
    arr.removeAtIndex(0);
    arr.removeAtIndex(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 0);

    cout << "Array push test time: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Array_Additional_Test) {
    Timer timer;
    timer.start();
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

    cout << "Array additional test time: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Array_Test_Index) {
    Timer timer;
    timer.start();
    Array arr;

    arr.addAtIndex(0, "5");
    arr.addAtIndex(1, "6");
    arr.addAtIndex(2, "7");
    arr.addAtIndex(3, "8");
    BOOST_CHECK_EQUAL(arr.getSize(), 4);

    BOOST_CHECK(arr.find("5"));
    BOOST_CHECK(arr.find("6"));
    BOOST_CHECK(arr.find("7"));
    BOOST_CHECK(arr.find("8"));
    BOOST_CHECK(!arr.find("9"));

    BOOST_CHECK_EQUAL(arr.getIndex(0), "5");
    BOOST_CHECK_EQUAL(arr.getIndex(1), "6");
    BOOST_CHECK_EQUAL(arr.getIndex(2), "7");
    BOOST_CHECK_EQUAL(arr.getIndex(3), "8");

    arr.removeAtIndex(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 3);
    BOOST_CHECK(!arr.find("5"));

    arr.removeAtIndex(2);
    BOOST_CHECK_EQUAL(arr.getSize(), 2);
    BOOST_CHECK(!arr.find("8"));

    arr.removeAtIndex(0);
    arr.removeAtIndex(0);
    BOOST_CHECK_EQUAL(arr.getSize(), 0);

    cout << "Array add index test time: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Array_Test_Resize) {
    Timer timer;
    timer.start();
    Array arr;

    // Тестируем добавление элементов, чтобы вызвать resize
    for (size_t i = 1; i <= 15; ++i) {
        arr.addToEnd(to_string(i));
    }

    // Проверяем, что массив увеличился
    BOOST_CHECK_EQUAL(arr.getSize(), 15);  // Убедимся, что все элементы добавлены
    BOOST_CHECK(arr.find("1"));
    BOOST_CHECK(arr.find("15"));

    // Перегружаем ShowArray и проверяем вывод
    stringstream buffer;
    streambuf* previous = cout.rdbuf(buffer.rdbuf()); // Подменяем cout

    arr.ShowArray();

    cout.rdbuf(previous); // Восстанавливаем cout

    string output = buffer.str();
    BOOST_CHECK(output == "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 \n"); // Проверка формата вывода

    cout << "Array resize and showarray test time: " << timer.elapsed() << " seconds" << endl;
}