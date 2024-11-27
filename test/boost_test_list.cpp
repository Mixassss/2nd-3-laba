#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "../include/list.h"

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

BOOST_AUTO_TEST_CASE(SinglyLinkedList_Test_Front) {
    Timer timer;
    timer.start();
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

    cout << "Singly list push front test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(SinglyLinkedList_Test_Back) {
    Timer timer;
    timer.start();
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

    cout << "Singly list push back test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(SinglyLinkedList_Test_PopBack) {
    Timer timer;
    timer.start();
    SinglyLinkedList sList;

    BOOST_CHECK(sList.isEmpty());
    BOOST_CHECK_EQUAL(sList.getSize(), 0);

    sList.pushBack("4");
    sList.pushBack("5");

    BOOST_CHECK_EQUAL(sList.getSize(), 2);
    
    BOOST_CHECK(sList.find("4"));
    BOOST_CHECK(sList.find("5"));
    BOOST_CHECK(!sList.find("6"));

    sList.popFront();
    BOOST_CHECK_EQUAL(sList.getSize(), 1);
    BOOST_CHECK(!sList.find("4"));

    sList.popBack();
    BOOST_CHECK_EQUAL(sList.getSize(), 0);
    BOOST_CHECK(!sList.find("5"));

    cout << "Singly list pop back test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(DoublyLinkedList_Test) {
    Timer timer;
    timer.start();
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

    cout << "Doubly list test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(DoublyLinkedList_PushTest) {
    Timer timer;
    timer.start();
    DoublyLinkedList dList;

    BOOST_CHECK(dList.isEmpty());
    BOOST_CHECK_EQUAL(dList.getSize(), 0);

    dList.pushBack("1");
    dList.pushBack("2");
    BOOST_CHECK_EQUAL(dList.getSize(), 2);

    BOOST_CHECK(dList.find("1"));
    BOOST_CHECK(dList.find("2"));
    BOOST_CHECK(!dList.find("3"));

    dList.pushFront("4");
    dList.pushFront("5");
    BOOST_CHECK_EQUAL(dList.getSize(), 4);

    BOOST_CHECK(dList.find("4"));
    BOOST_CHECK(dList.find("5"));
    BOOST_CHECK(!dList.find("6"));

    dList.popFront();
    BOOST_CHECK_EQUAL(dList.getSize(), 3);
    BOOST_CHECK(!dList.find("5"));

    dList.popBack();
    BOOST_CHECK_EQUAL(dList.getSize(), 2);
    BOOST_CHECK(!dList.find("2"));

    dList.removeAt("1");
    BOOST_CHECK_EQUAL(dList.getSize(), 1);
    BOOST_CHECK(!dList.find("1"));

    dList.removeAt("4");
    BOOST_CHECK_EQUAL(dList.getSize(), 0);
    BOOST_CHECK(!dList.find("4"));

    cout << "Doubly list test push back: " << timer.elapsed() << " seconds" << endl;
}