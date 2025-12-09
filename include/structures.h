#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "constants.h"

struct base_product {
    char name[MAX_NAME_LENGTH];
    float purchase_price;      // цена закупки
    float weight;              // вес одной единицы товара в кг
};

struct product {
    char name[MAX_NAME_LENGTH];
    float purchase_price;      // цена закупки
    float selling_price;       // цена продажи (вычисляется при добавлении в магазин)
    int quantity;              // количество на складе
    float weight;              // вес одной единицы товара в кг
    float markup_percentage;   // наценка в процентах
};

struct shop_data {
    product products[MAX_PRODUCTS];  // товары в магазине
    int product_count;
    float total_profit;        // общая прибыль за все время
    float daily_profit;        // прибыль за текущий день
    float balance;             // текущий баланс
    int customers_served;      // количество обслуженных покупателей за день
};

struct supplier_data {
    product products[MAX_PRODUCTS];  // товары у поставщика
    int product_count;
    bool is_generated;         // были ли сгенерированы товары у поставщика
};

struct all_products_data {
    base_product products[MAX_PRODUCTS];  // все возможные товары из файла
    int product_count;
};

struct basket_item {
    int product_index;         // индекс товара в магазине
    int quantity;             // количество в корзине
    float total_weight;       // общий вес этого товара в корзине
};

struct customer_data {
    float money;
    int capacity;             // вместимость корзины (количество единиц товара)
    float max_weight;         // максимальный вес, который может унести (кг)
    float current_weight;     // текущий вес корзины (кг)
    basket_item basket[MAX_BASKET_ITEMS];
    int basket_count;         // количество разных товаров в корзине
    int total_items;          // общее количество единиц товара в корзине
    int payment_method;       // 1 - наличные, 2 - кредитка
    int bags_bought;          // количество купленных пакетов
    int customer_id;          // ID покупателя для отладки
};

#endif // STRUCTURES_H