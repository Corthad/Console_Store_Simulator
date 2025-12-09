#include "seller.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "buyer_bot.h" 
#include "storage.h"
#include "utils.h"
#include "constants.h"
#include "global.h"
#include "structures.h"

using namespace std;

void reset_day_statistics() {
    g_shop.daily_profit = 0.0f;
    // g_shop.customers_served = 0;
}

void show_day_report() {
    cout << "=== ОТЧЕТ О РАБОЧЕМ ДНЕ ===\n";
    cout << "Обслужено покупателей: " << g_shop.customers_served << endl;
    cout << "Прибыль за день: " << fixed << setprecision(2) << g_shop.daily_profit << " руб.\n";
    cout << "Общая прибыль: " << fixed << setprecision(2) << g_shop.total_profit << " руб.\n";
    cout << "Баланс магазина: " << fixed << setprecision(2) << g_shop.balance << " руб.\n";
    cout << "Товаров осталось в магазине: " << g_shop.product_count << endl;
    
    // Подсчет общего количества оставшихся товаров
    int total_items_remaining = 0;
    for (int i = 0; i < g_shop.product_count; i++) {
        total_items_remaining += g_shop.products[i].quantity;
    }
    cout << "Единиц товара осталось: " << total_items_remaining << endl;
}

void simulate_business_day() {
    clean_screen();
    
    if (g_shop.product_count == 0) {
        cout << "В магазине нет товаров для продажи!\n";
        return;
    }
    
    reset_day_statistics();
    
    cout << "=== НАЧАЛО РАБОЧЕГО ДНЯ ===\n";
    
    // Генерируем случайное количество покупателей
    int num_customers = MIN_CUSTOMERS_PER_DAY + rand() % (MAX_CUSTOMERS_PER_DAY - MIN_CUSTOMERS_PER_DAY + 1);
    cout << "Сегодня в магазин придет " << num_customers << " покупателей.\n";
    
    // Симулируем каждого покупателя
    for (int i = 1; i <= num_customers; i++) {
        cout << "--- Покупатель #" << i << " заходит в магазин ---\n";
        
        // Генерируем случайного покупателя
        customer_data customer = generate_random_customer(i);
        
        // Симулируем покупки покупателя
        simulate_customer_purchase(customer);
        
        // Пауза для наглядности
        cout << "Покупатель #" << i << " ушел.\n";
    }
    
    // Показываем отчет о дне
    show_day_report();
    
    cout << "=== КОНЕЦ РАБОЧЕГО ДНЯ ===\n";
}