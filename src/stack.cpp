#include "../include/stack.h"

Stack::Stack(size_t size) : capacity(size), head(-1) {
    data = new string[capacity];
}

Stack::Stack() : capacity(10), head(-1) { // Например, установить начальную емкость 10
    data = new string[capacity];
}

Stack::~Stack() {
    delete[] data;
}

void Stack::push(string value) {
    if (head == capacity - 1) {
        throw overflow_error("Стек переполнен.");
    }
    data[++head] = value; // Добавление элемента и увеличение индекса
}

string Stack::pop() {
    if (head == -1) {
        throw underflow_error("Стек пустой.");
    }
    return data[head--]; // Возврат элемента и уменьшение индекса
}

 string Stack::peek() {
    if(head == -1) {
        throw underflow_error("Стек пустой.");
    }
    return data[head];
}

bool Stack::isEmpty() {
    return head == -1;
}

size_t Stack::size() {
    return head + 1;
}

void Stack::write_serialize(const string& filename) {
    ofstream fout(filename);
    for (size_t i = 0; i <= head; ++i) {
        fout << data[i] << endl; // Записываем каждый элемент в новую строку
    }
    fout.close();
}

void Stack::deserialize(const string& filename) {
    ifstream fin(filename);
    string value;
    while (getline(fin, value)) {
        push(value); // Добавляем значения в конец массива
    }
    fin.close();
}

void Stack::serializeBinary(const string& filename) {
    ofstream fout(filename, ios::binary);
    size_t currentSize = size();
    fout.write(reinterpret_cast<char*>(&currentSize), sizeof(currentSize)); // Записываем количество элементов
    for (size_t i = 0; i <= head; ++i) {
        size_t length = data[i].length();
        fout.write(reinterpret_cast<char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(data[i].data(), length); // Записываем данные
    }
    fout.close();
}

void Stack::deserializeBinary(const string& filename) {
    ifstream fin(filename, ios::binary);
    size_t currentSize;
    fin.read(reinterpret_cast<char*>(&currentSize), sizeof(currentSize)); // Читаем количество элементов
    for (size_t i = 0; i < currentSize; ++i) {
        size_t length;
        fin.read(reinterpret_cast<char*>(&length), sizeof(length)); // Читаем длину строки
        string value(length, '\0');
        fin.read(&value[0], length); // Читаем данные
        push(value);
    }
    fin.close();
}