#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    short arr[10];

    // Заполняем массив числами
    cout << "Введите 10 чисел типа short:" << endl;

    for (int i = 0; i < 10; i++)
    {
        cin >> arr[i];
    }

    // Выводим содержимое массива
    cout << "\nСодержимое массива:" << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    // Выводим адрес начала массива
    cout << "\nАдрес начала массива: " << (void*)arr << endl;

    // Выводим адрес и расстояние от начала массива
    cout << "\nАдреса элементов и расстояние от начала:" << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "Элемент arr[" << i << "]"
            << ", адрес: " << (void*)&arr[i]
            << ", расстояние: "
            << (char*)&arr[i] - (char*)arr
            << " байт" << endl;
    }

    return 0;

}