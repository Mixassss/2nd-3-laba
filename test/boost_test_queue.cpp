#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "../include/queue.h"

BOOST_AUTO_TEST_CASE(Queue_Test) {
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
}

BOOST_AUTO_TEST_CASE(Queue_Constructor_Test) {
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
}