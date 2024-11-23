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

void Hash_table::serializeToText(const string& filename) {
    ofstream fout(filename);
    for (size_t i = 0; i < SIZE; ++i) {
        HNode* current = table[i];
        while (current) {
            fout << current->key << ": " << current->value << endl;
            current = current->next;
        }
    }
    fout.close();
}

void Hash_table::deserializeFromText(const string& filename) {
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(': ');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            insert(key, value);
        }
    }
    fin.close();
}

void Hash_table::serializeToBinary(const string& filename) {
    ofstream fout(filename);
    for (size_t i = 0; i < SIZE; ++i) {
        HNode* current = table[i];
        while (current) {
            size_t keySize = current->key.size();
            size_t valueSize = current->value.size();
            fout.write(reinterpret_cast<char*>(&keySize), sizeof(keySize));
            fout.write(current->key.c_str(), keySize);
            fout.write(reinterpret_cast<char*>(&valueSize), sizeof(valueSize));
            fout.write(current->value.c_str(), valueSize);
            current = current->next;
        }
    }
    fout.close();
}

void Hash_table::deserializeFromBinary(const string& filename) {
    ifstream fin(filename, ios::binary);
    while(fin.peek() != EOF) {
        size_t keySize;
        fin.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));
        string key(keySize, '\0');
        fin.read(&key[0], keySize);

        size_t valueSize;
        fin.read(reinterpret_cast<char*>(&valueSize), sizeof(valueSize));
        string value(valueSize, '\0');
        fin.read(&value[0], valueSize);

        insert(key, value);
    }
    fin.close();
}