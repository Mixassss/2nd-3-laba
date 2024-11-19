#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "../include/list.h"

BOOST_AUTO_TEST_CASE(SinglyLinkedList_Test_Front) {
    SinglyLinkedList sList;

    BOOST_CHECK(sList.isEmpty());
    BOOST_CHECK_EQUAL(sList.getSize(), 0);
    
    sList.pushFront("1");
    sList.pushFront("2");
    sList.pushFront("3");
    sList.pushFront("4");
    BOOST_CHECK_EQUAL(sList.getSize(), 4);
    
    BOOST_CHECK(sList.find("1"));
    BOOST_CHECK(sList.find("2"));
    BOOST_CHECK(sList.find("3"));
    BOOST_CHECK(sList.find("4"));
    BOOST_CHECK(!sList.find("5"));

    sList.print();
    BOOST_CHECK_EQUAL(sList.getSize(), 4);

    sList.popFront();
    BOOST_CHECK_EQUAL(sList.getSize(), 3);
    BOOST_CHECK(!sList.find("4"));

    sList.popBack();
    BOOST_CHECK_EQUAL(sList.getSize(), 2);
    BOOST_CHECK(!sList.find("1"));

    sList.removeAt("2");
    BOOST_CHECK_EQUAL(sList.getSize(), 1);
    BOOST_CHECK(!sList.find("2"));

    sList.clearSList();
    BOOST_CHECK_EQUAL(sList.getSize(), 0);
    BOOST_CHECK(!sList.find("3"));

    sList.print();
    BOOST_CHECK_EQUAL(sList.getSize(), 0);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedList_Test_Back) {
    SinglyLinkedList sList;

    BOOST_CHECK(sList.isEmpty());
    BOOST_CHECK_EQUAL(sList.getSize(), 0);

    sList.pushBack("4");
    sList.pushBack("5");
    sList.pushBack("6");
    sList.pushBack("7");
    BOOST_CHECK_EQUAL(sList.getSize(), 4);
    
    BOOST_CHECK(sList.find("4"));
    BOOST_CHECK(sList.find("5"));
    BOOST_CHECK(sList.find("6"));
    BOOST_CHECK(sList.find("7"));
    BOOST_CHECK(!sList.find("8"));

    sList.print();
    BOOST_CHECK_EQUAL(sList.getSize(), 4);

    sList.popFront();
    BOOST_CHECK_EQUAL(sList.getSize(), 3);
    BOOST_CHECK(!sList.find("4"));

    sList.popBack();
    BOOST_CHECK_EQUAL(sList.getSize(), 2);
    BOOST_CHECK(!sList.find("7"));

    sList.removeAt("5");
    BOOST_CHECK_EQUAL(sList.getSize(), 1);
    BOOST_CHECK(!sList.find("5"));

    sList.clearSList();
    BOOST_CHECK_EQUAL(sList.getSize(), 0);
    BOOST_CHECK(!sList.find("6"));

    sList.print();
    BOOST_CHECK_EQUAL(sList.getSize(), 0);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedList_Test) {
    DoublyLinkedList dList;

    BOOST_CHECK(dList.isEmpty());
    BOOST_CHECK_EQUAL(dList.getSize(), 0);

    dList.pushFront("1");
    dList.pushFront("2");
    dList.pushFront("3");
    BOOST_CHECK_EQUAL(dList.getSize(), 3);

    BOOST_CHECK(dList.find("1"));
    BOOST_CHECK(dList.find("2"));
    BOOST_CHECK(dList.find("3"));
    BOOST_CHECK(!dList.find("4"));

    dList.pushBack("4");
    dList.pushBack("5");
    dList.pushBack("6");
    BOOST_CHECK_EQUAL(dList.getSize(), 6);

    BOOST_CHECK(dList.find("4"));
    BOOST_CHECK(dList.find("5"));
    BOOST_CHECK(dList.find("6"));
    BOOST_CHECK(!dList.find("7"));

    dList.popFront();
    BOOST_CHECK_EQUAL(dList.getSize(), 5);
    BOOST_CHECK(!dList.find("3"));

    dList.popBack();
    BOOST_CHECK_EQUAL(dList.getSize(), 4);
    BOOST_CHECK(!dList.find("6"));

    dList.removeAt("4");
    BOOST_CHECK_EQUAL(dList.getSize(), 3);
    BOOST_CHECK(!dList.find("4"));

    dList.clearDList();
    BOOST_CHECK_EQUAL(dList.getSize(), 0);
    BOOST_CHECK(!dList.find("1"));

    dList.print(); 
    BOOST_CHECK_EQUAL(dList.getSize(), 0);
}
