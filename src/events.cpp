#include "events.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "storage.h"
#include "supplier.h"
#include "buyer.h"
#include "utils.h"
#include "constants.h"
#include "global.h"
#include "structures.h"

using namespace std;

// Случайные события для владельца
void random_event_owner() {
    clean_screen();
    
    int event = rand() % 3;
    
    switch (event) {
        case 0:
            handle_tax_inspection();
            break;
        case 1:
            handle_product_damage();
            break;
        case 2:
            handle_supplier_discount();
            break;
    }
}

void handle_tax_inspection() {
    cout << "=== СЛУЧАЙНОЕ СОБЫТИЕ: ПРОВЕРКА НАЛОГОВОЙ ===\n";
    float fine = g_shop.balance * 0.1f; // Штраф 10% от баланса
    g_shop.balance -= fine;
    cout << "Налоговая проверила ваш магазин и выписала штраф!\n";
    cout << "Штраф: " << fixed << setprecision(2) << fine << " руб.\n";
    cout << "Новый баланс: " << fixed << setprecision(2) << g_shop.balance << " руб.\n";
}

void handle_product_damage() {
    cout << "=== СЛУЧАЙНОЕ СОБЫТИЕ: ПОРЧА ТОВАРА ===\n";
    if (g_shop.product_count == 0) {
        cout << "В магазине нет товаров для порчи.\n";
        return;
    }
    
    int index = rand() % g_shop.product_count;
    int damaged_quantity = min(g_shop.products[index].quantity, 1 + rand() % 5);
    
    g_shop.products[index].quantity -= damaged_quantity;
    
    cout << "Часть товара '" << g_shop.products[index].name << "' испортилась!\n";
    cout << "Испорчено: " << damaged_quantity << " единиц\n";
    cout << "Осталось: " << g_shop.products[index].quantity << " единиц\n";
    
    if (g_shop.products[index].quantity == 0) {
        // Удаляем товар
        for (int i = index; i < g_shop.product_count - 1; i++) {
            g_shop.products[i] = g_shop.products[i + 1];
        }
        g_shop.product_count--;
        cout << "Товар удален из ассортимента.\n";
    }
}

void handle_supplier_discount() {
    cout << "=== СЛУЧАЙНОЕ СОБЫТИЕ: СКИДКА ОТ ПОСТАВЩИКА ===\n";
    if (!g_supplier.is_generated) {
        cout << "Сначала посетите поставщика, чтобы сгенерировать товары!\n";
        return;
    }
    
    if (g_supplier.product_count == 0) {
        cout << "У поставщика нет товаров для скидки.\n";
        return;
    }
    
    int index = rand() % g_supplier.product_count;
    float discount = 0.8f + (rand() % 20) / 100.0f; // Скидка 0-20%
    
    float old_price = g_supplier.products[index].purchase_price;
    g_supplier.products[index].purchase_price *= discount;
    
    cout << "Поставщик предоставил скидку на товар '" << g_supplier.products[index].name << "'!\n";
    cout << "Старая цена закупки: " << fixed << setprecision(2) << old_price << " руб.\n";
    cout << "Новая цена закупки: " << fixed << setprecision(2) << g_supplier.products[index].purchase_price << " руб.\n";
    cout << "Скидка: " << fixed << setprecision(1) << (1 - discount) * 100 << "%\n";
}

// Случайные события для покупателя
void random_event_customer() {
    clean_screen();
    
    int event = rand() % 3;
    
    switch (event) {
        case 0:
            handle_customer_discount();
            break;
        case 1:
            handle_lost_money();
            break;
        case 2:
            handle_special_offer();
            break;
    }
}

void handle_customer_discount() {
    cout << "=== СЛУЧАЙНОЕ СОБЫТИЕ: СКИДОЧНЫЙ КУПОН ===\n";
    if (g_customer.basket_count == 0) {
        cout << "У вас пустая корзина. Добавьте товары, чтобы использовать купон.\n";
        return;
    }
    
    float discount = 0.9f; // 10% скидка
    cout << "Вы нашли скидочный купон на 10%!\n";
    cout << "Скидка будет применена при следующей покупке.\n";
    
    char use_now;
    cout << "Использовать сейчас? (y/n): ";
    cin >> use_now;
    
    if (use_now == 'y' || use_now == 'Y') {
        // Применяем скидку ко всем товарам в корзине
        for (int i = 0; i < g_customer.basket_count; i++) {
            int idx = g_customer.basket[i].product_index;
            g_shop.products[idx].selling_price *= discount;
        }
        cout << "Скидка применена ко всем товарам в корзине!\n";
    }
}

void handle_lost_money() {
    cout << "=== СЛУЧАЙНОЕ СОБЫТИЕ: ПОТЕРЯ ДЕНЕГ ===\n";
    float lost_amount = g_customer.money * (0.05f + (rand() % 10) / 100.0f); // 5-15% от денег
    
    if (lost_amount > g_customer.money) {
        lost_amount = g_customer.money;
    }
    
    g_customer.money -= lost_amount;
    
    cout << "Вы потеряли часть денег по дороге в магазин!\n";
    cout << "Потеряно: " << fixed << setprecision(2) << lost_amount << " руб.\n";
    cout << "Осталось денег: " << fixed << setprecision(2) << g_customer.money << " руб.\n";
}

void handle_special_offer() {
    cout << "=== СЛУЧАЙНОЕ СОБЫТИЕ: СПЕЦИАЛЬНОЕ ПРЕДЛОЖЕНИЕ ===\n";
    
    if (g_shop.product_count == 0) {
        cout << "В магазине нет товаров для акции.\n";
        return;
    }
    
    int index = rand() % g_shop.product_count;
    float discount = 0.7f + (rand() % 20) / 100.0f; // Скидка 10-30%
    
    float old_price = g_shop.products[index].selling_price;
    g_shop.products[index].selling_price *= discount;
    
    cout << "Специальное предложение на товар '" << g_shop.products[index].name << "'!\n";
    cout << "Старая цена: " << fixed << setprecision(2) << old_price << " руб.\n";
    cout << "Новая цена: " << fixed << setprecision(2) << g_shop.products[index].selling_price << " руб.\n";
    cout << "Скидка: " << fixed << setprecision(1) << (1 - discount) * 100 << "%\n";
    cout << "Предложение действительно до конца дня!\n";
}