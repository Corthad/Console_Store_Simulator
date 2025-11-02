#include "storage.h"
#include <iostream>
#include <vector>

const std::string storage_debug_menu[20] {
    "Меню отладки склада.\n",
    "1.   Считать список товаров с файла\n",
    "2.   Отобразить список товаров;\n",
    "3.   Добавить товар на склад;\n",
    "4.   Удалить товар со склада;\n",
    "5.   Изменить количество товара;\n",
    "6.   Изменить цену товара;\n",
    "7.   Изменить вес товара;\n",
    "8.   Сохранить список товаров в файл\n",
    "9.   Завершить программу\n"

};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка кодировки UTF-8
    int enter_the_activity_number;
    std::string a = "";
    int b;
    int c;
    int d;
    int e;
    bool exit_the_program_is_pressed = false;
    while (true) {
        std::cout << "\033c";
        for (int i = 0; i < 20 && storage_debug_menu[i] != ""; i++) {
            std::cout << storage_debug_menu[i];
        }
        std::cout << "Введите номер команды: ";
        std::cin >> enter_the_activity_number;
        std::cout << "\033c";
        switch(enter_the_activity_number) {
            case 1: 
                storage::load_data();
                std::cout << "Выполнено чтение списка товаров из файла.\n";
                system("pause");
                break;
            case 2: 
                std::cout << "Список товаров, доступных на складе:\n";
                storage::show_data();
                system("pause");
                break;
            case 3: 
                std::cout << "Добавление товара. Введите данные в следующем виде(порядке): имя цена количество вес.\n";
                std::cin >> a;
                std::cin >> b >> c >> d;
                storage::add_item(a, b, c, d);
                system("pause");
                break;
            case 4: 
                storage::show_data();
                std::cout << "Введите индекс товара, который хотите удалить.\n";
                std::cin >> e;
                storage::del_item(e);
                system("pause");
                break;
            case 5: 
                storage::show_data();
                std::cout << "Введите новое количество товара в следующем виде: индекс товара, новое значение колличества.\n";
                std::cin >> e >> c;
                storage::change_item_qty(e, c);
                system("pause");
                break;
            case 6: 
                storage::show_data();
                std::cout << "Введите новую цену товара в следующем виде: индекс товара, новое значение цены.\n";
                std::cin >> e >> d;
                storage::set_item_price(e, d);
                system("pause");
                break;
            case 7: 
                storage::show_data();
                std::cout << "Введите новый вес товара в следующем виде: индекс товара, новое значение веса.\n";
                std::cin >> e >> b;
                storage::set_item_weight(e, b);
                system("pause");
                break;
            case 8: 
                storage::save_data();
                std::cout << "Выполнено сохранение списка товаров в файл.\n";
                system("pause");
                break;
            case 9: 
                exit_the_program_is_pressed = true;
                break;
        }
        if (exit_the_program_is_pressed) {
            std::cout << "Инициирован выход из программы.\n";
            break;
        }
    }
    return 0;
}