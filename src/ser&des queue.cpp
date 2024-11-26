#include "../include/queue.h"

void serializeQueueText(const Queue& que, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    // Копируем данные в временную очередь
    Queue tempQueue = que;
    while (!tempQueue.isempty()) {
        fout << tempQueue.pop() << endl; // Записываем и удаляем элемент
    }

    fout.close();
}

Queue deserializeQueueText(const string& filename) {
    Queue que;
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return que;
    }

    string value;
    while (getline(fin, value)) {
        if (!value.empty()) {
            que.push(value); // Добавляем данные в очередь
        }
    }

    fin.close();
    return que;
}

void serializeQueueBinary(const Queue& que, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    // Копируем данные в временную очередь
    Queue tempQueue = que;
    while (!tempQueue.isempty()) {
        string value = tempQueue.pop();
        size_t length = value.size();
        fout.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(value.c_str(), length); // Записываем строку
    }

    fout.close();
}

Queue deserializeQueueBinary(const string& filename) {
    Queue que;
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return que;
    }

    while (fin.peek() != ifstream::traits_type::eof()) {
        size_t length;
        fin.read(reinterpret_cast<char*>(&length), sizeof(length)); // Читаем длину строки

        string value(length, ' ');
        fin.read(&value[0], length); // Читаем строку
        if (fin.gcount() != static_cast<streamsize>(length)) {
            cerr << "Ошибка чтения данных" << endl;
            break;
        }
        que.push(value); // Добавляем данные в очередь
    }

    fin.close();
    return que;
}

int main() {
    Queue que;

    que.push("4");
    que.push("5");
    que.push("6");
    serializeQueueText(que, "queue.txt");
    Queue queFromFileText = deserializeQueueText("queue.txt");

    // Пример использования бинарной сериализации
    Queue queBinary;
    queBinary.push("7");
    queBinary.push("8");
    queBinary.push("9");
    serializeQueueBinary(queBinary, "queue.bin");

    Queue queFromFileBinary = deserializeQueueBinary("queue.bin");

    return 0;
}

