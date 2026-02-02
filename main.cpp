#include "OOP_Lab_String.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace OOP_Lab;

void test_format()
{
    std::cout << ">>> format test begin\n";

    // 1. Форматирование int
    {
        const char* str = "Value: %i";
        String result = format(str, 9, 42);
        result.print(); // Ожидаем: Value: 42

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    // 2. Форматирование double
    {
        const char* str = "Pi = %d3";
        String result = format(str, 9, 3.14159);
        result.print(); // Ожидаем: Pi = 3.142

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    // 3. Форматирование char
    {
        const char* str = "Symbol: %c";
        String result = format(str, 11, 'X');
        result.print(); // Ожидаем: Symbol: X

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    // 4. Форматирование строки
    {
        const char* str = "Hello, %s!";
        String result = format(str, 11, "world");
        result.print(); // Ожидаем: Hello, world!

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    // 5. Смешанное форматирование
    {
        const char* str = "[%i] %s: %d2";
        String result = format(str, 13, 7, "value", 12.345);
        result.print(); // Ожидаем: [7] value: 12.35

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    // 6. Некорректный спецификатор — должен проигнорировать
    {
        const char* str = "Test %x %z %";
        String result = format(str, 17, 100, 'A');
        result.print(); // Ожидаем: Test %x %z %

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    // 7. Пустая строка
    {
        const char* str = "";
        String result = format(str, 1);
        result.print(); // Ожидаем: (ничего)
    }

    // 8. Неправильная длина строки
    {
        const char* str = "Only format"; // длина 11
        String result = format(str, 4, 42); // Не вся строка
        result.print(); // Ожидаем: Only

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    // 9. RT трока
    {
        char str[100]{};
        std::cin.getline(str, 100);
        size_t len = 0;
        while (str[len] != '\0')
            ++len;
        String result = format(str, len, 42);
        result.print();

        std::cout<< "\n\t"<<result.getSize()<<'\n';
    }

    std::cout << ">>> format test end\n";
}

int main()
{
    // Установка локали для корректного вывода
    SetConsoleOutputCP(CP_UTF8);

    test_format();
    std::cin.ignore();
    return 0;
}