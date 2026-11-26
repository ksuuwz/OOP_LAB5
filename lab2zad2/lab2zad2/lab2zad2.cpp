#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// ---------- Базовый класс: Публикация ----------
class publication
{
private:
    string title;                       // Название
public:
    void getdata()
    {
        cout << "Введите название: ";
        getline(cin, title);
    }
    void putdata() const
    {
        cout << "Название: " << title << endl;
    }
};

// ---------- Базовый класс: Продажи ----------
class sales
{
private:
    float money[3];                     // Стоимость продаж за 3 месяца
public:
    void getdata()
    {
        cout << "Введите стоимость продаж за последние 3 месяца:" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "  Месяц " << i + 1 << ": ";
            cin >> money[i];
        }
    }
    void putdata() const
    {
        cout << "Продажи за 3 месяца:" << endl;
        for (int i = 0; i < 3; i++)
            cout << "  Месяц " << i + 1 << ": " << money[i] << endl;
    }
};

// ---------- Производный класс: Книги ----------
class book : public publication, public sales
{
private:
    int pages;                          // Количество страниц
public:
    void getdata()
    {
        publication::getdata();         // название
        cout << "Введите количество страниц: ";
        cin >> pages;
        sales::getdata();               // продажи
    }
    void putdata() const
    {
        publication::putdata();         // название
        cout << "Страниц: " << pages << endl;
        sales::putdata();               // продажи
    }
};

// ---------- Производный класс: Аудиокниги ----------
class type : public publication, public sales
{
private:
    float minutes;                      // Минуты записи
public:
    void getdata()
    {
        publication::getdata();         // название
        cout << "Введите время записи (минуты): ";
        cin >> minutes;
        sales::getdata();               // продажи
    }
    void putdata() const
    {
        publication::putdata();         // название
        cout << "Время записи: " << minutes << " мин." << endl;
        sales::putdata();               // продажи
    }
};

// ---------- Главная функция ----------
int main()
{
    SetConsoleCP(1251);                 // кодировка ввода
    SetConsoleOutputCP(1251);           // кодировка вывода

    book b;
    type t;

    cout << "=== Ввод данных о книге ===" << endl;
    b.getdata();

    cin.ignore(1000, '\n');             // очистка буфера перед getline
    cout << endl << "=== Ввод данных об аудиокниге ===" << endl;
    t.getdata();

    cout << endl << "=== Данные о книге ===" << endl;
    b.putdata();

    cout << endl << "=== Данные об аудиокниге ===" << endl;
    t.putdata();

    system("pause");
    return 0;
}