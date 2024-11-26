#include "../include/tree.h"

// Сериализация в текстовом формате
void serializeText(NodeT* node, std::ostream& out) {
    if (!node) {
        out << "- ";
        return;
    }
    out << node->data << " "; // Сериализуем данные узла
    serializeText(node->left, out); // Рекурсивно сериализуем левое поддерево
    serializeText(node->right, out); // Рекурсивно сериализуем правое поддерево
}

// Десериализация из текстового формата
NodeT* deserializeText(std::istream& in) {
    std::string value;
    in >> value;

    if (value == "-") {
        return nullptr;
    }

    NodeT* node = new NodeT(stoi(value)); // Создаем новый узел
    node->left = deserializeText(in); // Десериализуем левое поддерево
    node->right = deserializeText(in); // Десериализуем правое поддерево
    return node;
}

// Сериализация в бинарном формате
void serializeBinary(NodeT* node, std::ofstream& out) {
    if (!node) {
        out.put(0); // Используем 0 для обозначения пустого узла
        return;
    }
    out.put(1); // Используем 1 для обозначения узла с данными
    out.write(reinterpret_cast<const char*>(&node->data), sizeof(node->data)); // Сериализуем данные узла
    serializeBinary(node->left, out); // Рекурсивно сериализуем левое поддерево
    serializeBinary(node->right, out); // Рекурсивно сериализуем правое поддерево
}

// Десериализация из бинарного формата
NodeT* deserializeBinary(std::ifstream& in) {
    char isNode = in.get();
    if (isNode == 0) {
        return nullptr; // Если встретили 0, возвращаем nullptr
    }

    NodeT* node = new NodeT(0);
    in.read(reinterpret_cast<char*>(&node->data), sizeof(node->data)); // Десериализуем данные узла
    node->left = deserializeBinary(in); // Десериализуем левое поддерево
    node->right = deserializeBinary(in); // Десериализуем правое поддерево
    return node;
}

// Внешние функции для сериализации и десериализации
void serializeTreeToFileText(const CompleteBinaryTree& tree, const std::string& filename) {
    std::ofstream out(filename);
    if (out.is_open()) {
        serializeText(tree.getRoot(), out);
        out.close();
    }
}

void deserializeTreeFromFileText(CompleteBinaryTree& tree, const std::string& filename) {
    std::ifstream fin(filename);
    if (fin.is_open()) {
        tree.clearTree(); // Очищаем текущее дерево перед десериализацией
        tree.setRoot(deserializeText(fin)); // Устанавливаем корень
        fin.close();
    }
}

// Внешние функции для бинарной сериализации и десериализации
void serializeTreeToFileBinary(const CompleteBinaryTree& tree, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open()) {
        serializeBinary(tree.getRoot(), out);
        out.close();
    }
}

void deserializeTreeFromFileBinary(CompleteBinaryTree& tree, const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open()) {
        tree.clearTree(); // Очищаем текущее дерево перед десериализацией
        tree.setRoot(deserializeBinary(in)); // Устанавливаем корень
        in.close();
    }
}

int main() {
    CompleteBinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    
    std::cout << "Дерево:\n";
    tree.print();

    std::string textFile = "tree_text.txt";
    serializeTreeToFileText(tree, textFile);
    std::cout << "Сериализация дерева в текстовый файл.\n";

    CompleteBinaryTree newTreeText;
    deserializeTreeFromFileText(newTreeText, textFile);
    std::cout << "Десериализация дерева из текстового файла:\n";
    newTreeText.print();

    std::string binaryFile = "tree_binary.bin";
    serializeTreeToFileBinary(tree, binaryFile);
    std::cout << "Сериализация дерева в бинарный файл.\n";

    CompleteBinaryTree newTreeBinary;
    deserializeTreeFromFileBinary(newTreeBinary, binaryFile);
    
    std::cout << "Десериализация дерева из бинарного файла:\n";
    newTreeBinary.print();

    return 0;
}