#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "storage.h"
#include <map>
#include <vector>

using namespace std;

namespace seller
{
	bool served = false;
	map<int, int> products;

	int paper_money;
	int digit_money;

	struct command
	{
		string name;
		string argsDescription;

		void(*func)(vector<string>);
	};

	// ПЕРЕНЕСТИ В УТИЛИТЫ
	// разделить строку на вектор строк
	std::vector<std::string> split(const std::string& str, char delimiter = ' ') {
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);

		while (std::getline(tokenStream, token, delimiter)) {
			tokens.push_back(token);
		}

		return tokens;
	}

	// загрузить данные о прибыли из тхт
	void load_data() {
		ifstream file;
		string path = "data/seller.txt";

		file.open(path);
		if (!file.is_open()) {
			std::cout << "ERROR: Не удалось получить данные с файла.\n";
		}
		else {
			file >> paper_money >> digit_money;
		}
		file.close();
	}

	// сохранить данные о прибыли в тхт
	void save_data(vector<string> args) {
		std::ofstream file;
		std::string path = "data/seller.txt";

		file.open(path);
		if (!file.is_open()) {
			std::cout << "ERROR: Не удалось cохранить данные с файла.\n";
		}
		else {
			file << paper_money << " " << digit_money << " ";
		}
		file.close();
	}

	// продать все пробитые товары
	void sell_products(vector<string> args)
	{
		//served = true;
		for (const auto& [id, quanity] : products)
		{
			paper_money += storage::items[id].price * quanity;
			storage::change_item_qty(id, -quanity);
		}
		products.clear();
	}

	// добавить товар на склад
	void add_product(vector<string> args)
	{
		storage::add_item(args[0], stoi(args[1], nullptr, 10), stoi(args[2], nullptr, 10), stoi(args[3], nullptr, 10));
	}

	// показать товары на складе
	void show_products(vector<string> args)
	{
		storage::show_data();
	}

	// показать деньги
	void show_money(vector<string> args)
	{
		cout << "Наличные: " << paper_money << endl;
		cout << "На счету: " << digit_money << endl;
	}

	// показать товары в корзине
	void show_cart(vector<string> args)
	{
		for (auto& pair : products)
		{
			cout << storage::items[pair.first].name << ": " << pair.second << endl;
		}
	}

	// пробить товар/положить в корзину
	// args: index, quantity
	void add_to_cart(vector<string> args)
	{
		int id = stoi(args[0], nullptr, 10);
		int quantity = stoi(args[1], nullptr, 10);

		if (storage::items.size() >= id + 1 && quantity <= storage::items[id].qty)
		{
			products[id] = quantity;
		}
	}

	// убрать товар из корзины
	// args: index, quantity
	void del_from_cart(vector<string> args)
	{
		int id = stoi(args[0], nullptr, 10);
		int quantity = stoi(args[1], nullptr, 10);

		if (products.find(id) != products.end() && products[id] >= quantity)
		{
			products[id] -= quantity;
			if (products[id] == 0)
				products.erase(id);
		}
	}

	// вектор команд
	vector<command> commands = { {"Добавить продукт", "Айди, Кол-во", add_product}, {"Продать пробитые товары", "", sell_products}, {"Показать товары", "", show_products}, {"Пробить товар", "Айди, Кол-во", add_to_cart},{"Сохранить данные о прибыли", "", save_data},{"Показать деньги", "", show_money},{"Удалить товар из корзины", "Айди, Кол-во", del_from_cart}, {"Показать товары в корзине", "", show_cart} };

	// начать поведение продавца
	void start_seller()
	{
		//load_data();
		storage::load_data();
		paper_money = 0;
		digit_money = 0;

		while (!served)
		{

			for (int i = 1; i <= commands.size(); i++)
			{
				cout << i << ".   " << commands[i - 1].name << endl;
			}
			int cmdNum;
			cin >> cmdNum;
			std::cout << "\033c";

			if (cmdNum > 0 && cmdNum <= commands.size())
			{
				vector<string> args = {};
				if (commands[cmdNum - 1].argsDescription != "")
				{
					cout << "Введите аргументы: " << commands[cmdNum - 1].argsDescription << endl;
					string input;
					cin.ignore();
					getline(cin, input);
					args = split(input, ' ');
				}
				commands[cmdNum - 1].func(args);
			}
			system("pause");
			std::cout << "\033c";
		}
	}

}



