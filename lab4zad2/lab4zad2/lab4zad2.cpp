#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <windows.h>
using namespace std;
// Иерархия классов: Человек
class Human {
public:
    virtual void showInfo() const = 0; // Чисто виртуальная функция
    virtual ~Human() {}
};
class Preschooler :
    public Human {
public:
    void showInfo() const override {
        cout << "Дошкольник (возраст 3-6 лет, посещает детский сад)." << endl;
    }
};
class Schoolchild :
    public Human {
public:
    void showInfo() const override {
        cout << "Школьник (возраст 7-17 лет, обучается в школе)." << endl;
    }
};
class Student :
    public Human {
public:
    void showInfo() const override {
        cout << "Студент (возраст 17-23 года, обучается в вузе или колледже)." << endl;
    }
};
class Working :
    public Human {
public:
    void showInfo() const override {
        cout << "Работающий (трудоустроенный специалист)." << endl;
    }
};
// Шаблонный класс для хранения массива указателей на объекты произвольного класса
template <typename T>class MyArray {
private:
vector<T*> data;public:
    // Добавление элемента в массив
    void add(T* item) {
        data.push_back(item);
    }

    // Перегрузка оператора [] с проверкой выхода за границы
    T* operator[](int index) {
        if (index < 0 || index >= data.size()) {
            throw out_of_range("Индекс " + to_string(index) + " вне диапазона массива!");
        }
        return data[index];
    }

    // Получение размера массива
    int size() const {
        return data.size();
    }

    // Деструктор для освобождения динамической памяти (защита от утечек)
    ~MyArray() {
        for (T* item : data) {
            delete item;
        }
        data.clear();
    }
};
int main() {
    // Настройка консоли для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Создание экземпляра шаблонного класса для иерархии Human
    MyArray<Human> peopleStorage;
    peopleStorage.add(new Preschooler());
    peopleStorage.add(new Schoolchild());
    peopleStorage.add(new Student());
    peopleStorage.add(new Working());

    // Вывод содержимого с помощью перегруженного оператора []
    cout << "Содержимое хранилища:" << endl;
    for (int i = 0; i < peopleStorage.size(); i++) {
        cout << "[" << i << "] ";
        peopleStorage[i]->showInfo();
    }

    // Обращение к несуществующему элементу с перехватом исключения out_of_range
    cout << "\nПопытка обратиться к несуществующему элементу (индекс 10):" << endl;
    try {
        peopleStorage[10]->showInfo();
    }
    catch (const out_of_range& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    cout << "\nПрограмма завершена. Память очищена." << endl;
    return 0;
}