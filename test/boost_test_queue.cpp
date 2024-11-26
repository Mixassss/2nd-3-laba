#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "../include/queue.h"

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

BOOST_AUTO_TEST_CASE(Queue_Test) {
    Timer timer;
    timer.start();
    Queue queue;

    BOOST_CHECK(queue.isempty());
    BOOST_CHECK_EQUAL(queue.Size(), 0);

    queue.push("1");
    BOOST_CHECK_EQUAL(queue.Size(), 1);
    BOOST_CHECK(!queue.isempty());
    BOOST_CHECK_EQUAL(queue.peek(), "1");

    queue.push("2");
    BOOST_CHECK_EQUAL(queue.Size(), 2);
    BOOST_CHECK_EQUAL(queue.peek(), "1");

    BOOST_CHECK_EQUAL(queue.pop(), "1");
    BOOST_CHECK_EQUAL(queue.Size(), 1);
    BOOST_CHECK_EQUAL(queue.peek(), "2");

    queue.pop();
    BOOST_CHECK(queue.isempty());

    BOOST_CHECK_THROW(queue.pop(), underflow_error);
    BOOST_CHECK_THROW(queue.peek(), underflow_error);

    for (int i = 0; i < 30; ++i) {
        queue.push(to_string(i));
    }
    BOOST_CHECK_THROW(queue.push("overflow"), overflow_error);

    cout << "Queue test time: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Queue_Constructor_Test) {
    Timer timer;
    timer.start();
    Queue customQueue(30);
    
    BOOST_CHECK(customQueue.isempty());
    BOOST_CHECK_EQUAL(customQueue.Size(), 0);
    
    for (int i = 0; i < 30; ++i) {
        customQueue.push(to_string(i));
    }
    
    BOOST_CHECK_EQUAL(customQueue.Size(), 30);
    BOOST_CHECK_THROW(customQueue.push("overflow"), overflow_error);
    
    for (int i = 0; i < 30; ++i) {
        BOOST_CHECK_EQUAL(customQueue.pop(), to_string(i));
    }
    
    BOOST_CHECK(customQueue.isempty());

    cout << "Queue constructor test time: " << timer.elapsed() << " seconds" << endl;
}