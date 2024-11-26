#include "../include/arr.h"

Array areadFile(const string& path, const string& nameStruct) {
    Array arr;
    string str;
    ifstream fin(path);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return arr;
    }

    while (getline(fin, str)) {
        cout << "Читанная строка: " << str << endl; // Отладочная информация
        stringstream ss(str);
        string tokens;
        getline(ss, tokens, ' '); // Первый токен

        if (tokens == nameStruct) {
            while (getline(ss, tokens, ' ')) {
                cout << "Добавляем токен: " << tokens << endl; // Отладочная информация
                arr.addToEnd(tokens);
            }
        }
    }
    fin.close();
    return arr;
}

void serializeText(const Array& array, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }
    for (size_t i = 0; i < array.getSize(); ++i) {
        fout << array.getIndex(i) << " ";
    }
    cout << "Сериализация массива завершена. Записано: " << array.getSize() << " элементов." << endl; // Отладочная информация
    fout.close();
}

Array deserializeText(const string& filename) {
    Array arr;
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return arr;
    }

    string value;
    while (fin >> value) {
        arr.addToEnd(value);
    }
    cout << "Десериализация массива завершена. Считано: " << arr.getSize() << " элементов." << endl; // Отладочная информация
    fin.close();
    return arr;
}

void serializeBinary(const Array& arr, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) {
        cerr << "Не удалось открыть бинарный файл для записи!" << endl;
        return;
    }

    size_t size = arr.getSize();
    fout.write(reinterpret_cast<const char*>(&size), sizeof(size)); // Записываем размер

    for (size_t i = 0; i < size; ++i) {
        string value = arr.getIndex(i);
        size_t length = value.size();
        fout.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Записываем длину строки
        fout.write(value.c_str(), length); // Записываем саму строку
    }
    cout << "Бинарная сериализация массива завершена. Записано: " << size << " элементов." << endl; // Отладочная информация
    fout.close();
}

Array deserializeBinary(const string& filename) {
    Array arr;
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть бинарный файл при чтении!" << endl;
        return arr;
    }

    size_t size;
    fin.read(reinterpret_cast<char*>(&size), sizeof(size)); // Читаем размер
    cout << "Десериализация из бинарного файла. Ожидаем размер: " << size << endl; // Отладочная информация

    for (size_t i = 0; i < size; ++i) {
        size_t length;
        fin.read(reinterpret_cast<char*>(&length), sizeof(length)); // Читаем длину строки
        string value(length, '\0'); // создаем строку нужного размера
        fin.read(&value[0], length); // считываем строку
        arr.addToEnd(value);
    }
    cout << "Бинарная десериализация завершена. Считано: " << arr.getSize() << " элементов." << endl; // Отладочная информация
    fin.close();
    return arr;
}


int main() {
    string aFile = "array.txt";
    string aBinaryFile = "arr.bin";
    string nameStruct = "MyArray";

    // Чтение данных из файла
    Array arr = areadFile(aFile, nameStruct);
    arr.ShowArray();

    // Сериализация в текстовом формате
    serializeText(arr, "outputArr.txt");

    Array arrFromText = deserializeText("outputArr.txt");
    arrFromText.ShowArray();

    // Сериализация в бинарном формате
    serializeBinary(arr, aBinaryFile);

    // Десериализация из бинарного формата
    Array arrFromBinary = deserializeBinary(aBinaryFile);
    arrFromBinary.ShowArray();

    return 0;
}