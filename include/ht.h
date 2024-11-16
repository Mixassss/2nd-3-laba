#ifndef ht_h
#define ht_h

#include "utility.h"

const size_t SIZE = 100; //Размер хэш-таблицы

class HNode {
public:
    string key;
    string value;
    HNode* next;

     // Конструктор для удобства создания узлов
    HNode(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

class Hash_table {
private:
    HNode* table[SIZE];
    int sizetable = 0;

    int hashFunction(const string& key); // Хеш-функция

public:
    Hash_table(); //Инициализация хэш таблицы
    ~Hash_table(); //Деконструктор

    void insert(string &key, string &value); //Функция долбавления элемента
    bool get(const string& key, string& value);
    bool remove(const string& key);
};

#include "../src/hash_table.cpp"

#endif // HT_H