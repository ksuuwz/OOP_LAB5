#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Предварительное объявление классов и шаблонной функции
class ComputerItem;
class SystemUnit;

template <typename T, typename... Args>
std::shared_ptr<T> createAndStore(std::vector<std::shared_ptr<ComputerItem>>& storage, Args&&... args);

// Базовый полиморфный класс
class ComputerItem {
protected:
    std::string name;

    // Защищенный конструктор (запрещает создание напрямую)
    ComputerItem(const std::string& name) : name(name) {}

public:
    virtual ~ComputerItem() = default;

    // Чисто виртуальный метод для полиморфного вывода
    virtual void display() const = 0;

    // Шаблонная дружественная функция
    template <typename T, typename... Args>
    friend std::shared_ptr<T> createAndStore(std::vector<std::shared_ptr<ComputerItem>>& storage, Args&&... args);
};

// Производный класс для готовой сборки (ПК)
class SystemUnit : public ComputerItem {
private:
    std::string componentsList; // Состав сборки
    int count;                  // Количество компонентов

protected:
    SystemUnit(const std::string& name, const std::string& componentsList, int count)
        : ComputerItem(name), componentsList(componentsList), count(count) {
    }

public:
    void display() const override {
        std::cout << "СИСТЕМА: " << name << " (состоит из " << count << " компонентов)\n"
            << "    Состав: " << componentsList << "\n";
    }

    template <typename T, typename... Args>
    friend std::shared_ptr<T> createAndStore(std::vector<std::shared_ptr<ComputerItem>>& storage, Args&&... args);
};

// Производный класс для отдельного компонента
class HardwarePart : public ComputerItem {
protected:
    HardwarePart(const std::string& name) : ComputerItem(name) {}

public:
    void display() const override {
        std::cout << "- Компонент: " << name << "\n";
    }

    template <typename T, typename... Args>
    friend std::shared_ptr<T> createAndStore(std::vector<std::shared_ptr<ComputerItem>>& storage, Args&&... args);
};

// Шаблонная дружественная функция для создания объекта и сохранения в вектор
template <typename T, typename... Args>
std::shared_ptr<T> createAndStore(std::vector<std::shared_ptr<ComputerItem>>& storage, Args&&... args) {
    std::shared_ptr<T> obj = std::shared_ptr<T>(new T(std::forward<Args>(args)...));
    storage.push_back(obj);
    return obj;
}

int main() {
    // Установка русской локали для корректного отображения в консоли Visual Studio
    setlocale(LC_ALL, "Russian");

    // Хранилище (вектор)
    std::vector<std::shared_ptr<ComputerItem>> storage;

    std::cout << "--- процесс сборки оборудования ---\n\n";

    std::cout << "1. Собираем Игровой ПК:\n";
    std::cout << "   Добавлен компонент: Процессор\n";
    std::cout << "   Добавлен компонент: Видеокарта\n";
    std::cout << "   Добавлен компонент: ОЗУ\n";
    std::cout << "   Добавлен компонент: SSD-накопитель\n\n";
    std::cout << "   СОБРАНА СИСТЕМА: Игровой ПК\n\n";

    std::cout << "2. Собираем Офисный ПК:\n";
    std::cout << "   Добавлен компонент: Процессор (встроенный)\n";
    std::cout << "   Добавлен компонент: Материнская плата\n";
    std::cout << "   Добавлен компонент: Блок питания\n\n";
    std::cout << "   СОБРАНА СИСТЕМА: Офисный ПК\n\n";

    // Заполняем хранилище через шаблонную функцию-друг
    // Комплектующие игрового ПК
    createAndStore<HardwarePart>(storage, "Процессор");
    createAndStore<HardwarePart>(storage, "Видеокарта");
    createAndStore<HardwarePart>(storage, "ОЗУ");
    createAndStore<HardwarePart>(storage, "SSD-накопитель");
    createAndStore<SystemUnit>(storage, "Игровой ПК", "Процессор, Видеокарта, ОЗУ, SSD-накопитель", 4);

    // Комплектующие офисного ПК
    createAndStore<HardwarePart>(storage, "Процессор (встроенный)");
    createAndStore<HardwarePart>(storage, "Материнская плата");
    createAndStore<HardwarePart>(storage, "Блок питания");
    createAndStore<SystemUnit>(storage, "Офисный ПК", "Процессор (встроенный), Материнская плата, Блок питания", 3);

    std::cout << "--- вывод из хранилища ---\n\n";

    // Вывод содержимого хранилища через полиморфизм
    for (const auto& item : storage) {
        item->display();
    }

    return 0;
}