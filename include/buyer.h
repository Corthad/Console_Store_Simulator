#ifndef BUYER_H
#define BUYER_H

#include <string>
#include <vector>

#include "basics.h"

namespace buyer {

    struct inventory {
        int paper_money;
        int digit_money;
        int hand_capacity;
    };

    extern std::vector<Item> cart;
    extern inventory inv;

    const std::string buyer_activity[10] {
    "Меню активностей покупателя.",
    "1.   Считать данные инвентаря с файла;",
    "2.   Сохранить данные инвентаря в файл;",
    "3.   Посмотреть данные инвентаря;",
    "4.   Посмотреть товары в корзине;",
    "5.   Добавить товары в корзину;",
    "6.   Убрать товары из корзины;",
    "7.   Отправиться на кассу;",
    "8.   Изменить данные инвентаря",
    "9.   Выйти в главное меню."
};

    void start_buyer();
    void load_data();
    void save_data();
    void view_inventory();
    void view_cart();
    void add_to_cart();
    void del_from_cart(bool one_time_launch = false);
    void edit_inventory();
    void go_to_checkout();
}

#endif