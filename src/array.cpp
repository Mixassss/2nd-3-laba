#include "../include/arr.h"

Array::Array() : size(0), capacity(10) {
    arr = new string[capacity];
}

Array::~Array() {
    delete[] arr; // Освобождение места
}

void Array::resize() {
    capacity *= 2; // Увеличиваем емкость в 2 раза
    string* newArr = new string[capacity];
    for (size_t i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

void Array::ShowArray() const {
    for (size_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void Array::addToEnd(string value) {
    if (size == capacity) {
        resize(); // Увеличение емкости, если массив переполнен
    }
    arr[size++] = value; // Увеличение длины массива   
}

void Array::addAtIndex(size_t index, string value) {
    if (index > size) return;
    if (size == capacity) {
        resize(); // Увеличение емкости
    }
    for (size_t i = size; i > index; --i) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    size++;
}

string Array::getIndex(size_t index) const {
    if (index >= size) {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

void Array::removeAtIndex(size_t index) {
    if (index >= size) return;
    for (size_t i = index; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    size--;
}

void Array::replaceAtIndex(size_t index, string value) {
    if (index >= size) return;
    arr[index] = value; // Замена элемента
}

bool Array::find(const string& value) const {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return true; // Элемент найден
        }
    }
    return false; // Элемент не найден
}

size_t Array::getSize() const {
    return size;
}