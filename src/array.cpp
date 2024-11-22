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

string Array::getIndex(size_t index) {
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

void Array::write_serialize(const string& filename) {
    ofstream fout(filename);
    for (size_t i = 0; i < size; ++i) {
        fout << arr[i] << endl; // Записываем каждый элемент в новую строку
    }
    fout.close();
}

void Array::deserialize(const string& filename) {
    delete [] arr; // Освобождаем предыдущее место
    size = 0;
    capacity = 10; // Сбрасываем емкость
    arr = new string[capacity];
    ifstream fin(filename);
    string value;
    while(getline(fin, value)) {
        addToEnd(value); // Добавляем значения в конец массива
    }
    fin.close();
}

void Array::serializeBinary(const string& filename) {
    ofstream fout(filename, ios::binary);
    for (size_t i = 0; i < size; ++i ) {
        size_t length = arr[i].size();
        fout.write(reinterpret_cast<char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(arr[i].data(), length); // Записываем данные
    }
    fout.close();
}

void Array::deserializeBinary(const string& filename) {
    delete [] arr; // Освобождаем предыдущее место
    size = 0;
    capacity = 10; // Сбрасываем емкость
    arr = new string[capacity]; // Создаем новый массив
    ifstream fin(filename, ios::binary);
    size_t length;
    while (fin.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        string value(length, '\0');
        fin.read(&value[0], length); // Читаем данные
        addToEnd(value); // Добавляем значения в конец массива
    }
    fin.close();
}