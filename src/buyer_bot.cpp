#include "buyer_bot.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "storage.h"
#include "constants.h"
#include "global.h"

using namespace std;

customer_data generate_random_customer(int id) {
    customer_data customer;
    
    // Генерация случайных характеристик покупателя
    customer.money = MIN_CUSTOMER_MONEY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(MAX_CUSTOMER_MONEY - MIN_CUSTOMER_MONEY)));
    customer.capacity = MIN_CUSTOMER_CAPACITY + rand() % (MAX_CUSTOMER_CAPACITY - MIN_CUSTOMER_CAPACITY + 1);
    customer.max_weight = MIN_CUSTOMER_WEIGHT + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(MAX_CUSTOMER_WEIGHT - MIN_CUSTOMER_WEIGHT)));
    customer.current_weight = 0.0f;
    customer.basket_count = 0;
    customer.total_items = 0;
    customer.payment_method = 1 + rand() % 2; // 1 или 2 (наличные или кредитка)
    customer.bags_bought = 0;
    customer.customer_id = id;
    
    return customer;
}

bool try_add_product_to_customer_basket(customer_data& customer, int product_index) {
    // Проверяем валидность индекса
    if (product_index < 0 || product_index >= g_shop.product_count) {
        return false;
    }
    
    // Проверяем, есть ли товар в наличии
    if (g_shop.products[product_index].quantity <= 0) {
        return false;
    }
    
    // Находим, сколько уже есть этого товара в корзине
    int already_in_basket = 0;
    for (int i = 0; i < customer.basket_count; i++) {
        if (customer.basket[i].product_index == product_index) {
            already_in_basket = customer.basket[i].quantity;
            break;
        }
    }
    
    // Определяем, сколько единиц товара покупатель может купить
    int max_by_money = 0;
    if (customer.payment_method == 1) { // Наличные
        max_by_money = static_cast<int>(customer.money / g_shop.products[product_index].selling_price);
    } else { // Кредитка - без ограничений по деньгам
        max_by_money = 100; // Большое число для кредитки
    }
    
    int max_by_capacity = customer.capacity - customer.total_items;
    int max_by_weight = static_cast<int>((customer.max_weight - customer.current_weight) / g_shop.products[product_index].weight);
    
    // Доступное количество в магазине за вычетом уже в корзине
    int max_by_stock = g_shop.products[product_index].quantity - already_in_basket;
    
    // Берем минимальное из всех ограничений
    int max_possible = min(min(min(max_by_money, max_by_capacity), max_by_weight), max_by_stock);
    
    // Если покупатель не может купить ни одной единицы
    if (max_possible <= 0) {
        return false;
    }
    
    // Случайное количество от 1 до max_possible
    int quantity = 1 + rand() % max_possible;
    
    // Если покупатель уже имеет этот товар в корзине, добавляем к существующему
    bool found = false;
    for (int i = 0; i < customer.basket_count; i++) {
        if (customer.basket[i].product_index == product_index) {
            customer.basket[i].quantity += quantity;
            customer.basket[i].total_weight += quantity * g_shop.products[product_index].weight;
            found = true;
            break;
        }
    }
    
    // Если товара еще нет в корзине
    if (!found) {
        if (customer.basket_count >= MAX_BASKET_ITEMS) {
            return false; // Корзина переполнена разными товарами
        }
        
        customer.basket[customer.basket_count].product_index = product_index;
        customer.basket[customer.basket_count].quantity = quantity;
        customer.basket[customer.basket_count].total_weight = quantity * g_shop.products[product_index].weight;
        customer.basket_count++;
    }
    
    // Обновляем общие показатели покупателя
    customer.total_items += quantity;
    customer.current_weight += quantity * g_shop.products[product_index].weight;
    
    // Списание денег (только для наличных)
    if (customer.payment_method == 1) {
        customer.money -= quantity * g_shop.products[product_index].selling_price;
    }
    
    return true;
}

void process_customer_checkout(customer_data& customer) {
    float total_sales = 0.0f;
    float total_profit = 0.0f;
    
    // Сначала обрабатываем все товары в корзине, уменьшая количество
    for (int i = 0; i < customer.basket_count; i++) {
        int product_index = customer.basket[i].product_index;
        int quantity = customer.basket[i].quantity;
        
        // Проверяем валидность индекса
        if (product_index < 0 || product_index >= g_shop.product_count) {
            continue;
        }
        
        // Обновляем магазин
        g_shop.products[product_index].quantity -= quantity;
        float sale_amount = g_shop.products[product_index].selling_price * quantity;
        float profit = (g_shop.products[product_index].selling_price - g_shop.products[product_index].purchase_price) * quantity;
        
        g_shop.balance += sale_amount;
        g_shop.total_profit += profit;
        g_shop.daily_profit += profit;
        
        total_sales += sale_amount;
        total_profit += profit;
    }
    
    // Затем удаляем товары с количеством <= 0
    // Идем с конца массива, чтобы избежать проблем со сдвигом индексов
    for (int i = g_shop.product_count - 1; i >= 0; i--) {
        if (g_shop.products[i].quantity <= 0) {
            // Обновляем индексы в корзине текущего покупателя
            for (int j = 0; j < customer.basket_count; j++) {
                if (customer.basket[j].product_index > i) {
                    customer.basket[j].product_index--;
                }
            }
            
            // Удаляем товар из массива магазина
            for (int j = i; j < g_shop.product_count - 1; j++) {
                g_shop.products[j] = g_shop.products[j + 1];
            }
            g_shop.product_count--;
        }
    }
    
    g_shop.customers_served++;
    
    // Вывод информации о покупке покупателя (для отладки)
    if (customer.total_items > 0) {
        cout << "Покупатель #" << customer.customer_id << " купил " << customer.total_items 
             << " товаров на сумму " << fixed << setprecision(2) << total_sales << " руб. (прибыль: " 
             << fixed << setprecision(2) << total_profit << " руб.)\n";
    }
}

void simulate_customer_purchase(customer_data& customer) {
    // Очищаем корзину покупателя
    customer.basket_count = 0;
    customer.total_items = 0;
    customer.current_weight = 0.0f;
    
    // Если в магазине нет товаров, выходим
    if (g_shop.product_count == 0) {
        return;
    }
    
    // Покупатель пытается сделать несколько покупок
    int max_purchase_attempts = 5 + rand() % 6; // от 5 до 10 попыток
    int attempts = 0;
    
    while (attempts < max_purchase_attempts && customer.total_items < customer.capacity) {
        // Выбираем случайный товар
        int product_index = rand() % g_shop.product_count;
        
        // Пытаемся добавить товар в корзину
        try_add_product_to_customer_basket(customer, product_index);
        
        attempts++;
    }
    
    // Если покупатель что-то купил, оформляем покупку
    if (customer.total_items > 0) {
        process_customer_checkout(customer);
    }
}