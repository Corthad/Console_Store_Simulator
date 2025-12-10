#include "buyer.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>

#include "storage.h"
#include "utils.h"
#include "constants.h"
#include "global.h"

using namespace std;

void reset_customer_data() {
    g_customer.money = 0.0f;
    g_customer.capacity = MAX_BASKET_CAPACITY;
    g_customer.max_weight = INITIAL_MAX_WEIGHT;
    g_customer.current_weight = 0.0f;
    g_customer.basket_count = 0;
    g_customer.total_items = 0;
    g_customer.payment_method = 1; // наличные по умолчанию
    g_customer.bags_bought = 0;
    g_customer.customer_id = 0;
}

bool is_valid_money_input(float money) {
    return money >= 0.0f;
}

float get_customer_money_input() {
    float money;
    bool valid_input = false;
    
    clean_screen();
    while (!valid_input) {
        cout << "=== РЕЖИМ ПОКУПАТЕЛЯ ===\n";
        cout << "Введите начальную сумму денег покупателя (руб.): ";
        input(money);
        
        valid_input = is_valid_money_input(money);
        if (!valid_input) {
            clean_screen();
            cout << "Ошибка! Сумма денег не может быть отрицательной.\n";
        }
    }
    
    return money;
}

void view_available_products() {
    clean_screen();
    
    if (g_shop.product_count == 0) {
        cout << "В магазине нет товаров!\n";
        return;
    }
    
    cout << "=== ДОСТУПНЫЕ ТОВАРЫ ===\n";
    cout << left << setw(20) << "Название" 
         << setw(15) << "Цена" 
         << setw(10) << "Кол-во" 
         << setw(10) << "Вес (кг)" << endl;
    cout << string(55, '-') << endl;
    
    int available_count = 0;
    for (int i = 0; i < g_shop.product_count; i++) {
        if (g_shop.products[i].quantity > 0) {
            print_product_customer_view(g_shop.products[i]);
            ++available_count;
        }
    }
    
    if (available_count == 0) {
        cout << "Нет доступных товаров (все товары распроданы).\n";
    }
}

bool can_carry_weight(float additional_weight) {
    return (g_customer.current_weight + additional_weight) <= g_customer.max_weight;
}

void add_to_basket() {
    clean_screen();
    
    if (g_shop.product_count == 0) {
        cout << "В магазине нет товаров!\n";
        pause_screen();
        return;
    }
    
    view_available_products();
    
    char product_name[MAX_NAME_LENGTH];
    cout << "Введите название товара: ";
    input(product_name, MAX_NAME_LENGTH);
    
    int index = find_product_by_name(product_name);
    if (index == -1 || g_shop.products[index].quantity == 0) {
        cout << "Товар не найден или отсутствует в наличии!\n";
        pause_screen();
        return;
    }
    
    int quantity;
    cout << "Введите количество (доступно: " << g_shop.products[index].quantity << "): ";
    input(quantity);
    
    if (quantity <= 0) {
        cout << "Неверное количество!\n";
        pause_screen();
        return;
    }
    else if (quantity > g_shop.products[index].quantity) {
        cout << "Недостаточно товара в магазине!\n";
        pause_screen();
        return;
    }
    else if (g_customer.total_items + quantity > g_customer.capacity) {
        cout << "Превышена вместимость корзины!\n";
        cout << "Можно добавить еще: " << g_customer.capacity - g_customer.total_items << " единиц\n";
        pause_screen();
        return;
    }
    
    float additional_weight = quantity * g_shop.products[index].weight;
    if (!can_carry_weight(additional_weight)) {
        cout << "Превышен максимальный вес!\n";
        cout << "Дополнительный вес: " << fixed << setprecision(2) << additional_weight << " кг\n";
        cout << "Текущий вес: " << fixed << setprecision(2) << g_customer.current_weight << " кг\n";
        cout << "Максимальный вес: " << fixed << setprecision(2) << g_customer.max_weight << " кг\n";
        cout << "Можно добавить еще: " << fixed << setprecision(2) << g_customer.max_weight - g_customer.current_weight << " кг\n";
        pause_screen();
        return;
    }
    
    // Проверяем, есть ли уже этот товар в корзине
    for (int i = 0; i < g_customer.basket_count; i++) {
        if (g_customer.basket[i].product_index == index) {
            g_customer.basket[i].quantity += quantity;
            g_customer.basket[i].total_weight += additional_weight;
            g_customer.total_items += quantity;
            g_customer.current_weight += additional_weight;
            clean_screen();
            cout << "Количество товара в корзине обновлено!\n";
            pause_screen();
            return;
        }
    }
    
    // Добавляем новый товар в корзину
    if (g_customer.basket_count >= MAX_BASKET_ITEMS) {
        cout << "Корзина переполнена (максимум разных товаров)!\n";
        pause_screen();
        return;
    }
    
    g_customer.basket[g_customer.basket_count].product_index = index;
    g_customer.basket[g_customer.basket_count].quantity = quantity;
    g_customer.basket[g_customer.basket_count].total_weight = additional_weight;
    g_customer.basket_count++;
    g_customer.total_items += quantity;
    g_customer.current_weight += additional_weight;
    
    clean_screen();
    cout << "Товар добавлен в корзину!\n";
    pause_screen();
}

void show_basket() {
    clean_screen();
    
    if (g_customer.basket_count == 0) {
        cout << "Корзина пуста!\n";
        return;
    }
    
    cout << "=== ВАША КОРЗИНА ===\n";
    cout << left << setw(20) << "Товар" 
         << setw(10) << "Кол-во" 
         << setw(10) << "Вес ед. (кг)"
         << setw(15) << "Цена за ед." 
         << setw(15) << "Сумма" << endl;
    cout << string(70, '-') << endl;
    
    float total = 0;
    for (int i = 0; i < g_customer.basket_count; i++) {
        int idx = g_customer.basket[i].product_index;
        float item_total = g_shop.products[idx].selling_price * g_customer.basket[i].quantity;
        total += item_total;
        
        cout << left << setw(20) << g_shop.products[idx].name
             << setw(10) << g_customer.basket[i].quantity
             << setw(10) << fixed << setprecision(2) << g_shop.products[idx].weight
             << setw(15) << fixed << setprecision(2) << g_shop.products[idx].selling_price
             << setw(15) << fixed << setprecision(2) << item_total << endl;
    }
    
    cout << string(70, '-') << endl;
    cout << "ИТОГО:\n";
    cout << "  Сумма: " << fixed << setprecision(2) << total << " руб.\n";
    cout << "  Вес: " << fixed << setprecision(2) << g_customer.current_weight << " / " 
         << fixed << setprecision(2) << g_customer.max_weight << " кг\n";
    cout << "  Количество товаров: " << g_customer.total_items << " / " << g_customer.capacity << " ед.\n";
    cout << "  Способ оплаты: " << (g_customer.payment_method == 1 ? "Наличные" : "Безналичные") << endl;
    cout << "  Доступно денег: " << fixed << setprecision(2) << g_customer.money << " руб.\n";
}

void checkout() {
    if (g_customer.basket_count == 0) {
        clean_screen();
        cout << "Корзина пуста!\n";
        pause_screen();
        return;
    }
    
    show_basket();
    
    // Рассчитываем общую сумму
    float total = 0;
    for (int i = 0; i < g_customer.basket_count; i++) {
        int idx = g_customer.basket[i].product_index;
        total += g_shop.products[idx].selling_price * g_customer.basket[i].quantity;
    }
    
    // Проверяем возможность оплаты
    if (g_customer.payment_method == 1 && total > g_customer.money) {
        cout << "Недостаточно наличных!\n";
        cout << "Нужно: " << fixed << setprecision(2) << total << " руб., доступно: " << fixed << setprecision(2) << g_customer.money << " руб.\n";
        pause_screen();
        return;
    }
    
    char confirm;
    while(true) {
        cout << "Оформить покупку? (y/n): ";

        input(&confirm, 1);
        confirm = tolower(confirm);

        if(confirm == 'y') {
            break;
        }
        else if(confirm == 'n') {
            cout << "Покупка отменена.\n";
            pause_screen();
            return;
        }
        else {
            cout << "Неверный ввод!\n";
            pause_screen();
        }
    }
    
    // Проверяем наличие товаров
    for (int i = 0; i < g_customer.basket_count; i++) {
        int idx = g_customer.basket[i].product_index;
        if (g_customer.basket[i].quantity > g_shop.products[idx].quantity) {
            cout << "Товар '" << g_shop.products[idx].name << "' больше не доступен в нужном количестве!\n";
            pause_screen();
            return;
        }
    }
    
    // Оформляем покупку
    for (int i = 0; i < g_customer.basket_count; i++) {
        int idx = g_customer.basket[i].product_index;
        int quantity = g_customer.basket[i].quantity;
        
        // Обновляем магазин
        g_shop.products[idx].quantity -= quantity;
        g_shop.balance += g_shop.products[idx].selling_price * quantity;
        float profit = (g_shop.products[idx].selling_price - g_shop.products[idx].purchase_price) * quantity;
        g_shop.total_profit += profit;
        g_shop.daily_profit += profit;
        
        // Удаляем товар если количество = 0
        if (g_shop.products[idx].quantity == 0) {
            for (int j = idx; j < g_shop.product_count - 1; j++) {
                g_shop.products[j] = g_shop.products[j + 1];
            }
            g_shop.product_count--;
            // Корректируем индексы в корзине других покупателей
            for (int j = i + 1; j < g_customer.basket_count; j++) {
                if (g_customer.basket[j].product_index > idx) {
                    g_customer.basket[j].product_index--;
                }
            }
        }
    }
    
    // Обновляем деньги покупателя
    if (g_customer.payment_method == 1) {
        g_customer.money -= total;
    }
    
    g_shop.customers_served++;
    
    clean_screen();
    cout << "Покупка оформлена успешно!\n";
    cout << "Спасибо за покупку!\n";
    cout << "Остаток денег: " << fixed << setprecision(2) << g_customer.money << " руб.\n";
    pause_screen();
    
    // Очищаем корзину
    clear_basket();
}

void clear_basket() {
    g_customer.basket_count = 0;
    g_customer.total_items = 0;
    g_customer.current_weight = 0.0f;
    clean_screen();
    cout << "Корзина очищена.\n";
}

void buy_bag() {
    clean_screen();
    
    if (g_customer.max_weight >= MAX_TOTAL_WEIGHT) {
        cout << "Вы уже достигли максимального веса (" << MAX_TOTAL_WEIGHT << " кг)!\n";
        pause_screen();
        return;
    }
    
    if (g_customer.payment_method == 1 && g_customer.money < BAG_PRICE) {
        cout << "Недостаточно наличных для покупки пакета!\n";
        cout << "Нужно: " << BAG_PRICE << " руб., доступно: " << g_customer.money << " руб.\n";
        pause_screen();
        return;
    }
    
    cout << "Пакет увеличит ваш максимальный вес на " << BAG_WEIGHT_INCREASE << " кг.\n";
    cout << "Текущий максимальный вес: " << g_customer.max_weight << " кг\n";
    cout << "Новый максимальный вес: " << min(g_customer.max_weight + BAG_WEIGHT_INCREASE, MAX_TOTAL_WEIGHT) << " кг\n";
    cout << "Цена: " << BAG_PRICE << " руб.\n";
    
    char confirm;
    while(true) {
        cout << "Купить пакет? (y/n): ";

        input(&confirm, 1);
        confirm = tolower(confirm);

        if(confirm == 'y') {
            break;
        }
        else if(confirm == 'n') {
            cout << "Покупка пакета отменена.\n";
            pause_screen();
            return;
        }
        else {
            cout << "Неверный ввод!\n";
            pause_screen();
        }
    }

    // Вычисляем, насколько можно увеличить вес
    float weight_increase = BAG_WEIGHT_INCREASE;
    if (g_customer.max_weight + weight_increase > MAX_TOTAL_WEIGHT) {
        weight_increase = MAX_TOTAL_WEIGHT - g_customer.max_weight;
    }
    
    // Списание денег
    if (g_customer.payment_method == 1) {
        g_customer.money -= BAG_PRICE;
    }
    
    // Увеличение максимального веса
    g_customer.max_weight += weight_increase;
    g_customer.bags_bought++;
    
    // Прибыль магазина (пакет считается товаром с нулевой себестоимостью)
    g_shop.balance += BAG_PRICE;
    g_shop.total_profit += BAG_PRICE;
    g_shop.daily_profit += BAG_PRICE;
    
    clean_screen();
    cout << "Пакет куплен!\n";
    cout << "Максимальный вес увеличен на " << weight_increase << " кг\n";
    cout << "Текущий максимальный вес: " << g_customer.max_weight << " кг\n";
    if (g_customer.payment_method == 1) {
        cout << "Остаток денег: " << g_customer.money << " руб.\n";
    }
    pause_screen();
}