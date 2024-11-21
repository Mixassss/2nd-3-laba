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

    hash.insert("veng", "1");
    BOOST_CHECK_EQUAL(hash.size(), 1);
    BOOST_CHECK(hash.get("veng", value));
    BOOST_CHECK_EQUAL(value, "1");
}

BOOST_AUTO_TEST_CASE(Hash_Test_NoVal) {
   Hash_table hash;
   string value;

   BOOST_CHECK(!hash.get("mute", value));
}

BOOST_AUTO_TEST_CASE(Hash_Test_Koliz) {
    Hash_table hash;

    hash.insert("key1", "value1");
    hash.insert("key2", "value2");
    string value;
    BOOST_CHECK(hash.get("key1", value));
    BOOST_CHECK(hash.get("key2", value));
}

BOOST_AUTO_TEST_CASE(Hash_Test_RemoveNonKey) {
    Hash_table hash;

    // Попытка удалить несуществующий ключ
    BOOST_CHECK(!hash.remove("spirit"));
    BOOST_CHECK_EQUAL(hash.size(), 0);
}

BOOST_AUTO_TEST_CASE(Hash_Test_RemoveLastElement) {
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
}