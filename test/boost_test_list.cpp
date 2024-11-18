#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "../include/list.h"

BOOST_AUTO_TEST_CASE(SinglyLinkedList_Test) {
    SinglyLinkedList sList;

    BOOST_CHECK(sList.isEmpty());
    BOOST_CHECK_EQUAL(sList.getSize(), 0);
    
    sList.pushFront("1");
    sList.pushFront("2");
    sList.pushFront("3");
    BOOST_CHECK_EQUAL(sList.getSize(), 3);
    
    BOOST_CHECK(sList.find("1"));
    BOOST_CHECK(sList.find("2"));
    BOOST_CHECK(sList.find("3"));
    BOOST_CHECK(!sList.find("4"));

    sList.pushBack("4");
    sList.pushBack("5");
    sList.pushBack("6");
    BOOST_CHECK_EQUAL(sList.getSize(), 6);
    
    BOOST_CHECK(sList.find("4"));
    BOOST_CHECK(sList.find("5"));
    BOOST_CHECK(sList.find("6"));
    BOOST_CHECK(!sList.find("7"));

    sList.popFront();
    BOOST_CHECK_EQUAL(sList.getSize(), 5);
    BOOST_CHECK(!sList.find("3"));

    sList.popBack();
    BOOST_CHECK_EQUAL(sList.getSize(), 4);
    BOOST_CHECK(!sList.find("6"));

    sList.removeAt("4");
    BOOST_CHECK_EQUAL(sList.getSize(), 3);
    BOOST_CHECK(!sList.find("4"));

    sList.clearSList();
    BOOST_CHECK_EQUAL(!sList.getSize(), 0);
    BOOST_CHECK(!sList.find("1"));
}
