#include "storage.h"
#include <iostream>
#include <vector>
#include <filesystem> // Для получения пути к рабочей папке

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка кодировки UTF-8

    std::vector<product> storage = load_data();

    show_storage(storage); // Вывод данных в консоль

    add_item(storage, 0, 5); // Увеличится количество на 5
    remove_item(storage, 1, 10); // Уменьшится количество на 1

    show_storage(storage);

    set_item_price(storage, 0, 777); // Устанавливается значение цены, равное 777
    set_item_weight(storage, 1, 100); // Устанавливается значение веса, равное 100

    show_storage(storage); // Вывод данных в консоль

    std::string current_path = std::filesystem::current_path().string();
    std::string updated_path = current_path + "/../data/products_upd.txt";
    save_data(storage, updated_path); // Сохранение данных в файл 'products_upd.txt'
    
    system("pause");
    return 0;
}