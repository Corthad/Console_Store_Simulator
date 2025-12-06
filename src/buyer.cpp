#include "buyer.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "basics.h"

std::vector<Item> buyer::items = {};

void buyer::show_data() {
	
	std::cout << "-------------------------\n";
	for(int i = 0; i < buyer::items.size(); ++i) {

		Item& item = buyer::items[i];

		std::cout << "ID: " << i << "\n";
		std::cout << "Название: " << item.name << "\n";
		std::cout << "Цена: " << item.price << "\n";
		std::cout << "Количество: " << item.qty << "\n";
		std::cout << "Вес: " << item.weight << "\n";
		std::cout << "-------------------------\n";
	}
}

int buyer::add_item(const std::string& name, unsigned price, unsigned qty, unsigned weight) {
	
	for(Item& item : buyer::items) {
		if(item.name == name && item.price == price && item.weight == weight) {
			item.qty += qty;
			return 0;
		}
	}

	if(qty == 0 || price == 0 || weight == 0) {
		return 1;
	}

	Item item {
		name, price, qty, weight
	};
	items.push_back(item);

	return 0;
}

int buyer::del_item(unsigned id) {
	
	if(0 > id || id >= buyer::items.size()) {
		return 1;
	}
	
	buyer::items.erase(buyer::items.begin() + id);

	return 0;
}

int buyer::change_item_qty(unsigned id, unsigned count) {
	
	if(0 > id || id >= buyer::items.size()) {
		return 1;
	}

	if(count == 0) {
		return 2;
	}

	Item& item = buyer::items[id];
	int result = item.qty + count;
	if(result < 0) {
		return 2;
	}
	else if(result = 0) {
		buyer::del_item(id);
	}

	return 0;
}