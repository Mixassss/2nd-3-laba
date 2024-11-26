#include "../include/stack.h"

void serializeText(Stack& stack, const string& filename) {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cout << "Не удалось открыть файл для записи." << endl;
        return;
    }

    Stack tempStack; // Временный стек для хранения элементов

    // Сериализация от дна к верху
    while (!stack.isEmpty()) {
        string value = stack.pop();
        ofs << value << endl; // Записываем элемент в файл
        tempStack.push(value); // Сохраняем элемент во временном стеке
    }

    // Восстанавливаем оригинальный стек
    while (!tempStack.isEmpty()) {
        stack.push(tempStack.pop());
    }

    ofs.close();
}

void deserializeText(Stack& stack, const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    string line;
    while (getline(ifs, line)) {
        stack.push(line); // Добавление элемента в стек
    }
    ifs.close();
}

void serializeBinary(Stack& stack, const string& filename) {
    ofstream ofs(filename, ios::binary);
    if (!ofs.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }

    Stack tempStack; // Временный стек для хранения элементов

    // Сериализация от дна к верху
    while (!stack.isEmpty()) {
        string value = stack.pop();
        size_t length = value.size();
        ofs.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Запись длины строки
        ofs.write(value.c_str(), length); // Запись самой строки
        tempStack.push(value); // Сохраняем элемент во временном стеке
    }

    // Восстанавливаем оригинальный стек
    while (!tempStack.isEmpty()) {
        stack.push(tempStack.pop());
    }

    ofs.close();
}

void deserializeBinary(Stack& stack, const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    while (true) {
        size_t length;
        if (ifs.read(reinterpret_cast<char*>(&length), sizeof(length))) {
            string value(length, ' ');
            ifs.read(&value[0], length); // Чтение строки
            stack.push(value); // Добавление элемента в стек
        } else {
            break; // Достигнут конец файла
        }
    }
    ifs.close();
}

int main() {
    Stack stack;
    stack.push("1");
    stack.push("2");
    stack.push("3");

    serializeText(stack, "stack.txt");
    serializeBinary(stack, "stack.bin");

    Stack stackFromText;
    deserializeText(stackFromText, "stack.txt");

    Stack stackFromBinary;
    deserializeBinary(stackFromBinary, "stack.bin");

    return 0;
}