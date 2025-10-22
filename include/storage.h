#pragma once

#include <string>
#include <vector>
#include <filesystem>

struct product
{
    std::string name;
    unsigned price;
    unsigned qty;
    unsigned weight;
};

const std::string PATH = std::filesystem::current_path().string() + "/../data/products.txt";

void show_storage(std::vector<product>& data);

std::vector<product> load_data(const std::string& path = PATH);
int save_data(std::vector<product>& data, const std::string& path = PATH);

int add_item(std::vector<product>& data, unsigned id, unsigned count = 1);
int remove_item(std::vector<product>& data, unsigned id, unsigned count = 1);
int set_item_price(std::vector<product>& data, unsigned id, unsigned price);
int set_item_weight(std::vector<product>& data, unsigned id, unsigned weight);