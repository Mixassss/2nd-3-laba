#pragma once

#include "utility.h"

class Array {
private:
    string* arr;
    size_t size; //Размер массива
    size_t razmer;

public:
    Array(); //Конструктор
    ~Array(); //Деструктор
    void ShowArray() const; // Вывод массива
    void addToEnd(string value); //Добавление элемента в конец массива
    void addAtIndex(size_t index, string value); // Добавление по индексу
    string getIndex(size_t index); //Получение элемента по индексу
    void removeAtIndex(size_t index); //Удаление элемента по индексу
    void replaceAtIndex(size_t index, string value);  // Замена элемента по индексу
    size_t getSize() const;
};

#include "../src/array.cpp"