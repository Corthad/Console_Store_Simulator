#ifndef BUYER_H
#define BUYER_H

#include <string>
#include <vector>

#include "basics.h"

namespace buyer {

    extern std::vector<Item> items;

    void show_data();

    int add_item(const std::string& name, unsigned price, unsigned qty, unsigned weight);
    int del_item(unsigned id);
    int change_item_qty(unsigned id, unsigned count);

}

#endif // BUYER_H