#include <string>
#include <iostream>
#include "../include/storage.h"
#include <map>
#include <vector>

using namespace std;
using namespace storage;

bool served = false;
vector<Item> products;

void sell_products(vector<string> args)
{
	//cout << "args: " << args << endl;
	products.clear();
	served = true;
}

void add_product(vector<string> args)
{
	//cout << "args: " << args << endl;
	cout << "name, price, quanity" << endl;
	add_item(args[0], stoi(args[1], nullptr, 10), stoi(args[2], nullptr, 10), stoi(args[3], nullptr, 10));
}

void show_products(vector<string> args)
{
	//cout << "args: " << args << endl;
	show_data();
}

void ring_up_product(vector<string> args)
{
	//cout << "args: " << args << endl;
	products.push_back(items[stoi(args[0], nullptr, 10)]);
}

map<string, void(*)(vector<string>)> commands{{"add", add_product}, {"sell", sell_products}, {"show", show_products}, {"ring", ring_up_product}};

void serve_buyer()
{
	while (!served)
	{
		string input;
		cout << "&";
		getline(cin, input);
		cout << input.substr(0, input.find(" ")) << endl;

		string func_name = input.substr(0, input.find(" "));
		string argsLine = input.find(" ") != string::npos ? input.substr(input.find(" ") - 1) : "";
		string a;
		vector<string> args;
		while (cin >> a) {
			if (a == "$") {
				break;
			}
			args.push_back(a);
		}
		cout << args.data();
		cin.ignore();
		if (commands.find(func_name) != commands.end())
			commands[func_name](args);
	}
}


