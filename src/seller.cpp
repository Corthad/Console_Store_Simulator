#include "seller.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>

#include "storage.h"
#include "utils.h"

int seller::loop() {

    int activity_idx;

    int item_idx;
    std::string item_name;
    unsigned item_price;
    unsigned item_qty;
    unsigned item_weight;

    while(true) {
        int code = 0;

        // Запрашиваем индекс действия
        activity_idx = utils::request("Меню склада", seller::storage_debug_menu);
        std::cout << "\033c";
        switch(activity_idx) {
            case 1: {
                storage::load_data();
                std::cout << "Выполнено чтение списка товаров из файла.\n";
                break;
            }
            case 2: {
                std::cout << "Список товаров, доступных на складе:\n";
                utils::show_data(storage::items);
                break;
            }
            case 3: {
                while(true) {
                    std::cout << "Добавление товара.\n";

                    item_name = utils::input("Имя товара: ");
                    
                    for(int i = 0; i < 3; ++i) {
                        std::string header;
                        unsigned* value = nullptr;
                        switch(i) {
                            case 0: {
                                header = "Цена: ";
                                value = &item_price;
                                break;
                            }
                            case 1: {
                                header = "Количество: ";
                                value = &item_qty;
                                break;
                            }
                            case 2: {
                                header = "Вес: ";
                                value = &item_weight;
                                break;
                            }
                        }
                        *value = utils::get_unum(header);
                    }

                    code = storage::add_item(item_name, item_price, item_qty, item_weight);
                    if(code > 0) {
                        std::cout << "\033c";
                        std::cout << "Неправильно введены данные!\n";
                        continue;
                    }
                    break;
                }

                std::cout << "Успешно!\n";
                break;
            }
            case 4: {
                if(storage::items.empty()) {
                    std::cout << "Хранилище пустое!\n";
                    break;
                }
                while(true) {
                    utils::show_data(storage::items);
                    std::cout << "Введите индекс товара, который хотите удалить:\n";
                    
                    item_idx = utils::get_unum("ID товара: ");

                    code = storage::del_item(item_idx);
                    if(code == 0) {
                        break;
                    }

                    std::cout << "\033c";
                    std::cout << "Неправильно введён индекс товара!\n";
                }
                std::cout << "Успешно!\n";
                break;
            }
            case 5: {
                if(storage::items.empty()) {
                    std::cout << "Хранилище пустое!\n";
                    break;
                }
                while(true) {
                    utils::show_data(storage::items);
                    std::cout << "Введите, сколько добавить/убрать определённого товара\n";

                    item_idx = utils::get_unum("ID товара: ");
                    item_qty = utils::get_unum("Кол-во товара: ");

                    code = storage::change_item_qty(item_idx, item_qty);
                    if(code == 0) {
                        break;
                    }
                    std::cout << "\033c";
                    std::cout << "Неверно введён индекс товара и/или кол-во!\n";
                }
                std::cout << "Успешно!\n";
                break;
            }
            case 6: {
                if(storage::items.empty()) {
                    std::cout << "Хранилище пустое!\n";
                    break;
                }
                while(true) {
                    utils::show_data(storage::items);
                    std::cout << "Введите новую цену товара\n";

                    item_idx = utils::get_unum("ID товара: ");
                    item_price = utils::get_unum("Цена товара: ");

                    code = storage::set_item_price(item_idx, item_price);
                    if(code == 0) {
                        break;
                    }
                    std::cout << "\033c";
                    std::cout << "Неверно введён индекс товара и/или цена!\n";
                }
                std::cout << "Успешно!\n";
                break;
            }
            case 7: {
                if(storage::items.empty()) {
                    std::cout << "Хранилище пустое!\n";
                    break;
                }
                while(true) {
                    utils::show_data(storage::items);
                    std::cout << "Введите новый вес товара\n";

                    item_idx = utils::get_unum("ID товара: ");
                    item_weight = utils::get_unum("Вес товара: ");

                    code = storage::set_item_weight(item_idx, item_weight);
                    if(code == 0) {
                        break;
                    }
                    std::cout << "\033c";
                    std::cout << "Неверно введён индекс товара и/или вес!\n";
                }
                std::cout << "Успешно!\n";
                break;
            }
            case 8: {
                storage::save_data("products_upd");
                std::cout << "Выполнено сохранение списка товаров в файл.\n";
                break;
            }
            case 9: {
                std::cout << "Инициирован выход из программы.\n";
                return 0;
            }
            default: {
                std::cout << "Неизвестный номер команды!\n";
                break;
            }
        }
        utils::sort(storage::items, SortField::item_price);
        system("pause");
        std::cout << "\033c";
    }
}