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

void CompleteBinaryTree::serializeToTextFile(const string& filename) {
    ofstream out(filename);
    if (out.is_open()) {
        serializeText(root, out);
        out.close();
    }
}

void CompleteBinaryTree::serializeText(NodeT* node, ofstream& out) {
    if (node == nullptr) {
        out << "  ";  // Используем "null" для представления пустого узла
        return;
    }

    out << node->data << " "; // Сохраняем данные узла
    serializeText(node->left, out); // Сериализуем левое поддерево
    serializeText(node->right, out); // Сериализуем правое поддерево
}

void CompleteBinaryTree::deserializeFromTextFile(const string& filename) {
    ifstream in(filename);
    if (in.is_open()) {
        root = deserializeText(in);
        in.close();
    }
}

NodeT* CompleteBinaryTree::deserializeText(ifstream& in) {
    string value;
    in >> value;

    if (value == "  ") {
        return nullptr; // Если "null", возвращаем пустой узел
    }

    NodeT* node = new NodeT(stoi(value)); // Создаем узел с прочитанным значением
    node->left = deserializeText(in); // Десериализуем левое поддерево
    node->right = deserializeText(in); // Десериализуем правое поддерево

    return node;
}

void CompleteBinaryTree::serializeBinary(NodeT* node, ofstream& out) {
    if (node == nullptr) {
        out.write(reinterpret_cast<char*>(&node), sizeof(node));
        return;
    }

    out.write(reinterpret_cast<char*>(&node->data), sizeof(node->data)); // Сохраняем данные узла
    serializeBinary(node->left, out); // Сериализуем левое поддерево
    serializeBinary(node->right, out); // Сериализуем правое поддерево
}

// Десериализация из бинарного формата
NodeT* CompleteBinaryTree::deserializeBinary(ifstream& in) {
    NodeT* node = nullptr;
    in.read(reinterpret_cast<char*>(&node), sizeof(node));

    if (node == nullptr) {
        return nullptr; // Проверяем, нет ли пустого узла
    }

    node = new NodeT(0); // Создаем узел с временным значением
    in.read(reinterpret_cast<char*>(&node->data), sizeof(node->data)); // Читаем данные узла

    node->left = deserializeBinary(in); // Десериализуем левое поддерево
    node->right = deserializeBinary(in); // Десериализуем правое поддерево

    return node;
}

// Метод сериализации в файл в бинарном формате
void CompleteBinaryTree::serializeToBinaryFile(const string& filename) {
    ofstream out(filename, ios::binary);
    if (out.is_open()) {
        serializeBinary(root, out);
        out.close();
    }
}

// Метод десериализации из файла в бинарном формате
void CompleteBinaryTree::deserializeFromBinaryFile(const string& filename) {
    ifstream in(filename, ios::binary);
    if (in.is_open()) {
        root = deserializeBinary(in);
        in.close();
    }
}