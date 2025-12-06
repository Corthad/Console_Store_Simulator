#ifndef BASICS_H
#define BASICS_H

#include <vector>
#include <string>

/* Перечисление способов сравнения (больше, меньше, равно ...) */
enum Operator {
    equal,
    less,
    bigger
};

/* Перечисление полей для сортировки */
enum SortField {
    item_name,
    item_price,
    item_qty,
    item_weight
};

/* Предмет - товар */
struct Item {
    std::string name;
    unsigned price;
    unsigned qty;
    unsigned weight;
};

struct WeightBounds {
    unsigned current;
    unsigned max;
};

/* Хранилище с предметами и макс. вместимостью (весом) */
struct Storage {
    std::vector<Item> items;
    WeightBounds weight;
};

/* Кошелёк с наличными и безналичными деньгами */
struct Wallet {
    unsigned cash;
    unsigned bank_card;
};

#endif // BASICS_H