#include <iostream>
#include <fstream>
#include <vector>

#include "objbase.h"

/*
Контейнер для хранения состояний объекта.

Values:
 - `name` : std::string -> Наименование
 - `price` : int -> Цена
 - `qty` : int -> Количество
 - `weight` : int -> Вес
*/
struct product
{
    std::string name;
    unsigned price;
    unsigned qty;
    unsigned weight;
};

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
std::vector<product>& add_item(std::vector<product>& items, unsigned id, unsigned k = 1)
{
    if(0 > id || id >= items.size())
    {
        std::cout << "ERROR: [id] находится за пределами размера [items]. Возвращены исходные данные.\n";
    }
    else
    {
        product *p = &items[id];
        p->qty += k;
    }
    return items;
}

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
std::vector<product>& remove_item(std::vector<product>& items, unsigned id, unsigned k = 1)
{
    if(0 > id || id >= items.size())
    {
        std::cout << "ERROR: [id] находится за пределами размера [items]! Возвращены исходные данные.\n";
    }
    else
    {
        product *p = &items[id];
        if(p->qty == 0)
        {
            std::cout << "WARNING: Количество данного предмета уже равно 0! Возвращены исходные данные.\n";
        }
        else
        {
            p->qty -= 1;
        }
    }
    return items;
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

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product>& set_item_price(std::vector<product>& items, unsigned id, unsigned price)
{
    if(0 > id || id >= items.size())
    {
        std::cout << "WARNING: [id] находится за пределами размера [items]! Возвращены исходные данные.\n";
    }
    else
    {
        product *p = &items[id];
        p->price = price;
    }
    return items;
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

 - `items` : std::vector<product>
   Вектор из предметов. Смотри `product`
*/
std::vector<product>& set_item_weight(std::vector<product>& items, unsigned id, unsigned weight)
{
    if(0 > id || id >= items.size())
    {
        std::cout << "WARNING: [id] находится за пределами размера [items]! Возвращены исходные данные.\n";
    }
    else
    {
        product *p = &items[id];
        p->weight = weight;
    }
    return items;
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
std::vector<product> load_data(std::string& path)
{
    std::vector<product> products;
    
    std::ifstream data;
    data.open(path);
    if(data.is_open())
    {
        product p;
        while(data >> p.name >> p.price >> p.qty >> p.weight)
        {
            products.push_back(p);
        }

        data.close();
    }
    else
    {
        std::cout << "ERROR: Не удалось получить данные с файла\n";
    }

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
   Код завершения. `0` - успешно, `1` - ошибка.
*/
int save_data(std::string& path, std::vector<product>& data)
{
    std::ofstream file;
    file.open(path);
    if(file.is_open())
    {
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

    std::cout << "ERROR: Не удалось сохранить файл\n";
    return 1;
}

/* 
int main()
{
    std::string load_path = "products.txt";
    std::vector<product> products = load_data(load_path);

    for(product p : products)
    {
        std::cout << p.name << " ";
        std::cout << p.price << " ";
        std::cout << p.qty << " ";
        std::cout << p.weight << "\n";
    }

    add_item(products, 0, 5);
    products = remove_item(products, 1, 2);

    products = set_item_price(products, 0, 777);
    products = set_item_weight(products, 1, 228);

    for(product p : products)
    {
        std::cout << p.name << " ";
        std::cout << p.price << " ";
        std::cout << p.qty << " ";
        std::cout << p.weight << "\n";
    }

    std::string save_path = "products_upd.txt";
    save_data(save_path, products);

    return 0;
} 
*/