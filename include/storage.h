#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

namespace storage {

    struct Item {
        std::string name;
        unsigned price;
        unsigned qty;
        unsigned weight;
    };

    extern std::vector<Item> items;

    const std::string DATA_PATH = "../data/";

    void show_data();

    int load_data(const std::string& name);
    int save_data(const std::string& name);

    int add_item(const std::string& name, unsigned price, unsigned qty, unsigned weight);
    int del_item(unsigned id);
    int change_item_qty(unsigned id, unsigned count);
    int set_item_price(unsigned id, unsigned price);
    int set_item_weight(unsigned id, unsigned weight);

}

#endif // STORAGE_H