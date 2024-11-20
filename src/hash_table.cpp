#include "../include/ht.h"

Hash_table::Hash_table() : sizetable(0) {
    for (size_t i = 0; i < SIZE; ++i) {
        table[i] = nullptr; // Присваивание каждой ноды нулевого значения
    }
}

Hash_table::~Hash_table() {
    for (size_t i = 0; i < SIZE; ++i) {
        HNode* current = table[i];
        while (current) {
            HNode* toDelete = current;
            current = current->next; // Освобождение каждой ноды
            delete toDelete;
        }
    }
}

int Hash_table::hashFunction(const string& key) {
    hash<string> hashFn;
    return hashFn(key) % SIZE;
}

void Hash_table::insert(const string& key, const string& value) {
    int hashValue = hashFunction(key);
    HNode* newPair = new HNode(key, value);

    if(table[hashValue] == nullptr) {
        table[hashValue] = newPair;
        sizetable++;
    } else {
        HNode* current = table[hashValue];
        while(current) { 
            if(current->key == key) {
                current->value = value;
                delete newPair;
                return;
            }
            if (current->next == nullptr) break;
            current = current->next;
        }
        current->next = newPair;  
        sizetable++;
    }
}

bool Hash_table::get(const string& key, string &value) {
    int hashValue = hashFunction(key);
    HNode* current = table[hashValue];
    while(current) {
        if(current->key == key) {
            value = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

int Hash_table::size() const {
    return sizetable; // Вернуть значение sizetable
}

HNode* Hash_table::getTableEntry(int index) const {
    if (index < 0 || index >= SIZE) return nullptr;
    return table[index];
}

bool Hash_table::remove(const string& key) {
    int hashValue = hashFunction(key);
    HNode* current = table[hashValue];
    HNode* perv = nullptr;

    while(current) {
        if(current->key == key) {
            if(perv) {
                perv->next = current->next;
            } else {
                table[hashValue] = current->next;
            }
            delete current; 
            sizetable--;  // Уменьшаем sizetable при удалении
            return true; 
        }
        perv = current;
        current = current->next;
    }
    return false; 
}