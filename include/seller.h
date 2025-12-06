#ifndef SELLER_H
#define SELLER_H

#include <vector>
#include <string>

namespace seller {

    const std::vector<std::string> storage_debug_menu {
        "Считать список товаров с файла",
        "Отобразить список товаров",
        "Добавить товар на склад",
        "Удалить товар со склада",
        "Изменить количество товара",
        "Установить цену товара",
        "Установить вес товара",
        "Сохранить список товаров в файл",
        "Завершить программу"
    };

    int loop();

    void start_seller();
}

#endif // SELLER_H