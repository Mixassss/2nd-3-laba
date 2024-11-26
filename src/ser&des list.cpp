#include "../include/list.h"

void serializeSinglyLinkedList(const SinglyLinkedList& list, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    Node* current = list.getHead();
    while (current) {
        fout << current->data << endl; // Записываем каждое значение в новой строке
        current = current->next;
    }
    fout.close();
}

SinglyLinkedList deserializeSinglyLinkedList(const string& filename) {
    SinglyLinkedList list;
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return list;
    }

    string value;
    while (getline(fin, value)) {
        list.pushBack(value); // Добавляем данные в список
    }
    fin.close();
    return list;
}

void serializeSinglyLinkedListBinary(const SinglyLinkedList& list, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    Node* current = list.getHead();
    while (current) {
        size_t length = current->data.size();
        fout.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(current->data.c_str(), length); // Записываем строку
        current = current->next;
    }
    fout.close();
}

SinglyLinkedList deserializeSinglyLinkedListBinary(const string& filename) {
    SinglyLinkedList list;
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return list;
    }

    while (fin) {
        size_t length;
        fin.read(reinterpret_cast<char*>(&length), sizeof(length)); // Читаем длину строки
        if (!fin) break;
        
        string value(length, '\0'); // Создаем строку нужного размера
        fin.read(&value[0], length); // Читаем строку
        list.pushBack(value); // Добавляем данные в список
    }
    fin.close();
    return list;
}

void serializeDoublyLinkedList(const DoublyLinkedList& list, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    DoubleNode* current = list.getHead();
    while (current) {
        fout << current->data << endl; // Записываем каждое значение в новой строке
        current = current->next;
    }
    fout.close();
}

DoublyLinkedList deserializeDoublyLinkedList(const string& filename) {
    DoublyLinkedList list;
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return list;
    }

    string value;
    while (getline(fin, value)) {
        list.pushBack(value); // Добавляем данные в список
    }
    fin.close();
    return list;
}

void serializeDoublyLinkedListBinary(const DoublyLinkedList& list, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    DoubleNode* current = list.getHead();
    while (current) {
        size_t length = current->data.size();
        fout.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(current->data.c_str(), length); // Записываем строку
        current = current->next;
    }
    fout.close();
}

DoublyLinkedList deserializeDoublyLinkedListBinary(const string& filename) {
    DoublyLinkedList list;
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return list;
    }

    while (fin) {
        size_t length;
        fin.read(reinterpret_cast<char*>(&length), sizeof(length)); // Читаем длину строки
        if (!fin) break;
        
        string value(length, '\0'); // Создаем строку нужного размера
        fin.read(&value[0], length); // Читаем строку
        list.pushBack(value); // Добавляем данные в список
    }
    fin.close();
    return list;
}


int main() {

    // Создание и заполнение односвязного списка
    SinglyLinkedList sl;
    sl.pushBack("A");
    sl.pushBack("B");
    sl.pushBack("C");

    // Сериализация односвязного списка в текстовом формате
    serializeSinglyLinkedList(sl, "singlyLinkedList.txt");
    // Бинарная сериализация
    serializeSinglyLinkedListBinary(sl, "singlyLinkedList.bin");

    // Десериализация односвязного списка
    SinglyLinkedList slFromFile = deserializeSinglyLinkedList("singlyLinkedList.txt");
    // Бинарная десериализация
    SinglyLinkedList slFromBinary = deserializeSinglyLinkedListBinary("singlyLinkedList.bin");

    // Печать десериализованного списка
    cout << "Данные из сериализованного односвязного списка:" << endl;
    slFromFile.print();
    cout << "Данные из десериализованного односвязного списка из бинарного файла:" << endl;
    slFromBinary.print();

    // Создание и заполнение двусвязного списка
    DoublyLinkedList dl;
    dl.pushBack("X");
    dl.pushBack("Y");
    dl.pushBack("Z");

    // Сериализация двусвязного списка в текстовом формате
    serializeDoublyLinkedList(dl, "doublyLinkedList.txt");
    // Бинарная сериализация
    serializeDoublyLinkedListBinary(dl, "doublyLinkedList.bin");

    // Десериализация двусвязного списка
    DoublyLinkedList dlFromFile = deserializeDoublyLinkedList("doublyLinkedList.txt");
    // Бинарная десериализация
    DoublyLinkedList dlFromBinary = deserializeDoublyLinkedListBinary("doublyLinkedList.bin");

    // Печать десериализованного списка
    cout << "Данные из сериализованного двусвязного списка:" << endl;
    dlFromFile.print();
    cout << "Данные из десериализованного двусвязного списка из бинарного файла:" << endl;
    dlFromBinary.print();

    return 0;
}