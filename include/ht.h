#ifndef ht_h
#define ht_h

#include "utility.h"

const size_t SIZE = 100; // Размер хэш-таблицы

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
    int sizetable = 0;

    int hashFunction(const string& key);

public:
    Hash_table();
    ~Hash_table();

    void insert(string& key, string& value);
    bool get(const string& key, string& value);
    bool remove(const string& key);
    int size() const; 
    HNode* getTableEntry(int index) const; // Новый метод для доступа к элементам
};

#include "../src/hash_table.cpp"

#endif // HT_H