#ifndef ht_h
#define ht_h

#include "utility.h"

const size_t SIZE = 100; //Размер хэш-таблицы

class HNode {
public:
    string key;
    string value;
    HNode* next;

    HNode(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

class Hash_table {
private:
    HNode* table[SIZE];

    int hashFunction(const string& key); // Хеш-функция

public:
    int sizetable;
    Hash_table(); // Инициализация хэш таблицы
    ~Hash_table(); // Деконструктор

    void insert(const string& key, const string& value); // Функция добавления элемента
    bool get(const string& key, string& value);
    bool remove(const string& key);
    int size() const;

    HNode** getTable() { return table; };
};

#include "../src/hash_table.cpp"

#endif // HT_H