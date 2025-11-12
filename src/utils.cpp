#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <limits>

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

int utils::request(const std::string& header, const std::vector<std::string>& choice, const short alignment) {
	int idx = -1;
	int max_count = static_cast<int>(choice.size());

	int max_str_len = 0;
	for(const std::string& str : choice) {
		int len = utils::utf_len(str);
		max_str_len = std::max(max_str_len, len);
	}

	while(1 > idx || idx >= max_count + 1) {
		
		if(header != "") {
			int len = utils::utf_len(header);
			int start_pad = utils::num_len(max_count);

			std::string l_pad(std::max(max_str_len - len + 4 + 2*start_pad, 0)/2 * alignment, ' ');

			std::cout << l_pad << header << "\n";
		}

		for(int i = 0; i < max_count; ++i) {
			int len = utf_len(choice[i]);
			std::string num_fill(num_len(max_count) - num_len(i), ' ');

			std::string l_pad(std::max(max_str_len - len, 0)/2.0f * alignment, ' ');
			std::string r_pad(std::max(max_str_len - len + 1, 0)/2.0f * (2 - alignment), ' ');

			std::cout << "[" << num_fill << i + 1 << "|" << l_pad << choice[i] << r_pad << "|" << num_fill << i + 1 << "]\n";
		}
		std::cout << "- ";
		std::cin >> idx;

		if(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			idx = -1;
		}
		if(1 > idx || idx >= max_count + 1) {
			std::cout << "\033c"; // Очищает консоль
			std::cout << "Несуществующий номер! Попробуйте заново...\n";
			idx = -1;
		}
	}
	
	return idx;
}

int utils::randint(int min, int max) {
    return min + std::rand() % max;
}

int utils::save_int_input(const std::string& message, const int& min_value, const int& max_value) {
	int value;
	while (true) {
		std::cout << "\033c";
		std::cout << message;
		if (std::cin >> value) {
			if (value >= min_value && value <= max_value) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return value;
			}
			else {
				std::cout << "Введенное значение находится вне диапазона выбора. Введите значение из диапазона от " << min_value << " до " << max_value << ".\n";
				system("pause");
			}
		}
		else {
				std::cout << "Введен некорректный тип данных или введенное значение находится вне диапазона этого типа.\n";
				system("pause");
		}
        std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}	
}