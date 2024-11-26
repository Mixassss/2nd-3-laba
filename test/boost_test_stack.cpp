#define BOOST_TEST_MODULE StackTest
#include <boost/test/included/unit_test.hpp>
#include "../include/stack.h"

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

BOOST_AUTO_TEST_CASE(Stack_Test) {
    Timer timer;
    timer.start();
    Stack stack;

    BOOST_CHECK(stack.isEmpty());
    BOOST_CHECK_EQUAL(stack.size(), 0);

    stack.push("1");
    BOOST_CHECK_EQUAL(stack.size(), 1);
    BOOST_CHECK(!stack.isEmpty());
    BOOST_CHECK_EQUAL(stack.peek(), "1");
    stack.push("2");
    BOOST_CHECK_EQUAL(stack.size(), 2);
    BOOST_CHECK_EQUAL(stack.peek(), "2");

    BOOST_CHECK_EQUAL(stack.pop(), "2");
    BOOST_CHECK_EQUAL(stack.size(), 1);
    BOOST_CHECK_EQUAL(stack.pop(), "1");
    BOOST_CHECK(stack.isEmpty());

    cout << "Stack test: empty, push, size, peek, pop: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Stack_Test_Underflow) {
    Timer timer;
    timer.start();
    Stack stack;

    BOOST_CHECK_THROW(stack.pop(), underflow_error);
    BOOST_CHECK_THROW(stack.peek(), underflow_error);

    cout << "Stack test underflow:  " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(StackOverflow) {
    Timer timer;
    timer.start();
    Stack stack(2);
    
    stack.push("1");
    stack.push("2");

    BOOST_CHECK_THROW(stack.push("3"), overflow_error);

    cout << "Stack test overflow:  " << timer.elapsed() << " seconds" << endl;
}