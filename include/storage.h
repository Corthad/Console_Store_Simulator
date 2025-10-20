#pragma once

#include <string>
#include <vector>

struct product
{
    std::string name;
    unsigned price;
    unsigned qty;
    unsigned weight;
};

std::vector<product> storage;

void show_storage();

int load_data(const std::string& path);
int save_data(const std::string& path);

int add_item(unsigned id, unsigned count = 1);
int remove_item(unsigned id, unsigned count = 1);
int set_item_price(unsigned id, unsigned price);
int set_item_weight(unsigned id, unsigned weight);