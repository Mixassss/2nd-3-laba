#ifndef list_h
#define list_h

#include "utility.h"

struct Node {
    string data;
    Node* next; //Указатель на след. элемент
    
    Node(string value); //Конструктор узла
};

class SinglyLinkedList {
private:
    Node* head;
    size_t elementCount = 0;

public:

    SinglyLinkedList(); //Конструктор
    ~SinglyLinkedList(); //Деконструктор

    bool isEmpty() const;
    void print(); // ф-ия вывода списка
    void pushFront(string value); //Добавление в начало списка
    void pushBack(string value); //Добавление в конец списка
    void popFront(); //Удаление в начале списка
    void popBack(); //Удаление в конце списка
    void removeAt(string value); //Удаление по индексу
    bool find(string value); //Поиск значений в списке
    size_t getSize() const;
    void clearSList();
    Node* getHead() const; // Добавлен метод getHead
};


struct DoubleNode {
    string data;
    DoubleNode* next;
    DoubleNode* prev; //Указатель на предыдущий элемент в списке

    DoubleNode(string value); //Конструктор узла
};

class DoublyLinkedList {
private:
    DoubleNode* head;
    DoubleNode* tail;
    size_t elementCount = 0;

public:

    DoublyLinkedList(); //Конструктор
    ~DoublyLinkedList(); //Деконструктор

    bool isEmpty() const;
    void pushFront(string value); //Добавление в начало списка
    void pushBack(string value); //Добавление в конец списка
    void popFront(); //Удаление в начале списка
    void popBack(); //Удаление в конце списка
    void removeAt(string value); //Удаление по индексу
    bool find(string value); //Поиск значений в списке
    void print(); // Функция вывода списка
    size_t getSize() const;
    void clearDList();
    DoubleNode* getHead() const; // Добавленный метод getHead
};

#include "../src/list.cpp"

#endif // LIST_H