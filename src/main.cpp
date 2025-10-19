#include "storage.h"
#include <iostream>
#include <vector>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка кодировки UTF-8

    std::vector<product> items = load_data("products.txt");
    items_list(items); // Вывод данных в консоль

    add_item(items, 0, 5); // Увеличится количество на 5
    remove_item(items, 1); // Уменьшится количество на 1

    set_item_price(items, 0, 777); // Устанавливается значение цены, равное 777
    set_item_weight(items, 1, 100); // Устанавливается значение веса, равное 100

    items_list(items); // Вывод данных в консоль

    save_data("products_updated.txt", items); // Сохранение данных в файл 'products_updated.txt'

    system("pause");
    return 0;
}