#include "storage.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "config.h"
#include "utils.h"
#include "basics.h"

std::vector<Item> storage::items = {};

int storage::load_data(const std::string& name) {
	
	std::ifstream file;
	std::string path = DATA_PATH + name + ".txt";
	
	file.open(path);
	if(!file.is_open()) {
		std::cout << "ERROR: Не удалось получить данные с файла.\n";
		return 1;
	}
	
	storage::items = {};
	Item item;
	// Пока в file есть данные, добавляем их в storage::items
	while(file >> item.name >> item.price >> item.qty >> item.weight) {
		storage::items.push_back(item);
	}
	file.close();
	
	return 0;
}

int storage::save_data(const std::string& name) {
	
	std::ofstream file;
	std::string path = storage::DATA_PATH + name + ".txt";

	file.open(path);
	if(!file.is_open()) {
		std::cout << "ERROR: Не удалось сохранить данные в файл.\n";
		return 1;
	}
	
	for(Item& item : storage::items) {
		file << item.name << " ";
		file << item.price << " ";
		file << item.qty << " ";
		file << item.weight << "\n";
	}
	file.close();
	
	return 0;
}

int storage::add_item(const std::string& name, unsigned price, unsigned qty, unsigned weight) {
	
	for(Item& item : storage::items) {
		if(item.name == name && item.price == price && item.weight == weight) {
			item.qty += qty;
			return 0;
		}
	}

	if(name == "" || qty == 0 || price == 0 || weight == 0) {
		return 1;
	}

	Item item {
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

int storage::change_item_qty(unsigned id, int count) {
	
	if(0 > id || id >= storage::items.size()) {
		return 1;
	}

	if(count == 0) {
		return 2;
	}

	Item& item = storage::items[id];
	int result = item.qty + count;
	if(result < 0) {
		return 2;
	}
	else if(result == 0) {
		storage::del_item(id);
	}
	else {
		item.qty += count;
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
	
	Item& item = storage::items[id];
	item.price = price;

	for(int i = 0; i < storage::items.size(); ++i) {
		Item& other = storage::items[i];
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
	
	Item& item = storage::items[id];
	item.weight = weight;

	for(int i = 0; i < storage::items.size(); ++i) {
		Item& other = storage::items[i];
		if(other.name == item.name && other.price == item.price && other.weight == item.weight && i != id) {
			other.qty += item.qty;
			storage::del_item(id);
		}
	}

	return 0;
}