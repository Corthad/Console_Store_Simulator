#include <string>
#include <iostream>
#include "../include/storage.h"
#include <map>

using namespace std;

bool served = false;

void sell_products(string args)
{
	cout << "args: " << args << endl;
}

void add_product(string args)
{
	cout << "args: " << args << endl;
}

void show_products(string args)
{
	cout << "args: " << args << endl;
}

void ring_up_product(string args)
{
	cout << "args: " << args << endl;
}

map<string, void(*)(string)> commands { {"add", add_product}, { "sell", sell_products }, { "show", show_products }, { "ring", ring_up_product } };

void serve_buyer(string product_name, int quantity)
{
	string input;
	while (!served)
	{
		cout << "&";
		getline(cin, input);
		cout << input.substr(0, input.find(" ")) << endl;

		string func_name = input.substr(0, input.find(" "));
		string args = input.find(" ") != string::npos ? input.substr(input.find(" ") - 1) : "";
		if (commands.find(func_name) != commands.end())
			commands[func_name](args);
	}
}


