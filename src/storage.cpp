#include "storage.h"

#include <iostream>
#include <fstream>
#include <vector>

/*
Вывод списка предметов в консоль.

Args:

 - `products` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
void items_list(std::vector<product> items)
{
	for(product p : items)
	{
		std::cout << p.name << " ";
		std::cout << p.price << " ";
		std::cout << p.qty << " ";
		std::cout << p.weight << "\n";
	}
}

/*
Загрузка игровых данных
    
Args:

 - `path` : std::string
   Путь к данным.

Returns:

 - `products` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product> load_data(const std::string& path)
{
	std::vector<product> products;
		
	std::ifstream data;
	data.open(path);
	if(!data.is_open())
	{
		std::cout << "ERROR: Не удалось получить данные с файла\n";
		return products; // Пустой вектор
	}
	
	product p;
	while(data >> p.name >> p.price >> p.qty >> p.weight) // Пока в data есть данные, добавляем их в products
	{
		products.push_back(p);
	}
	data.close();
	
	return products;
}

/*
Сохранение игровых данных
    
Args:

 - `path` : std::string
   Путь, куда сохранятся данные.
 - `products` : std::vector<product>
   Вектор из предметов. Смотри `product`

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - ошибка открытия файла.
*/
int save_data(const std::string& path, std::vector<product>& data)
{
	std::ofstream file;
	file.open(path);
	if(!file.is_open())
	{
		std::cout << "ERROR: Не удалось сохранить файл\n";
		return 1;
	}
	
	for(product item : data)
	{
		file << item.name << " ";
		file << item.price << " ";
		file << item.qty << " ";
		file << item.weight << "\n";
	}
	file.close();
	
	return 0;
}

/*
Добавление определённого предмета.
    
Args:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
 - `id` : unsigned int
   ID предмета.
 - `count` : unsigned int
   Количество предметов.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id.
*/
int add_item(std::vector<product>& items, unsigned id, unsigned count)
{
	if(0 > id || id >= items.size())
	{
		std::cout << "ERROR: [id] находится за пределами размера [items]. Возвращены исходные данные.\n";
		return 1;
	}
	
	product *p = &items[id];
	p->qty += count;
	return 1;
}

/*
Удаление определённого предмета.
    
Args:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
 - `id` : unsigned int
   ID предмета.
 - `count` : unsigned int
   Количество предметов.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id, `2` - ошибка изменения значения.
*/
int remove_item(std::vector<product>& items, unsigned id, unsigned count)
{
	if(0 > id || id >= items.size())
	{
		std::cout << "ERROR: [id] находится за пределами размера [items]! Возвращены исходные данные.\n";
		return 1;
	}
	
	product *p = &items[id];
	if(p->qty == 0)
	{
		std::cout << "WARNING: Количество данного предмета уже равно 0! Возвращены исходные данные.\n";
		return 2;
	}
	p->qty -= count;
	return 0;
}

/*
Установка цены определённого предмета.
    
Args:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
 - `id` : unsigned int
   ID предмета.
 - `price` : unsigned int
   Значение новой цены.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id.
*/
int set_item_price(std::vector<product>& items, unsigned id, unsigned price)
{
	if(0 > id || id >= items.size())
	{
		std::cout << "WARNING: [id] находится за пределами размера [items]! Возвращены исходные данные.\n";
		return 1;
	}
	
	product *p = &items[id];
	p->price = price;
	return 0;
}

/*
Установка веса определённого предмета.
    
Args:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
 - `id` : unsigned int
   ID предмета.
 - `weight` : unsigned int
   Значение нового веса.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id.
*/
int set_item_weight(std::vector<product>& items, unsigned id, unsigned weight)
{
	if(0 > id || id >= items.size())
	{
		std::cout << "WARNING: [id] находится за пределами размера [items]! Возвращены исходные данные.\n";
		return 1;
	}
	
	product *p = &items[id];
	p->weight = weight;
	return 0;
}