#ifndef stack_h
#define stack_h

#include "utility.h"

class Stack{
private:
    string* data;
    int head;
    int capacity; //Вместимост стека
    
public:
    Stack(size_t size);
    Stack();
    ~Stack();

    void push(string value); //Функция добавления
    string pop(); //Функция удаление элемента и возврат значения
    string peek(); // Функция удаления верхнего элемента
    bool isEmpty();
    size_t size();
};

#include "../src/stack.cpp"

#endif // STACK_H