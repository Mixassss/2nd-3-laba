#include "../include/tree.h"

NodeT::NodeT(int value) {
    data = value;
    left = nullptr; 
    right = nullptr;
}

CompleteBinaryTree::CompleteBinaryTree() {
    root = nullptr;
    size = 0;
}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear(root);
}

void CompleteBinaryTree::insert(int value) {
    root = _insert(root, value);
    size++;
}

NodeT* CompleteBinaryTree::_insert(NodeT* node, int value) {
    if (node == nullptr) {
        return new NodeT(value);
    }

    if (value < node->data) {
        node->left = _insert(node->left, value);
    } else {
        node->right = _insert(node->right, value);
    }

    return node;
}

bool CompleteBinaryTree::search(int value) {
    return search(root, value);
}

bool CompleteBinaryTree::search(NodeT* node, int value) {
    if (node == nullptr) return false;
    if (node->data == value) return true;
    return search(node->left, value) || search(node->right, value);
}

bool CompleteBinaryTree::isComplete() {
    return isComplete(root, 0, countNodes(root));
}

bool CompleteBinaryTree::isComplete(NodeT* node, int index, int totalNodes) {
    if (node == nullptr) return true;
    if (index >= totalNodes) return false;

    return isComplete(node->left, 2 * index + 1, totalNodes) &&
           isComplete(node->right, 2 * index + 2, totalNodes);
}

int CompleteBinaryTree::countNodes(NodeT* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

std::string CompleteBinaryTree::toString() {
    return _toString(root);
}

std::string CompleteBinaryTree::_toString(NodeT* node) {
    if (node == nullptr) return "";

    std::ostringstream oss;
    oss << node->data << " ";
    oss << _toString(node->left);
    oss << _toString(node->right);

    return oss.str();
}

void CompleteBinaryTree::print() {
    printTree(root, 0);
    std::cout << std::endl;
}

void CompleteBinaryTree::printTree(NodeT* node, int depth) {
    if (node == nullptr) return;
    printTree(node->right, depth + 1);
    std::cout << std::setw(4 * depth) << " " << node->data << std::endl;
    printTree(node->left, depth + 1);
}

void CompleteBinaryTree::clear(NodeT* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void CompleteBinaryTree::clearTree() {
    clear(root);
    root = nullptr;
    size = 0;
}