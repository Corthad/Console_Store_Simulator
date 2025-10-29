#include <string>
#include <iostream>
#include "../include/storage.h"
#include <map>
#include <vector>

using namespace std;

bool served = false;
vector<product> products;

void sell_products(vector<string> args)
{
	//cout << "args: " << args << endl;
}

void add_product(vector<string> args)
{
	string a = "35435";
	cout << stoi(a, nullptr, 10);
	//cout << "args: " << args << endl;
	cout << "name, price, quanity" << endl;
	add_item(stoi(args[0], nullptr, 10), (unsigned)args[1], (unsigned)args[2]);
}

void show_products(vector<string> args)
{
	//cout << "args: " << args << endl;
	show_storage();
}

void ring_up_product(vector<string> args)
{
	//cout << "args: " << args << endl;
	products
}

map<string, void(*)(string[])> commands{{"add", add_product}, {"sell", sell_products}, {"show", show_products}, {"ring", ring_up_product}};

void serve_buyer(string product_name, int quantity)
{
	string input;
	while (!served)
	{
		cout << "&";
		getline(cin, input);
		cout << input.substr(0, input.find(" ")) << endl;

		string func_name = input.substr(0, input.find(" "));
		string argsLine = input.find(" ") != string::npos ? input.substr(input.find(" ") - 1) : "";
		vector<string> args = argsLine.Split(" ");
		if (commands.find(func_name) != commands.end())
			commands[func_name](args);
	}
}


