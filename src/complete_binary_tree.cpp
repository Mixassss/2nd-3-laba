#include "../include/tree.h"

NodeT::NodeT(int value) {
    data= value;
    left = nullptr; 
    right = nullptr;
}

CompleteBinaryTree::CompleteBinaryTree() {
    root = nullptr;
    size = 0;
}

void CompleteBinaryTree::insert(int value) {
    root = _insert(root, value);
    size++;
}

NodeT* CompleteBinaryTree::_insert(NodeT* node, int value) {
    if (node == nullptr) { // Если текущий узел равен нулю
        return new NodeT(value); // Создаем новый узел и возвращаем его
    }

    if (value < node->data) { // Сравниваем значения
        node->left = _insert(node->left, value); // Рекурсивно вставляем в левое поддерево
    } else {
        node->right = _insert(node->right, value); // Рекурсивно вставляем в правое поддерево
    }

    return node; // Возвращаем текущий узел
}

bool CompleteBinaryTree::search(int value) {
    return search(root, value);
}

bool CompleteBinaryTree::search(NodeT* node, int value) {
    if (node == nullptr) return false; // Если нет значений
    if (node->data == value) return true;
    return search(node->left, value) || search(node->right, value);
}

bool CompleteBinaryTree::isComplete() {
    return isComplete(root, 0, countNodes(root));
}

bool CompleteBinaryTree::isComplete(NodeT* node, int index, int totalNodes) {
    if (node == nullptr) return true; // Если узел пустой, это считается полным
    if (index >= totalNodes) return false; // Если индекс больше или равен количеству узлов, не полное

    return isComplete(node->left, 2 * index + 1, totalNodes) && // Проверяем рекурсивно для левого и правого поддеревьев
           isComplete(node->right, 2 * index + 2, totalNodes);
}

int CompleteBinaryTree::countNodes(NodeT* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

string CompleteBinaryTree::toString() {
    return _toString(root);
}

string CompleteBinaryTree::_toString(NodeT* node) {
    if (node == nullptr) return "";

    ostringstream oss;
    oss << node->data << " "; // Добавляем текущий узел

    oss << _toString(node->left); // Рекурсивно добавляем элементы из левого поддерева
    oss << _toString(node->right); // Рекурсивно добавляем элементы из правого поддерева

    return oss.str();
}

void CompleteBinaryTree::print() {
    printTree(root, 0);
    cout << endl;
}

void CompleteBinaryTree::printTree(NodeT* node, int depth) {
    if (node == nullptr) return;
    printTree(node->right, depth + 1);
    cout << setw(4 * depth) << " " << node->data << endl;
    printTree(node->left, depth + 1);
}

void CompleteBinaryTree::clear(NodeT* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear(root);
}

// Сериализация дерева
string CompleteBinaryTree::serializeToText() {
    ostringstream oss;
    _serializeToText(root, oss);
    return oss.str();
}

void CompleteBinaryTree::_serializeToText(NodeT* node, ostringstream& oss) {
    if (node == nullptr) {
        oss << "# "; // Используем "#" для обозначения пустых узлов
        return;
    }
    oss << node->data << " "; // Сохраняем значение узла
    _serializeToText(node->left, oss); // Рекурсия для левого поддерева
    _serializeToText(node->right, oss); // Рекурсия для правого поддерева
}

// Десериализация дерева
void CompleteBinaryTree::deserialize(const string& data) {
    istringstream iss(data);
    root = deserialize(iss);
}

NodeT* CompleteBinaryTree::deserialize(istringstream& iss) {
    string value;
    iss >> value;
    if (value == "#") return nullptr; // Если пустой узел, возвращаем nullptr
  
    NodeT* node = new NodeT(stoi(value)); // Создаем новый узел
    node->left = deserialize(iss); // Десериализация левого поддерева
    node->right = deserialize(iss); // Десериализация правого поддерева
    return node;
}