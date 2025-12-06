#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "storage.h"
#include "config.h"
#include "basics.h"

// TODO: Добавить проверки на тип введённых данных от пользователя (число/строка)

int utils::utf_len(const std::string& str) {
	int len = 0;
	for(char c : str) {
		// Так как кирилица кодируется двумя байтами, а не одним, как латиница 
		// (причём 1-й байт равен -47 или -48), мы не считаем 1-й байт.
		// Также не считаем 0, так как он информирует об окончании строки.
		len += (c != -48 && c != -47 && c != 0 ? 1 : 0);
	}
	return len;
}

int utils::num_len(int num) {
    num = std::abs(num);
	if(num == 0) {
		return 1;
	}

	int len = 0;
	while(num > 0) {
		num /= 10;
		++len;
	}
	return len;
}

std::string utils::num2str(long long num) {
    int len = utils::num_len(num);
    std::string str(len, '0');
    if(num < 0) {
        str += "-";
    }
    
    num = std::abs(num);
    for(int i = len - 1; i >= 0; --i) {
        int digit = num % 10;
        str[i] = static_cast<char>(digit + utils::NUM_TO_STR_COEF);
        num /= 10;
    }

    return str;
}

long long utils::str2num(const std::string& str) {
	int len = str.size();
    long long num = 0;
    int sign = 1;
    for(int i = 0; i < str.size(); ++i) {
        char ch = str[i];
		switch(ch) {
			case '\0': {
				continue;
			}
			case '.': {
				num /= static_cast<long long>(std::pow(10, str.size() - 1 - i));
				return num;
			}
			case '-': {
				if(i != 0) {
					return utils::ERR_VALUE;
				}
				sign = -1;
				break;
			}
			default: {
				long long value = static_cast<int>(ch) - utils::NUM_TO_STR_COEF;
				if(0 > value || value > 9) {
					return utils::ERR_VALUE;
				}
		
				num += value * static_cast<long long>(std::pow(10, str.size() - 1 - i));
				break;
			}
		}
    }
    return num * sign;
}

std::string utils::input(const std::string& header) {
	std::cout << header;
	
	std::string str;
	char ch = '\0';
	while(true) {
		std::cin.get(ch);
		if(ch == '\n') {
			break;
		}
		str += ch;
	}
	return str;
}

unsigned long long utils::get_unum(const std::string& header) {
	std::string str = utils::input(header);
	long long num = 0;
	while(true) {
		num = utils::str2num(str);
		if(num == utils::ERR_VALUE || num < 0) {
			std::cerr << "[ ERROR ] Ввод не является беззнаковым целым числом!\n";
			str = utils::input(header);
		}
		else {
			return num;
		}
	}
}

long long utils::get_num(const std::string& header) {
	std::string str = utils::input(header);
	long long num = 0;
	while(true) {
		num = utils::str2num(str);
		if(num == utils::ERR_VALUE) {
			std::cerr << "[ ERROR ] Ввод не является целым числом!\n";
			str = utils::input(header);
		}
		else {
			return num;
		}
	}
}

bool utils::compare_items_fields(const Item& first, const Item& second, SortField field, Operator op) {
	bool condition;
	switch(field) {
		case SortField::item_name: {
			if(op == Operator::less) {
				condition = first.name < second.name;
			}
			else if(op == Operator::bigger) {
				condition = first.name > second.name;
			}
			else {
				condition = first.name == second.name;
			}
			break;
		}
		case SortField::item_price: {
			if(op == Operator::less) {
				condition = first.price < second.price;
			}
			else if(op == Operator::bigger) {
				condition = first.price > second.price;
			}
			else {
				condition = first.price == second.price;
			}
			break;
		}
		case SortField::item_qty: {
			if(op == Operator::less) {
				condition = first.qty < second.qty;
			}
			else if(op == Operator::bigger) {
				condition = first.qty > second.qty;
			}
			else {
				condition = first.qty == second.qty;
			}
			break;
		}
		case SortField::item_weight: {
			if(op == Operator::less) {
				condition = first.weight < second.weight;
			}
			else if(op == Operator::bigger) {
				condition = first.weight > second.weight;
			}
			else {
				condition = first.weight == second.weight;
			}
			break;
		}
	}
	return condition;
}

void utils::sort(std::vector<Item>& data, SortField _sort_field) {
	utils::sort(0, data.size() - 1, data, _sort_field);
}

void utils::sort(int start, int end, std::vector<Item>& data, SortField _sort_field) {
	if(start >= end) {
		return;
	}

	int idx = utils::randint(start, end);
	Item& pivot = data[idx];

	int l = start - 1;
	int r = end + 1;
	while(true) {
		do {
			l++;
		} 
		while(compare_items_fields(data[l], pivot, _sort_field, Operator::less));

		do {
			r--;
		} 
		while(compare_items_fields(data[r], pivot, _sort_field, Operator::bigger));

		if(l >= r) {
			break;
		}
		std::swap(data[l], data[r]);
	}

	l = r++; // Сначала установится l = r, затем r += 1
	
	utils::sort(start, l, data, _sort_field);
	utils::sort(r, end, data, _sort_field);
}

int utils::request(const std::string& header, const std::vector<std::string>& choice, const char alignment) {
	int idx = -1;
	int max_count = choice.size();

	int max_str_len = 0;
	for(const std::string& str : choice) {
		int len = utils::utf_len(str);
		max_str_len = std::max(max_str_len, len);
	}

	while(true) {
		
		if(header != "") {
			int len = utils::utf_len(header);
			int start_pad = utils::num_len(max_count);

			std::string l_padding(std::max(max_str_len - len + 4 + 2*start_pad, 0)/2 * alignment, ' ');

			std::cout << l_padding << header << "\n";
		}

		for(int i = 1; i < max_count + 1; ++i) {
			int len = utf_len(choice[i - 1]);
			std::string num_fill(num_len(max_count) - num_len(i), ' ');

			std::string l_padding((max_str_len - len)/2 * alignment, ' ');
			std::string r_padding((max_str_len - len)/2 * (2 - alignment), ' ');

			std::string delta((max_str_len - len) % 2, ' ');
			r_padding += (alignment == 0 ? delta : "");
			l_padding += (alignment != 0 ? delta : "");

			std::cout << "[" << num_fill << i << "|" << l_padding << choice[i - 1] << r_padding << "|" << num_fill << i << "]\n";
		}

		idx = utils::get_num("- ");
		if(1 > idx || idx >= max_count + 1) {
			std::cout << "\033c"; // Очищает консоль
			std::cout << "Несуществующий номер! Попробуйте заново...\n";
			continue;
		}
		return idx;
	}
}

int* utils::max_params_len(const std::vector<Item>& items) {
	int* ptr_result = new int[4];

	int max_name_len = 0;
	int max_price_len = 0;
	int max_qty_len = 0;
	int max_weight_len = 0;

	for(const Item& item : items) {
		max_name_len = std::max(max_name_len, utils::utf_len(item.name));
		max_price_len = std::max(max_price_len, utils::num_len(item.price));
		max_qty_len = std::max(max_qty_len, utils::num_len(item.qty));
		max_weight_len = std::max(max_weight_len, utils::num_len(item.weight));
	}

	ptr_result[0] = max_name_len;
	ptr_result[1] = max_price_len;
	ptr_result[2] = max_qty_len;
	ptr_result[3] = max_weight_len;

	return ptr_result;
}

void utils::show_data(std::vector<Item>& items) {
	int* params_lens = max_params_len(items);

	int cell_width = std::max({params_lens[0], params_lens[1], params_lens[3]});
	cell_width += params_lens[2] + 4;

	delete[] params_lens;
	
	int remaining = items.size();
	int iters_count = (remaining / config::COLUMNS_COUNT) + static_cast<int>((remaining % config::COLUMNS_COUNT) > 0);
	for(int i = 0; i < iters_count; ++i) {
		std::string cells_row[4];
		int cells_count = std::min(static_cast<unsigned>(remaining), config::COLUMNS_COUNT);
		remaining -= config::COLUMNS_COUNT;

		for(int j = 0; j < cells_count; ++j) {
			int idx = config::COLUMNS_COUNT * i + j;
			const Item& item = items[idx];

			std::string roof(cell_width - utils::num_len(item.qty) - 3, '_');
			std::string pad(utils::num_len(item.qty) + 2, ' ');
			cells_row[0] += " " + roof + pad + " ";

			pad = std::string(cell_width - utils::num_len(item.qty) - utils::utf_len(item.name) - 3, ' ');
			cells_row[1] += "|" + item.name + pad + "[" + utils::num2str(item.qty) + "] ";

			pad = std::string(cell_width - utils::num_len(item.weight) - 3, ' ');
			cells_row[2] += "|" + pad + utils::num2str(item.weight) + "г| ";

			pad = std::string(cell_width - utils::num_len(idx) - utils::num_len(item.price) - 5, '_');
			cells_row[3] += "[#" + utils::num2str(idx) + "]" + pad + utils::num2str(item.price) + "р| ";
		}

		for(std::string& row : cells_row) {
			std::cout << row << "\n";
		}
	}
}

int utils::randint(int min, int max) {
    return (std::rand() * std::rand()) % (max - min + 1) + min;
}