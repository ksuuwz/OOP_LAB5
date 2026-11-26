#include <iostream>
#include <string>
using namespace std;

// Типы книг
enum BookType
{
    Fiction = 1,    // Художественная
    Technical = 2   // Техническая
};

// Класс книги
class Book
{
public:
    string author;
    string title;
    BookType type;

    // Конструктор с тремя параметрами
    Book(string a, string t, BookType tp)
    {
        if (a.empty() || t.empty())
        {
            throw invalid_argument("Автор и название книги не могут быть пустыми!");
        }

        author = a;
        title = t;
        type = tp;
    }
};

// Процедура подсчёта книг без switch
void countBooks(Book books[], int size)
{
    int fictionCount = 0;
    int technicalCount = 0;

    for (int i = 0; i < size; i++)
    {
        if (books[i].type == Fiction)
        {
            fictionCount++;
        }
        else if (books[i].type == Technical)
        {
            technicalCount++;
        }
    }

    cout << "\nКоличество художественных книг: "
        << fictionCount << endl;

    cout << "Количество технических книг: "
        << technicalCount << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Создаём библиотеку из нескольких книг
    Book books[] = {
        Book("Александр Пушкин", "Капитанская дочка", Fiction),
        Book("Лев Толстой", "Война и мир", Fiction),
        Book("Фёдор Достоевский", "Преступление и наказание", Fiction),
        Book("Бьярне Страуструп", "Язык программирования C++", Technical),
        Book("Эндрю Таненбаум", "Архитектура компьютера", Technical)
    };

    int size = sizeof(books) / sizeof(books[0]);

    // Выводим все книги библиотеки
    cout << "Список книг библиотеки:\n" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << "Автор: " << books[i].author << endl;
        cout << "Название: " << books[i].title << endl;

        if (books[i].type == Fiction)
        {
            cout << "Тип: художественная" << endl;
        }
        else
        {
            cout << "Тип: техническая" << endl;
        }

        cout << "------------------------" << endl;
    }

    // Вызываем процедуру подсчёта без switch
    countBooks(books, size);

    return 0;
}