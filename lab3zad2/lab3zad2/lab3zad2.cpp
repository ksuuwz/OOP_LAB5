#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>

// Базовый полиморфный класс
class Base {
protected:
    int value; // Храним случайное число, определившее тип

public:
    Base(int val) : value(val) {}

    virtual ~Base() {
        // Деструктор базового класса
    }

    // Виртуальный метод для демонстрации разницы в поведении
    virtual void action() const {
        std::cout << "    -> Проверка: Число " << value << " является базовым.\n";
    }

    // Виртуальный метод клонирования для корректного копирования в функцию add
    virtual Base* clone() const {
        return new Base(*this);
    }

    int getValue() const { return value; }
};

// Производный полиморфный класс
class Derived : public Base {
public:
    Derived(int val) : Base(val) {}

    ~Derived() override {
        // Деструктор производного класса
    }

    // Переопределенный метод (полиморфизм) — разное поведение
    void action() const override {
        std::cout << "    -> Проверка: Число " << value << " является НЕЧЕТНЫМ.\n";
    }

    Base* clone() const override {
        return new Derived(*this);
    }
};

// Производный класс для четных чисел (чтобы логика четности была явно разделена)
class EvenDerived : public Base {
public:
    EvenDerived(int val) : Base(val) {}

    ~EvenDerived() override {}

    void action() const override {
        std::cout << "    -> Проверка: Число " << value << " является ЧЕТНЫМ.\n";
    }

    Base* clone() const override {
        return new EvenDerived(*this);
    }
};

// Функция add: принимает объект и помещает его копию в общее хранилище
void add(const Base& obj, std::vector<Base*>& storage) {
    storage.push_back(obj.clone());
}

int main() {
    // Установка русской локали для корректного отображения в Visual Studio
    setlocale(LC_ALL, "Russian");

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    // Общее хранилище
    std::vector<Base*> storage;

    std::cout << "--- генерация случайных чисел ---\n\n";

    int totalSteps = 6;
    for (int i = 1; i <= totalSteps; ++i) {
        int randomNumber = (rand() % 90) + 10; // Случайное двузначное число от 10 до 99

        if (randomNumber % 2 == 0) {
            std::cout << "Шаг " << i << " (выпало " << randomNumber << "):\n";
            std::cout << "Создан объект: Четное число " << randomNumber << "\n\n";

            EvenDerived obj(randomNumber);
            add(obj, storage);
        }
        else {
            std::cout << "Шаг " << i << " (выпало " << randomNumber << "):\n";
            std::cout << "Создан объект: Нечетное число " << randomNumber << "\n\n";

            Derived obj(randomNumber);
            add(obj, storage);
        }
    }

    std::cout << "--- результат проверки чисел ---\n\n";

    // Достаем объекты по очереди из хранилища и демонстрируем полиморфизм
    for (size_t i = 0; i < storage.size(); ++i) {
        std::cout << "Объект #" << (i + 1) << ":\n";
        // Полиморфный вызов метода action()
        storage[i]->action();
    }

    std::cout << "\n--- освобождение ресурсов ---\n";

    // Удаляем элементы из кучи
    for (Base* item : storage) {
        delete item;
    }
    storage.clear();

    std::cout << "Все объекты удалены. Программа завершена.\n";

    return 0;
}