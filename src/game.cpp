#include <iostream>
#include <vector>
#include <limits>
#include <windows.h>

#include "game.h"
#include "buyer.h"
#include "seller.h"
#include "storage.h"

bool exit_to_main_menu;

//Создано для отладки склада. В будущем можно удалить или перенести в отдельный файл
void storage_debug_mode() {
    
    int activity_id;

    int item_id;
    std::string item_name;
    int item_price;
    int item_qty;
    int item_weight;

    bool no_function_error = false;

    while(true) {
        std::cout << "\033c";
        
        for (const std::string &row : storage_debug_menu) {
            std::cout << row << "\n";
        }

        item_id = -1;
        item_name = "";
        item_price = -1;
        item_qty = -1;
        item_weight = -1;

        std::cout << "Введите номер команды: ";
        std::cin >> activity_id;

        std::cout << "\033c";

        switch(activity_id) {
            case 1: 
                storage::load_data();
                std::cout << "Выполнено чтение списка товаров из файла.\n";
                break;
            case 2: 
                std::cout << "Список товаров, доступных на складе:\n";
                storage::show_data();
                break;
            case 3: 
                std::cout << "Добавление товара на склад.\n";
                while(item_name == "" || item_price <= 0 || item_qty <= 0 || item_weight <= 0) {
                    std::cout << "Введите имя товара: ";

                    std::cin.clear();                                                   //!
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //! Нужно перед std::getline()
                    std::getline(std::cin, item_name);

                    std::cout << "Введите данные товара в следующем порядке: [цена] [количество] [вес]: ";
                    std::cin >> item_price >> item_qty >> item_weight;

                    if(std::cin.fail()) {
                        item_name = "";
                        item_price = 0;
                        item_qty = 0;
                        item_weight = 0;
                    }

                    //Костыль для отлова отрицательных значений. Необходимо изменить функцию add_item
                    item_price = std::max(item_price, 0);
                    item_qty = std::max(item_qty, 0);
                    item_weight = std::max(item_weight, 0);

                    no_function_error = storage::add_item(item_name, item_price, item_qty, item_weight);
                    if(no_function_error) {
                        std::cout << "\033c";
                        std::cout << "Ошибка при вводе данных товара.\n";
                    }
                }
                std::cout << "Товары успешно добавлены.\n";
                break;
            case 4: 
                while(0 > item_id || item_id >= storage::items.size()) {
                    storage::show_data();
                    std::cout << "Введите индекс товара, который хотите удалить: ";
                    std::cin >> item_id;
                    
                    if(std::cin.fail()) {
                        item_id = -1;
                    }

                    no_function_error = storage::del_item(item_id);
                    if(no_function_error) {
                        std::cout << "\033c";
                        std::cout << "Неправильно введён индекс товара!\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                std::cout << "Удаление товара прошло успешно.\n";
                break;
            case 5: 
                while((0 > item_id || item_id >= storage::items.size()) || (item_qty == 0)) {
                    storage::show_data();
                    std::cout << "Для изменения количества товара, введите в следующем порядке: [индекс_товара] [значение: 'x'  или '-x']: ";
                    std::cin >> item_id >> item_qty;

                    if(std::cin.fail()) {
                        item_id = -1;
                        item_qty = 0;
                    }

                    no_function_error = storage::change_item_qty(item_id, item_qty);
                    if(no_function_error) {
                        std::cout << "\033c";
                        std::cout << "Неверно введён индекс товара и/или значение!\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        item_qty = 0;
                    }
                    item_id = 0;
                }
                std::cout << "Изменение количества товара выполнено успешно.\n";
                break;
            case 6: 
                while((0 > item_id || item_id >= storage::items.size()) || (item_price <= 0)) {
                    storage::show_data();
                    std::cout << "Введите новую цену товара в следующем виде: [индекс_товара] [цена]: ";
                    std::cin >> item_id >> item_price;

                    if(std::cin.fail()) {
                        item_id = -1;
                        item_price = -1;
                    }

                    item_price = std::max(item_price, 0);

                    no_function_error = storage::set_item_price(item_id, item_price);
                    if(no_function_error) {
                        std::cout << "\033c";
                        std::cout << "Неверно введён индекс товара и/или цена!\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        item_price = -1;
                    }
                    item_id = 0;
                }
                std::cout << "Изменение цены выполнено успешно!\n";
                break;
            case 7: 
                while((0 > item_id || item_id >= storage::items.size()) || (item_weight <= 0)) {
                    storage::show_data();
                    std::cout << "Введите новый вес товара в следующем виде: [индекс_товара] [вес]:\n";
                    std::cin >> item_id >> item_weight;

                    if(std::cin.fail()) {
                        item_id = -1;
                        item_weight = -1;
                    }

                    item_weight = std::max(item_weight, 0);

                    no_function_error = storage::set_item_weight(item_id, item_weight);
                    if(no_function_error) {
                        std::cout << "\033c";
                        std::cout << "Неверно введён индекс товара и/или вес!\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        item_weight = -1;
                    }
                    item_id = 0;
                }
                std::cout << "Изменение веса выполнено успешно!\n";
                break;
            case 8: 
                storage::save_data();
                std::cout << "Сохранение списка в файл выполнено успешно.\n";
                break;
            case 9: 
                exit_to_main_menu = true;
                break;
            default:
                std::cout << "Неизвестный номер команды.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }

        if (exit_to_main_menu) {
            std::cout << "\033c";
            break;
        }

        system("pause");
    }
}

void game() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int user_type_id = 0;

    std::cout << "\033c";

    while (true) {
        exit_to_main_menu = false;

        std::cout << "Добро пожаловать в консольный симулятор магазина.\n";
        std::cout << "Выберете тип пользователя.\n";
        std::cout << "1. Покупатель;\n";
        std::cout << "2. Продавец;\n";
        std::cout << "3. Разработчик (отладка функций склада);\n";
        std::cout << "0. Выход из игры.\n";

        
        std::cin >> user_type_id;
        bool exit_the_game = false;
        

        if (std::cin.fail()) {
            user_type_id = 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033c";
            std::cout << "Используйте для ввода только числа. \n";
        }
        else {
            std::cout << "\033c";
            switch (user_type_id) {
                case 0:
                    exit_the_game = true;
                    break;
                case 1: 
                    buyer::start_buyer();
                    std::cout << "Этот раздел еще находится в разработке. Прошу проявить терпение.\n";
                    system("pause");
                    std::cout << "\033c";
                    break;
                case 2: 
                    //start_seller();
                    std::cout << "Этот раздел еще находится в разработке. Прошу проявить терпение.\n";
                    system("pause");
                    std::cout << "\033c";
                    break;
                case 3: 
                    storage_debug_mode();
                    break;
                default:
                    std::cout << "Введен неверный номер типа пользователя.\n";  
                    system("pause");
                    std::cout << "\033c";                  
            }
            if (exit_the_game) {
                break;
            }
        }
    }
}