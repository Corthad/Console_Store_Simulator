#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

/*
Контейнер для хранения состояний объекта.

Values:
 - `name` : std::string -> Наименование
 - `price` : int -> Цена
 - `qty` : int -> Количество
 - `weight` : int -> Вес
*/
struct product;

/*
Добавление определённого предмета.
    
Args:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
 - `id` : unsigned int
   ID предмета.

Returns:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product>& add_item(std::vector<product>& items, unsigned id, unsigned k = 1);

/*
Удаление определённого предмета.
    
Args:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
 - `id` : unsigned int
   ID предмета.

Returns:

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product>& remove_item(std::vector<product>& items, unsigned id, unsigned k = 1);

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

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product>& set_item_price(std::vector<product>& items, unsigned id, unsigned price);

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

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product>& set_item_weight(std::vector<product>& items, unsigned id, unsigned weight);

/*
Загрузка игровых данных
    
Args:

 - `path` : std::string
   Путь к данным.

Returns:

 - `products` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product> load_data(std::string& path);

/*
Сохранение игровых данных
    
Args:

 - `path` : std::string
   Путь, куда сохранятся данные.
 - `products` : std::vector<product>
   Вектор из предметов. Смотри `product`

Returns:

 - `code` : int
   Код завершения. `0` - успешно, `1` - ошибка.
*/
int save_data(std::string& path, std::vector<product>& data);

#endif