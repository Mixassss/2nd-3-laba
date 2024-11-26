#ifndef tree_h
#define tree_h

#include "utility.h"

class NodeT {
public:
    int data;
    NodeT* left;
    NodeT* right;

    NodeT(int value);
};

class CompleteBinaryTree {
private:
    NodeT* root;
    size_t size;

    NodeT* _insert(NodeT* node, int value);
    bool search(NodeT* node, int value);
    bool isComplete(NodeT* node, int index, int totalNodes);
    int countNodes(NodeT* node);
    std::string _toString(NodeT* node);
    void printTree(NodeT* node, int depth);
    void clear(NodeT* node);

public:
    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void print();
    std::string toString();
    void insert(int value);
    bool search(int value);
    bool isComplete();
    void clearTree();

    NodeT* getRoot() const { return root; }
    size_t getSize() const { return size; }
    void setRoot(NodeT* newRoot) { root = newRoot; }
};

#include "../src/complete_binary_tree.cpp"

#endif // tree_h