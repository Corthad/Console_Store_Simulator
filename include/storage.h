#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

#include "basics.h"

namespace storage {
    extern std::vector<Item> items;

    const std::string DATA_PATH = "../data/";
    const std::string DATA_NAME = "products";

    /* Загрузка данных по имени. По умолчанию `name` = "products". */
    int load_data(const std::string& name = DATA_NAME);

    /* Сохранение данных по имени. По умолчанию `name` = "products". */
    int save_data(const std::string& name = DATA_NAME);

    int add_item(const std::string& name, unsigned price, unsigned qty, unsigned weight);
    int del_item(unsigned id);
    int change_item_qty(unsigned id, int count);
    int set_item_price(unsigned id, unsigned price);
    int set_item_weight(unsigned id, unsigned weight);
}

#endif // STORAGE_H