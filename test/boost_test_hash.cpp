#define BOOST_TEST_MODULE HashTableTest
#include <boost/test/included/unit_test.hpp>
#include "../include/ht.h"

BOOST_AUTO_TEST_CASE(Hash_Test_Push) {
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

}

BOOST_AUTO_TEST_CASE(Hash_Test_NoVal) {
   Hash_table hash;
   string value;

   BOOST_CHECK(!hash.get("mute", value));
}

BOOST_AUTO_TEST_CASE(Hash_Test_Koliz) {
    Hash_table hash;
    string value;

    hash.insert("axe", "1");
    BOOST_CHECK_EQUAL(hash.size(), 1);
    BOOST_CHECK(hash.get("axe", value));
    BOOST_CHECK_EQUAL(value, "1");
    hash.insert("kez", "2");
    BOOST_CHECK_EQUAL(hash.size(), 2);
    BOOST_CHECK(hash.get("kez", value));
    BOOST_CHECK_EQUAL(value, "2");
    hash.insert("invoker", "3");
    BOOST_CHECK_EQUAL(hash.size(), 3);
    BOOST_CHECK(hash.get("invoker", value));
    BOOST_CHECK_EQUAL(value, "3");
}

BOOST_AUTO_TEST_CASE(Hash_Test_GetTableEntry_OutOfBound) {
    Hash_table hash;

    // Проверка выхода за пределы
    BOOST_CHECK(hash.getTableEntry(-1) == nullptr);
    BOOST_CHECK(hash.getTableEntry(SIZE) == nullptr);
}

BOOST_AUTO_TEST_CASE(Hash_Test_RemoveNonKey) {
    Hash_table hash;

    // Попытка удалить несуществующий ключ
    BOOST_CHECK(!hash.remove("axe"));
    BOOST_CHECK_EQUAL(hash.size(), 0);
}

BOOST_AUTO_TEST_CASE(Hash_Test_RemoveLastElement) {
    Hash_table hash;
    string value;
    
    hash.insert("key1", "value1");
    hash.insert("key2", "value2");
    hash.insert("key3", "value3");
    
    BOOST_CHECK_EQUAL(hash.size(), 3);

    // Удаление последнего элемента в цепочке (key3)
    BOOST_CHECK(hash.remove("key3"));
    BOOST_CHECK_EQUAL(hash.size(), 2);
    BOOST_CHECK(!hash.get("key3", value)); // Проверка удаления
}

BOOST_AUTO_TEST_CASE(Hash_Test_RemoveLastElement) {
    Hash_table hash;
    string value;
    
    hash.insert("key1", "value1");
    hash.insert("key2", "value2");
    hash.insert("key3", "value3");
    
    BOOST_CHECK_EQUAL(hash.size(), 3);

    // Удаление последнего элемента в цепочке (key3)
    BOOST_CHECK(hash.remove("value1"));
    BOOST_CHECK_EQUAL(hash.size(), 2);
    BOOST_CHECK(!hash.get("value1", value)); // Проверка удаления
}