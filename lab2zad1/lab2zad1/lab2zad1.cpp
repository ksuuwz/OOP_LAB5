#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// Родительский класс
class Publication
{
protected:
    string title;
    float price;

public:
    // Ввод данных
    virtual void getdata()
    {
        cout << "Введите название: ";
        getline(cin >> ws, title);

        cout << "Введите цену: ";
        cin >> price;
    }

    // Вывод данных
    virtual void putdata()
    {
        cout << "Название: " << title << endl;
        cout << "Цена: " << price << " руб." << endl;
    }
};

// Класс книги
class Book : public Publication
{
private:
    int pages;

public:
    void getdata() override
    {
        Publication::getdata();

        cout << "Введите количество страниц: ";
        cin >> pages;
    }

    void putdata() override
    {
        Publication::putdata();

        cout << "Количество страниц: " << pages << endl;
    }
};

// Класс аудиозаписи
class Type : public Publication
{
private:
    int time;

public:
    void getdata() override
    {
        Publication::getdata();

        cout << "Введите время записи в минутах: ";
        cin >> time;
    }

    void putdata() override
    {
        Publication::putdata();

        cout << "Время записи: " << time << " мин." << endl;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Book book;
    Type audio;

    cout << "=== ВВОД ДАННЫХ О КНИГЕ ===" << endl;
    book.getdata();

    cout << endl;
    cout << "=== ВВОД ДАННЫХ ОБ АУДИОЗАПИСИ ===" << endl;
    audio.getdata();

    cout << endl;
    cout << "=== ИНФОРМАЦИЯ О КНИГЕ ===" << endl;
    book.putdata();

    cout << endl;
    cout << "=== ИНФОРМАЦИЯ ОБ АУДИОЗАПИСИ ===" << endl;
    audio.putdata();

    return 0;
}