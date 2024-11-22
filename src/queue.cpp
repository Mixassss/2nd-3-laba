#include "../include/queue.h"

Queue::Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
    data = new string[capacity];
}

Queue::Queue() : capacity(30), front(0), rear(-1), size(0) {
    data = new string[capacity]; //Размер списка
}

Queue::~Queue() {
    delete[] data;
}

bool Queue::isempty() {
    return size == 0;
}

void Queue::push(string value) {
    if (size == capacity) {
        throw overflow_error("Очередь переполнена"); // Проверка на переполнение
    }
    rear = (rear + 1) % capacity; // Циклическое увеличение индекса
    data[rear] = value; // Добавление элемента
    size++; // Увеличение размера очереди
}

string Queue::pop() {
    if (size == 0) {
        throw underflow_error("Очередь пуста"); // Проверка на пустоту
    }
    string value = data[front]; // Сохранение значения для возврата
    front = (front + 1) % capacity; // Циклическое увеличение индекса
    size--; // Уменьшение размера очереди
    return value; // Возврат удаленного элемента
}

string Queue::peek() {
    if (isempty()) {
        throw underflow_error("Очередь пуста"); // Проверка на пустоту
    }
    return data[front];
}

int Queue::Size() {
    return size;
}

void Queue::write_serialize(const string& filename) {
    ofstream fout(filename);
    for (size_t i = 0; i < size; ++i) {
        fout << data[(front + i) % capacity] << endl; // Записываем каждый элемент в новую строку
    }
    fout.close();
}

void Queue::deserialize(const string& filename) {
    ifstream fin(filename);
    string value;
    while (getline(fin, value)) {
        push(value); // Добавляем значения в конец массива
    }
    fin.close();
}

void Queue::serializeBinary(const string& filename) {
    ofstream fout(filename, ios::binary);
    for (size_t i = 0; i < size; ++i) {
        string& value = data[(front + i) % capacity];
        size_t length = value.length();
        fout.write(reinterpret_cast<char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(value.data(), length); // Записываем данные
    }
    fout.close();
}

void Queue::deserializeBinary(const string& filename) {
    ifstream fin(filename, ios::binary);
    size_t length;
    while (fin.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        string value(length, '\0');
        fin.read(&value[0], length); // Читаем данные
        push(value); // Добавляем значения в конец массива
    }
    fin.close();
}