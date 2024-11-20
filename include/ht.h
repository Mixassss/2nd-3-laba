#ifndef ht_h
#define ht_h

#include "utility.h"

const size_t SIZE = 100; // Пример размера хэш-таблицы

struct HNode {
    string key;
    string value;
    HNode* next;
    HNode(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

class Hash_table {
public:
    Hash_table();
    ~Hash_table();
    void insert(const string& key, const string& value);
    bool get(const string& key, string& value);
    int size() const;
    HNode* getTableEntry(int index) const;
    bool remove(const string& key);

private:
    HNode* table[SIZE];
    int sizetable = 0;
    int hashFunction(const string& key);
};

#include "../src/hash_table.cpp"

#endif // HT_H