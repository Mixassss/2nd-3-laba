#include "../include/list.h"

Node::Node(string value) {
    data = value;
    next = nullptr;
} 

SinglyLinkedList::SinglyLinkedList() {
    head = nullptr; //Если список не содержит элементов, то присваиваем нулевое значение
}

SinglyLinkedList::~SinglyLinkedList() {
    while(!isEmpty()) {
        popFront(); //Вызывает список, после которого очищает память
    }
}

bool SinglyLinkedList::isEmpty() const {
    return elementCount == 0;
}

void SinglyLinkedList::print() {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void SinglyLinkedList::pushFront(string value) { 
    Node* newNode = new Node(value);
    newNode->next = head; //Следующий узел, становится текущей головой списка
    head = newNode;
    elementCount++;
}

void SinglyLinkedList::pushBack(string value) {
    Node* newNode = new Node(value);
    if(head == nullptr) { //Условие если список пуст
        head = newNode;
    } else {
        Node* current = head;
        while(current->next != nullptr) {
            current = current->next; //Присваиваем current следующее значение
        }
        current->next = newNode;
    }
    elementCount++;
}

void SinglyLinkedList::popFront() {
    if(head == nullptr) return;
    Node* nextHead = head->next; //Создание временной переменной, для сохранения
    delete head;
    head = nextHead;
    elementCount--;
}

void SinglyLinkedList::popBack() {
    if (head == nullptr) return; // Если список пуст
    if (head->next == nullptr) { // Если один элемент
        delete head;
        head = nullptr; // Исправлено
    } else {
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
            delete current->next; // Удаляем последний элемент
            current->next = nullptr; // Обнуляем указатель на следующий элемент
        }
    elementCount--;
}

void SinglyLinkedList::removeAt(string value) {
    if (isEmpty()) return;
    if (head->data == value) {
        popFront();
        return;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }
    if (current->next != nullptr) {
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
        elementCount--;
    }
}

bool SinglyLinkedList::find(string value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

size_t SinglyLinkedList::getSize() const {
    return elementCount;
}

Node* SinglyLinkedList::getHead() const {
    return head;
}

void SinglyLinkedList::clearSList() {
    while (!isEmpty()) {
        popFront();
    }
}

void SinglyLinkedList::write_serialize(const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) return; // Проверка на успешное открытие файла
    Node* current = head;
    while (current) {
        fout << current->data << endl; // Записываем каждый элемент в новую строку
        current = current->next;
    }
    fout.close();
}

void SinglyLinkedList::deserialize(const string& filename) {
    clearSList();
    ifstream fin(filename);
    if (!fin.is_open()) return; // Проверка на успешное открытие файла
    string value;
    while(getline(fin, value)) {
        pushBack(value);
    }
    fin.close();
}

void SinglyLinkedList::serializeBinary(const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) return; // Проверка на успешное открытие файла
    Node* current = head;
    while (current) {
        size_t length = current->data.size();
        fout.write(reinterpret_cast<char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(current->data.data(), length); // Записываем данные
        current = current->next;
    }
    fout.close();
}

void SinglyLinkedList::deserializeBinary(const string& filename) {
    clearSList();
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) return; // Проверка на успешное открытие файла
    size_t length;
    while (fin.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        string value(length, '\0');
        fin.read(&value[0], length); // Читаем данные
        pushBack(value); // Добавляем значения в конец списка
    }
    fin.close();
}

DoubleNode::DoubleNode(string value){ 
    data = value;
    next = nullptr;
    prev = nullptr;
}

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr; //Если список не содержит элементов, то присваиваем нулевое значение
    tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
    while(!isEmpty()) {
        popFront(); //Вызывает список, после которого очищает память
    }
}

bool DoublyLinkedList::isEmpty() const {
    return elementCount == 0;
}

void DoublyLinkedList::pushFront(string value) {
    DoubleNode* newNode = new DoubleNode(value);
    newNode->next = head; //Следующий узел, становится текущей головой списка
    if (head != nullptr) {
        head->prev = newNode; // Обновляем указатель prev у старой головы
    } else {
        tail = newNode; // Если список был пуст, новый узел становится и хвостом
    }
    head = newNode;
    elementCount++;
}

void DoublyLinkedList::pushBack(string value) {
    DoubleNode* newNode = new DoubleNode(value);
    if(tail == nullptr) { //Условие если список пуст
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    elementCount++;
}

void DoublyLinkedList::popFront() {
    if(head == nullptr) return;
    DoubleNode* nextHead = head; //Создание временной переменной, для сохранения
    head = head->next;
    if(head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete nextHead;
    elementCount--;
}

void DoublyLinkedList::popBack() {
    if(tail == nullptr) return;
    if(head == tail) { //Если один элемент
        head = nullptr;
        tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr; //Следующий элемент - ноль
    }
    delete tail->next; // Удаляем последний элемент
    elementCount--;
}

void DoublyLinkedList::removeAt(string value) {
    DoubleNode* current = head;
    while (current) {
        if (current->data == value) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next; // Удаляем голову
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev; // Удаляем хвост
            }
            delete current;
            elementCount--;
            return; // Выход после удаления первого найденного элемента
        }
        current = current->next;
    }
}

bool DoublyLinkedList::find(string value) {
    DoubleNode* current = head;
    while(current) {
        if(current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void DoublyLinkedList::print() {
    DoubleNode* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

size_t DoublyLinkedList::getSize() const {
    return elementCount;
}

void DoublyLinkedList::clearDList() {
    while (!isEmpty()) {
        popFront();
    }
}

void DoublyLinkedList::write_serialize(const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) return; // Проверка на успешное открытие файла
    DoubleNode* current = head;
    while (current) {
        fout << current->data << endl; // Записываем каждый элемент в новую строку
        current = current->next;
    }
    fout.close();
}

void DoublyLinkedList::deserialize(const string& filename) {
    clearDList();
    ifstream fin(filename);
    if (!fin.is_open()) return; // Проверка на успешное открытие файла
    string value;
    while(getline(fin, value)) {
        pushBack(value);
    }
    fin.close();
}

void DoublyLinkedList::serializeBinary(const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) return; // Проверка на успешное открытие файла
    DoubleNode* current = head;
    while (current) {
        size_t length = current->data.size();
        fout.write(reinterpret_cast<char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(current->data.data(), length); // Записываем данные
        current = current->next;
    }
    fout.close();
}

void DoublyLinkedList::deserializeBinary(const string& filename) {
    clearDList();
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) return; // Проверка на успешное открытие файла
    size_t length;
    while (fin.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        string value(length, '\0');
        fin.read(&value[0], length); // Читаем данные
        pushBack(value); // Добавляем значения в конец списка
    }
    fin.close();
}