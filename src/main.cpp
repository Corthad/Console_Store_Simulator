#include "storage.h"
#include <iostream>
#include <vector>
#include <filesystem> // Для получения пути к рабочей папке

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка кодировки UTF-8

    std::string current_path = std::filesystem::current_path().string();
    std::string products_path = current_path + "/data/products.txt";
    std::string updated_path = current_path + "/data/products_upd.txt";

    load_data(products_path);
    show_storage(); // Вывод данных в консоль

    add_item(0, 5); // Увеличится количество на 5
    remove_item(1); // Уменьшится количество на 1

    set_item_price(0, 777); // Устанавливается значение цены, равное 777
    set_item_weight(1, 100); // Устанавливается значение веса, равное 100

    show_storage(); // Вывод данных в консоль

    save_data(updated_path); // Сохранение данных в файл 'products_updated.txt'
    
    system("pause");
    return 0;
}