#include "storage.h"

#include <iostream>
#include <fstream>
#include <vector>

// Вывод списка предметов в консоль.
void show_storage()
{
	for(product p : storage)
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

 - `code` : int
   Код завершения. `0` - успешно, `1` - ошибка открытия файла.
*/
int load_data(const std::string& path)
{
	std::ifstream data;
	data.open(path);
	if(!data.is_open())
	{
		std::cout << "ERROR: Не удалось получить данные с файла.\n";
		return 1; // Пустой вектор
	}

	storage = {};
	product p;
	while(data >> p.name >> p.price >> p.qty >> p.weight) // Пока в data есть данные, добавляем их в products
	{
		storage.push_back(p);
	}
	data.close();
	
	return 0;
}

/*
Сохранение игровых данных
    
Args:

 - `path` : std::string
   Путь, куда сохранятся данные.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - ошибка открытия файла.
*/
int save_data(const std::string& path)
{
	std::ofstream file;
	file.open(path);
	if(!file.is_open())
	{
		std::cout << "ERROR: Не удалось сохранить файл.\n";
		return 1;
	}
	
	for(product item : storage)
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

 - `id` : unsigned int
   ID предмета.
 - `count` : unsigned int
   Количество предметов.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id.
*/
int add_item(unsigned id, unsigned count)
{
	if(0 > id || id >= storage.size())
	{
		std::cout << "ERROR: [id] находится за пределами размера [items]!\n";
		return 1;
	}
	
	product *p = &storage[id];
	p->qty += count;
	return 1;
}

/*
Удаление определённого предмета.
    
Args:

 - `id` : unsigned int
   ID предмета.
 - `count` : unsigned int
   Количество предметов.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id, `2` - ошибка изменения значения.
*/
int remove_item(unsigned id, unsigned count)
{
	if(0 > id || id >= storage.size())
	{
		std::cout << "ERROR: [id] находится за пределами размера [items]!\n";
		return 1;
	}
	
	product *p = &storage[id];
	if(p->qty == 0)
	{
		std::cout << "ERROR: Количество данного предмета уже равно 0!\n";
		return 2;
	}
	p->qty -= count;
	return 0;
}

/*
Установка цены определённого предмета.
    
Args:

 - `id` : unsigned int
   ID предмета.
 - `price` : unsigned int
   Значение новой цены.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id.
*/
int set_item_price(unsigned id, unsigned price)
{
	if(0 > id || id >= storage.size())
	{
		std::cout << "ERROR: [id] находится за пределами размера [items]!\n";
		return 1;
	}
	
	product *p = &storage[id];
	p->price = price;
	return 0;
}

/*
Установка веса определённого предмета.
    
Args:

 - `id` : unsigned int
   ID предмета.
 - `weight` : unsigned int
   Значение нового веса.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id.
*/
int set_item_weight(unsigned id, unsigned weight)
{
	if(0 > id || id >= storage.size())
	{
		std::cout << "ERROR: [id] находится за пределами размера [items]!\n";
		return 1;
	}
	
	product *p = &storage[id];
	p->weight = weight;
	return 0;
}