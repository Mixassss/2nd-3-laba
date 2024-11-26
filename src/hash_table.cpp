#include "../include/ht.h"

Hash_table::Hash_table(): sizetable(0) {
    for(size_t i = 0; i < SIZE; ++i) {
        table[i] = nullptr; //Присваиванпие каждой ноды, нулевого значения
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

void Hash_table::insert(const string &key, const string &value) {
    int hashValue = hashFunction(key);
    HNode* newPair = new HNode(key, value);

    if(table[hashValue] == nullptr) {
        table[hashValue] = newPair;
        sizetable++;
    } else {
        HNode* current = table[hashValue];
        while(current) { 
            if(current->key == key) {
                current->value = value; // Обновляем значение
                delete newPair; // Удаляем временный узел
                return; 
            }
            if (current->next == nullptr) break; 
            current = current->next;
        }
        current->next = newPair; // Добавляем новый элемент
        sizetable++;
    }
}

bool Hash_table::get(const string& key, string& value) {
    int HashValue = hashFunction(key); //Хэш значение соответсвующее этому ключу
    HNode* current = table[HashValue];
    while(current) {
        if(current->key == key) {
            value = current->value; //Возвращаем значение
            cout << value << endl;
            return true; //Ключ найден
        }
        current = current->next;
    }
    return false; //Ключ не найден
}

int Hash_table::size() const {
    return sizetable; // Возвращаем текущее количество элементов
}

bool Hash_table::remove(const string& key) {
    int HashValue = hashFunction(key);
    HNode* current = table[HashValue];
    HNode* perv = nullptr;

    while(current) {
        if(current->key == key) {
            if(perv) {
                perv->next = current->next; 
            } else {
                table[HashValue] = current->next; 
            }
            delete current; 
            sizetable--; // Уменьшаем размер
            return true; 
        }
        perv = current;
        current = current->next;
    }
    return false; 
}