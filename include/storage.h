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

void items_list(std::vector<product> items);

std::vector<product> load_data(const std::string& path);
int save_data(const std::string& path, std::vector<product>& data);

int add_item(std::vector<product>& items, unsigned id, unsigned count = 1);
int remove_item(std::vector<product>& items, unsigned id, unsigned count = 1);
int set_item_price(std::vector<product>& items, unsigned id, unsigned price);
int set_item_weight(std::vector<product>& items, unsigned id, unsigned weight);