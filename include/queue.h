#ifndef queue_h
#define queue_h

#include "utility.h"

class Queue {
private:
    string* data;
    size_t size;
    int front; // Индекс первого элемента
    int rear; // Индекс последнего элемента
    int capacity; // Вместимость очереди

public:
    Queue(int cap);
    Queue();
    ~Queue();

    bool isempty();
    void push(string value); //Функция добаления элемента
    string pop(); // функция удаления элемента с начала очереди и его возврат
    string peek(); // функция вывода элемента в начале очереди
    int Size();
    void write_serialize(const string& filename);
    void deserialize(const string& filename);
    void serializeBinary(const string& filename);
    void deserializeBinary(const string& filename);
};

#include "../src/queue.cpp"

#endif //  QUEUE_H