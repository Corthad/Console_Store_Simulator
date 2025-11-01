#include "storage.h"
#include <iostream>
#include <vector>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка кодировки UTF-8

    storage::load_data();

    storage::show_data(); // Вывод данных в консоль

    storage::add_item("M&Ms", 120, 3, 50); // Добавить "M&Ms".
    storage::del_item(0); // Удалить "Milk.Молоко".
    storage::change_item_qty(1, 10); // Кол-во "Bread": 5 -> 10;
    storage::set_item_price(3, 185); // Цена "Egg": 200 -> 185.
    storage::set_item_weight(5, 120); // Вес "Tea": 200 -> 120.

    storage::show_data();

    storage::save_data("products_upd");
    
    system("pause");
    return 0;
}