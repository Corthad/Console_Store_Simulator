#include "storage.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "config.h"
#include "utils.h"

std::vector<storage::Item> storage::items = {};

/**
 * @brief Вспомогательный метод для получения максимальной длины среди имён, цен, количеств и весов. 
 * @param ptr_result указатель, куда нужно сохранить итоговые значения.
*/
void max_params_len(int* ptr_result) {
	int max_name_len = 0;
	int max_price_len = 0;
	int max_qty_len = 0;
	int max_weight_len = 0;

	for(storage::Item& item : storage::items) {
		max_name_len = std::max(max_name_len, utils::utf_len(item.name));
		max_price_len = std::max(max_price_len, utils::num_len(item.price));
		max_qty_len = std::max(max_qty_len, utils::num_len(item.qty));
		max_weight_len = std::max(max_weight_len, utils::num_len(item.weight));
	}

	ptr_result[0] = max_name_len;
	ptr_result[1] = max_price_len;
	ptr_result[2] = max_qty_len;
	ptr_result[3] = max_weight_len;
}

void storage::show_data() {
	int* params_lens = new int[4];
	max_params_len(params_lens);

	int cell_width = std::max({params_lens[0], params_lens[1], params_lens[3]});
	cell_width += params_lens[2] + 4;

	delete[] params_lens;
	
	int remaining = storage::items.size();
	int iters_count = (remaining / config::COLUMNS_COUNT) + static_cast<int>((remaining % config::COLUMNS_COUNT) > 0);
	for(int i = 0; i < iters_count; ++i) {
		std::string cells_row[4];
		int cells_count = std::min(static_cast<unsigned>(remaining), config::COLUMNS_COUNT);
		remaining -= config::COLUMNS_COUNT;

		for(int j = 0; j < cells_count; ++j) {
			int idx = config::COLUMNS_COUNT * i + j;
			storage::Item& item = storage::items[idx];

			std::string roof(cell_width - utils::num_len(item.qty) - 3, '_');
			std::string pad(utils::num_len(item.qty) + 2, ' ');
			cells_row[0] += " " + roof + pad + " ";

			pad = std::string(cell_width - utils::num_len(item.qty) - utils::utf_len(item.name) - 3, ' ');
			cells_row[1] += "|" + item.name + pad + "[" + std::to_string(item.qty) + "] ";

			pad = std::string(cell_width - utils::num_len(item.weight) - 3, ' ');
			cells_row[2] += "|" + pad + std::to_string(item.weight) + "г| ";

			pad = std::string(cell_width - utils::num_len(idx) - utils::num_len(item.price) - 5, '_');
			cells_row[3] += "[#" + std::to_string(idx) + "]" + pad + std::to_string(item.price) + "р| ";
		}

		for(std::string& row : cells_row) {
			std::cout << row << "\n";
		}
	}
}

int storage::load_data(const std::string& name) {
	
	std::ifstream file;
	std::string path = DATA_PATH + name + ".txt";
	
	file.open(path);
	if(!file.is_open()) {
		std::cout << "ERROR: Не удалось получить данные с файла.\n";
		return 1;
	}

	storage::items = {};
	storage::Item item;
	// Пока в file есть данные, добавляем их в storage::items
	while(file >> item.name >> item.price >> item.qty >> item.weight) {
		storage::items.push_back(item);
	}
	file.close();
	
	return 0;
}

int storage::save_data(const std::string& name) {
	
	std::ofstream file;
	std::string path = storage::DATA_PATH + name;

	file.open(path);
	if(!file.is_open()) {
		std::cout << "ERROR: Не удалось сохранить данные в файл.\n";
		return 1;
	}
	
	for(storage::Item& item : storage::items) {
		file << item.name << " ";
		file << item.price << " ";
		file << item.qty << " ";
		file << item.weight << "\n";
	}
	file.close();
	
	return 0;
}

int storage::add_item(const std::string& name, unsigned price, unsigned qty, unsigned weight) {
	
	for(storage::Item& item : storage::items) {
		if(item.name == name && item.price == price && item.weight == weight) {
			item.qty += qty;
			return 0;
		}
	}

	if(qty == 0 || price == 0 || weight == 0) {
		return 1;
	}

	storage::Item item {
		name, price, qty, weight
	};
	storage::items.push_back(item);

	return 0;
}

int storage::del_item(unsigned id) {
	
	if(0 > id || id >= storage::items.size()) {
		return 1;
	}
	
	storage::items.erase(storage::items.begin() + id);

	return 0;
}

int storage::change_item_qty(unsigned id, unsigned count) {
	
	if(0 > id || id >= storage::items.size()) {
		return 1;
	}

	if(count == 0) {
		return 2;
	}

	storage::Item& item = storage::items[id];
	int result = item.qty + count;
	if(result < 0) {
		return 2;
	}
	else if(result = 0) {
		storage::del_item(id);
	}

	return 0;
}

int storage::set_item_price(unsigned id, unsigned price) {
	
	if(0 > id || id >= storage::items.size()) {
		return 1;
	}

	if(price == 0) {
		return 2;
	}
	
	storage::Item& item = storage::items[id];
	item.price = price;

	for(int i = 0; i < storage::items.size(); ++i) {
		storage::Item& other = storage::items[i];
		if(other.name == item.name && other.price == item.price && other.weight == item.weight && i != id) {
			other.qty += item.qty;
			storage::del_item(id);
		}
	}

	return 0;
}

int storage::set_item_weight(unsigned id, unsigned weight) {
	
	if(0 > id || id >= storage::items.size()) {
		return 1;
	}

	if(weight == 0) {
		return 2;
	}
	
	storage::Item& item = storage::items[id];
	item.weight = weight;

	for(int i = 0; i < storage::items.size(); ++i) {
		storage::Item& other = storage::items[i];
		if(other.name == item.name && other.price == item.price && other.weight == item.weight && i != id) {
			other.qty += item.qty;
			storage::del_item(id);
		}
	}

	return 0;
}