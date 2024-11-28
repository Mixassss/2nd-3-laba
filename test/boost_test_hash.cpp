#define BOOST_TEST_MODULE HashTableTest
#include <boost/test/included/unit_test.hpp>
#include "../include/ht.h"

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

BOOST_AUTO_TEST_CASE(Hash_Test_Push) {
    Timer timer;
    timer.start();
    Hash_table hash;
    string value;

    BOOST_CHECK_EQUAL(hash.size(), 0);
    hash.insert("axe", "1");
    BOOST_CHECK_EQUAL(hash.size(), 1);
    BOOST_CHECK(hash.get("axe", value));
    BOOST_CHECK_EQUAL(value, "1");

    hash.insert("axe", "2");
    BOOST_CHECK(hash.get("axe", value));
    BOOST_CHECK_EQUAL(value, "2");
    BOOST_CHECK_EQUAL(hash.size(), 1);

    BOOST_CHECK(hash.remove("axe"));
    BOOST_CHECK_EQUAL(hash.size(), 0);
    BOOST_CHECK(!hash.get("axe", value));

    hash.insert("veng", "1");
    BOOST_CHECK_EQUAL(hash.size(), 1);
    BOOST_CHECK(hash.get("veng", value));
    BOOST_CHECK_EQUAL(value, "1");

    cout << "Hash table push test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Hash_Test_NoVal) {
    Timer timer;
    timer.start();
    Hash_table hash;
    string value;

   BOOST_CHECK(!hash.get("stalker", value));

   cout << "Hash no value get test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Hash_Test_Koliz) {
    Timer timer;
    timer.start();
    Hash_table hash;

    hash.insert("654321", "1");
    hash.insert("6543219", "2");
    string value;
    BOOST_CHECK(hash.get("654321", value));
    BOOST_CHECK(hash.get("6543219", value));

    cout << "Hash kolizion test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Hash_Test_RemoveNonKey) {
    Timer timer;
    timer.start();
    Hash_table hash;

    // Попытка удалить несуществующий ключ
    BOOST_CHECK(!hash.remove("spirit"));
    BOOST_CHECK_EQUAL(hash.size(), 0);

    hash.insert("654321", "1");
    hash.insert("6543219", "2");
    hash.remove("6543219");
    hash.insert("6543219", "2");
    hash.remove("654321");

    cout << "Hash remove non key test: " << timer.elapsed() << " seconds" << endl;
}

BOOST_AUTO_TEST_CASE(Hash_Test_RemoveLastElement) {
    Timer timer;
    timer.start();
    Hash_table hashs;
    string value;
    
    hashs.insert("key1", "value1");
    hashs.insert("key2", "value2");
    hashs.insert("key3", "value3");
    
    BOOST_CHECK_EQUAL(hashs.size(), 3);

    // Удаление последнего элемента в цепочке (key3)
    BOOST_CHECK(hashs.remove("key3"));
    BOOST_CHECK_EQUAL(hashs.size(), 2);
    BOOST_CHECK(!hashs.get("key3", value)); // Проверка удаления

    BOOST_CHECK(hashs.remove("key2"));
    BOOST_CHECK_EQUAL(hashs.size(), 1);
    BOOST_CHECK(!hashs.get("key2", value)); // Проверка удаления

    BOOST_CHECK(hashs.remove("key1"));
    BOOST_CHECK_EQUAL(hashs.size(), 0);
    BOOST_CHECK(!hashs.get("key1", value)); // Проверка удаления

    cout << "Hash remove last element test: " << timer.elapsed() << " seconds" << endl;
}