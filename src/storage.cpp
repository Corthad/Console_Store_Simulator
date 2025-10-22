#include "storage.h"

#include <iostream>
#include <fstream>
#include <vector>

/*
Вывод ошибки, связанный с индексом списка.

Args:

 - `list_name` : std::string
   Наименование списка-переменной.
 - `list_size` : unsigned int
   Количество элементов в списке.
 - `id` : int
   Идентификатор, из-за которого вызывается ошибка.

Example:

>>> id_err("items", items.size(), 20); // Предположим, что значений в списке всего 10
>>> 'ERROR: [id] должен быть в пределах размера [items]! В итоге, [idx] = 20, [list_size] = 10.'
*/
void id_err(const std::string& list_name, unsigned list_size, int id)
{
	std::cout << "ERROR: [id] должен быть в пределах размера [" << list_name << "]! ";
	std::cout << "В итоге, [id] = " << id << ", ";
	std::cout << "[list_size] = " << list_size << ".\n";
}

/*
Вывод ошибки, связанный с неправильным значением переменной.

Args:

 - `value_name` : std::string
   Наименование значения-переменной.
 - `value` : int
   Значение, из-за которого вызывается ошибка.
 - `ex` : std::string
   Причина, из-за которой вызывается ошибка.

Example:

>>> value_err("value", -1, "должен быть больше 0");
>>> 'ERROR: [value] должен быть больше 0! В итоге, [value] = -1.'
*/
void value_err(const std::string& value_name, int value, const std::string& ex)
{
	std::cout << "ERROR: [" << value_name << "] " << ex << "! ";
	std::cout << "В итоге, [" << value_name << "] = " << value << ".\n";
}

/*
Вывод списка предметов в консоль.

Args:

 - `data` : std::vector<product>
   Список предметов. См. `product`
*/
void show_storage(std::vector<product>& data)
{
	std::cout << "-------------------------\n";
	for(int i=0; i < data.size(); ++i)
	{
		product &p = data[i];
		std::cout << "ID: " << i << "\n";
		std::cout << "Название: " << p.name << "\n";
		std::cout << "Цена: " << p.price << "\n";
		std::cout << "Количество: " << p.qty << "\n";
		std::cout << "Вес: " << p.weight << "\n";
		std::cout << "-------------------------\n";
	}
}

/*
Загрузка игровых данных.
    
Args:

 - `path` : std::string (optional)
   Путь к получаемым данным. По умолчанию: `PATH`.

Returns:

 - `data` : std::vector<product>
   Список предметов. См. `product`.
*/
std::vector<product> load_data(const std::string& path)
{
	std::ifstream file;
	file.open(path);
	if(!file.is_open())
	{
		std::cout << "ERROR: Не удалось получить данные с файла.\n";
		return {}; // Пустой вектор
	}

	std::vector<product> data;
	product p;
	while(file >> p.name >> p.price >> p.qty >> p.weight) // Пока в file есть данные, добавляем их в products
	{
		data.push_back(p);
	}
	file.close();
	
	return data;
}

/*
Сохранение игровых данных.
    
Args:

 - `data` : std::vector<product>
   Список предметов. См. `product`.
 - `path` : std::string (optional)
   Путь, куда сохранятся данные. По умолчанию: `PATH`.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - ошибка сохранения файла.
*/
int save_data(std::vector<product>& data, const std::string& path)
{
	std::ofstream file;
	file.open(path);
	if(!file.is_open())
	{
		std::cout << "ERROR: Не удалось сохранить данные в файл.\n";
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
Увеличение количества предмета в списке.
    
Args:

 - `data` : std::vector<product>
   Список предметов. См. `product`.
 - `id` : unsigned int
   ID добавляемого предмета.
 - `count` : unsigned int (optional)
   Количество предметов, которое добавится в список. По умолчанию: `1`.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id.
*/
int add_item(std::vector<product>& data, unsigned id, unsigned count)
{
	if(0 > id || id >= data.size())
	{
		id_err("items", data.size(), id);
		return 1;
	}
	
	product &p = data[id];
	p.qty += count;
	return 0;
}

/*
Уменьшение количества предмета в списке.
    
Args:

 - `data` : std::vector<product>
   Список предметов. См. `product`.
 - `id` : unsigned int
   ID убираемого предмета.
 - `count` : unsigned int (optional)
   Количество предметов, которое уберётся из списка. По умолчанию: `1`.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id, `2` - итоговое значение отрицательно.
*/
int remove_item(std::vector<product>& data, unsigned id, unsigned count)
{
	if(0 > id || id >= data.size())
	{
		id_err("items", data.size(), id);
		return 1;
	}
	
	product &p = data[id];
	int result = p.qty - count;
	if(result < 0)
	{
		value_err("p.qty", result, "не может быть меньше 0");
		return 2;
	}
	p.qty = result;
	return 0;
}

/*
Установка цены предмета.
    
Args:

 - `data` : std::vector<product>
   Список предметов. См. `product`.
 - `id` : unsigned int
   ID предмета, значение которого нужно изменить.
 - `price` : unsigned int
   Новое значение цены.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id, `2` - значение за допустимыми пределами.
*/
int set_item_price(std::vector<product>& data, unsigned id, unsigned price)
{
	if(0 > id || id >= data.size())
	{
		id_err("items", data.size(), id);
		return 1;
	}

	if(price < 1)
	{
		value_err("price", price, "должен быть натуральным числом");
		return 2;
	}
	
	product &p = data[id];
	p.price = price;
	return 0;
}

/*
Установка веса предмета.
    
Args:

 - `data` : std::vector<product>
   Список предметов. См. `product`.
 - `id` : unsigned int
   ID предмета, значение которого нужно изменить.
 - `weight` : unsigned int
   Новое значение веса.

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - некорректный id, `2` - значение за допустимыми пределами.
*/
int set_item_weight(std::vector<product>& data, unsigned id, unsigned weight)
{
	if(0 > id || id >= data.size())
	{
		id_err("items", data.size(), id);
		return 1;
	}

	if(weight < 1)
	{
		value_err("weight", weight, "должен быть натуральным числом");
		return 2;
	}
	
	product &p = data[id];
	p.weight = weight;
	return 0;
}