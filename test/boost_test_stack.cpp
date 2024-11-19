#define BOOST_TEST_MODULE StackTest
#include <boost/test/included/unit_test.hpp>
#include "../include/stack.h"

BOOST_AUTO_TEST_CASE(Stack_Test) {
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
}

BOOST_AUTO_TEST_CASE(Stack_Test_Underflow) {
    Stack stack;

    BOOST_CHECK_THROW(stack.pop(), underflow_error);
    BOOST_CHECK_THROW(stack.peek(), underflow_error);
}

BOOST_AUTO_TEST_CASE(StackOverflow) {
    Stack stack(2);
    stack.push("1");
    stack.push("2");

    BOOST_CHECK_THROW(stack.push("3"), overflow_error);
}