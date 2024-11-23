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
    string _toString(NodeT* node);
    void printTree(NodeT* node, int depth);
    void clear(NodeT* node);
    void serializeText(NodeT* node, ofstream& out);
    NodeT* deserializeText(ifstream& in);
    void serializeBinary(NodeT* node, ofstream& out);
    NodeT* deserializeBinary(std::ifstream& in);

public:
    CompleteBinaryTree();
    ~CompleteBinaryTree();
    
    void print();
    string toString();
    void insert(int value);
    bool search(int value);
    bool isComplete();
    void serializeToBinaryFile(const string& filename);
    void deserializeFromBinaryFile(const string& filename);
    void deserializeFromTextFile(const string& filename);
    void serializeToTextFile(const string& filename);
};

#include "../src/complete_binary_tree.cpp"

#endif // TREE_H