#include "../include/ht.h"

// Сериализация в текстовый формат
void serializeToText(Hash_table& ht, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }

    for (size_t i = 0; i < SIZE; ++i) {
        HNode* current = ht.getTable()[i];
        while (current) {
            outFile << current->key << " " << current->value << "\n";
            current = current->next;
        }
    }

    outFile.close();
}

// Десериализация из текстового формата
void deserializeFromText(Hash_table& ht, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    string key;
    string value;
    while (inFile >> key) {
        if (getline(inFile, value)) {
            value.erase(0, 1); // Удаление пробела перед значением
            ht.insert(key, value);
        }
    }

    inFile.close();
}

// Сериализация в бинарный формат
void serializeToBinary(Hash_table& ht, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }

    for (size_t i = 0; i < SIZE; ++i) {
        HNode* current = ht.getTable()[i];
        while (current) {
            size_t keyLength = current->key.size();
            size_t valueLength = current->value.size();

            outFile.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
            outFile.write(current->key.c_str(), keyLength);
            outFile.write(reinterpret_cast<const char*>(&valueLength), sizeof(valueLength));
            outFile.write(current->value.c_str(), valueLength);
            current = current->next;
        }
    }

    outFile.close();
}

// Десериализация из бинарного формата
void deserializeFromBinary(Hash_table& ht, const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    while (inFile.peek() != ifstream::traits_type::eof()) {
        size_t keyLength;
        inFile.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));
        
        string key(keyLength, '\0');
        inFile.read(&key[0], keyLength);

        size_t valueLength;
        inFile.read(reinterpret_cast<char*>(&valueLength), sizeof(valueLength));
        
        string value(valueLength, '\0');
        inFile.read(&value[0], valueLength);

        ht.insert(key, value);
    }

    inFile.close();
}

int main() {
    Hash_table ht;
    // Пример использования: добавление, сериализация и десериализация
    ht.insert("merz", "1");
    ht.insert("bmw", "2");
    ht.insert("bmw", "3");

    serializeToText(ht, "hash_table.txt");
    serializeToBinary(ht, "hash_table.bin");

    Hash_table ht2;
    deserializeFromText(ht2, "hash_table.txt");
    deserializeFromBinary(ht2, "hash_table.bin");

    cout << "Размер после десерилизации: " << ht2.size() << endl;

    return 0;
}