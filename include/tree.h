#ifndef tree_h
#define tree_h

#include "utility.h"

class NodeT {
private:
    int data;
    NodeT* left;
    NodeT* right;

public:
    NodeT(int value);
    int getData() const { return data; }
    NodeT* getLeft() const { return left; }
    NodeT* getRight() const { return right; }
    void setLeft(NodeT* nodet) { left = nodet; }
    void setRight(NodeT* nodet) { right = nodet; }
};

class CompleteBinaryTree {
private:
    NodeT* root; // Главная часть в бинарном дереве
    size_t size;
    
    NodeT* _insert(NodeT* nodeb, int value);
    bool search(NodeT* nodet, int value); // Функция поиска
    bool isComplete(NodeT* nodet, int index, int totalNodes); // Проверка на complete
    int countNodes(NodeT* nodet);
    string _toString(NodeT* nodet);
    void printTree(NodeT* node, int depth);
    void clear(NodeT* nodet); // Освобождение памяти

public:
    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void print();
    string toString();
    void insert(int value); // Функция добавления элемента
    bool isComplete();
    bool search(int value); // Функция для поиска
    size_t getSize() const { return size; } // Новый метод для получения размера
    NodeT* getRoot() const { return root; } // Новый метод для получения корня
};

#include "../src/complete_binary_tree.cpp"

#endif // TREE_H