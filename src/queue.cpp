#include "../include/queue.h"

Queue::Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
    data = new string[capacity];
}

Queue::Queue() : Queue(30) {}

Queue::~Queue() {
    delete[] data;
}

bool Queue::isempty() {
    return size == 0;
}

void Queue::push(string value) {
    if (size == capacity) {
        throw overflow_error("Очередь переполнена");
    }
    rear = (rear + 1) % capacity;
    data[rear] = value;
    size++;
}

string Queue::pop() {
    if (isempty()) {
        throw underflow_error("Очередь пуста");
    }
    string value = data[front];
    front = (front + 1) % capacity;
    size--;
    return value;
}

string Queue::peek() {
    if (isempty()) {
        throw underflow_error("Очередь пуста");
    }
    return data[front];
}

int Queue::Size() {
    return size;
}