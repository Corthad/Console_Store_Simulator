#include "supplier.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

#include "storage.h"
#include "utils.h"
#include "constants.h"
#include "global.h"

using namespace std;

int find_supplier_product_by_name(const char* name) {
    for (int i = 0; i < g_supplier.product_count; i++) {
        if (strcmp(g_supplier.products[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void print_supplier_product(const product& p) {
    cout << left << setw(20) << p.name 
         << setw(20) << fixed << setprecision(2) << p.purchase_price 
         << setw(15) << p.quantity 
         << setw(15) << fixed << setprecision(2) << p.weight << endl;
}

void generate_supplier_products() {
    clean_screen();
    
    if (g_all_products.product_count == 0) {
        cout << "База товаров пуста! Невозможно сгенерировать товары для поставщика.\n";
        pause_screen();
        return;
    }
    
    // Сбрасываем товары поставщика
    g_supplier.product_count = 0;
    
    // Генерируем случайное количество товаров у поставщика
    int num_products = MIN_SUPPLIER_PRODUCTS + rand() % (MAX_SUPPLIER_PRODUCTS - MIN_SUPPLIER_PRODUCTS + 1);
    
    // Ограничиваем количеством товаров в базе
    if (num_products > g_all_products.product_count) {
        num_products = g_all_products.product_count;
    }
    
    // Используем вектор для отслеживания уже использованных товаров
    vector<bool> used(g_all_products.product_count, false);
    
    for (int i = 0; i < num_products; i++) {
        // Выбираем случайный товар, который еще не использовался
        int product_index;
        int attempts = 0;
        do {
            product_index = rand() % g_all_products.product_count;
            attempts++;
            if (attempts > g_all_products.product_count * 2) {
                // Если не можем найти неиспользованный товар, выходим
                break;
            }
        } while (used[product_index]);
        
        if (used[product_index]) {
            // Все товары уже использованы
            break;
        }
        
        used[product_index] = true;
        
        const base_product& bp = g_all_products.products[product_index];
        
        // Создаем товар для поставщика
        product supplier_product;
        strcpy(supplier_product.name, bp.name);
        supplier_product.purchase_price = bp.purchase_price;
        supplier_product.selling_price = 0.0f; // У поставщика нет цены продажи
        supplier_product.markup_percentage = 0.0f;
        
        // Генерируем случайное количество
        supplier_product.quantity = MIN_SUPPLIER_QUANTITY + rand() % (MAX_SUPPLIER_QUANTITY - MIN_SUPPLIER_QUANTITY + 1);
        supplier_product.weight = bp.weight;
        
        g_supplier.products[g_supplier.product_count] = supplier_product;
        g_supplier.product_count++;
    }
    
    g_supplier.is_generated = true;
    
    cout << "Сгенерировано " << g_supplier.product_count << " товаров у поставщика.\n";
    pause_screen();
}

void show_supplier_products() {
    clean_screen();
    
    if (g_supplier.product_count == 0) {
        cout << "У поставщика нет товаров!\n";
        return;
    }
    
    cout << "=== ТОВАРЫ У ПОСТАВЩИКА ===\n";
    cout << left << setw(20) << "Название" 
         << setw(20) << "Цена закупки" 
         << setw(15) << "Кол-во" 
         << setw(15) << "Вес (кг)" << endl;
    cout << string(70, '-') << endl;
    
    for (int i = 0; i < g_supplier.product_count; i++) {
        cout << i + 1 << ". ";
        print_supplier_product(g_supplier.products[i]);
    }
}

void purchase_from_supplier() {
    // Генерируем товары у поставщика, если еще не были сгенерированы
    if (!g_supplier.is_generated) {
        cout << "Генерация товары у поставщика...\n";
        generate_supplier_products();
    }
    
    if (g_supplier.product_count == 0) {
        cout << "У поставщика нет товаров для продажи!\n";
        pause_screen();
        return;
    }
    
    int choice;
    do {
        clean_screen();
        cout << SUPPLIER_MENU;
        cin >> choice;
        
        switch (choice) {
            case 1:
                show_supplier_products();
                pause_screen();
                break;
            case 2:
                {
                    clean_screen();
                    show_supplier_products();
                    cout << "Введите номер товара для закупки (1-" << g_supplier.product_count << "): ";
                    int product_num;
                    cin >> product_num;
                    
                    if (cin.fail() || product_num < 1 || product_num > g_supplier.product_count) {
                        cout << "Неверный номер товара!\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pause_screen();
                        break;
                    }
                    
                    int supplier_index = product_num - 1;
                    const product& supplier_product = g_supplier.products[supplier_index];
                    
                    cout << "Введите количество для закупки (доступно: " << supplier_product.quantity << "): ";
                    int quantity;
                    cin >> quantity;
                    
                    if (cin.fail() || quantity <= 0) {
                        cout << "Неверное количество!\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pause_screen();
                        break;
                    }
                    
                    if (quantity > supplier_product.quantity) {
                        cout << "У поставщика недостаточно товара!\n";
                        pause_screen();
                        break;
                    }
                    
                    float cost = supplier_product.purchase_price * quantity;
                    
                    if (cost > g_shop.balance) {
                        cout << "Недостаточно средств на балансе магазина!\n";
                        cout << "Нужно: " << fixed << setprecision(2) << cost << " руб., доступно: " << fixed << setprecision(2) << g_shop.balance << " руб.\n";
                        pause_screen();
                        break;
                    }
                    
                    // Запрашиваем наценку для товара
                    clean_screen();
                    cout << "Установите наценку для товара '" << supplier_product.name << "':\n";
                    float markup = get_markup_percentage();
                    
                    // Рассчитываем цену продажи
                    float selling_price = supplier_product.purchase_price * (1 + markup / 100);
                    
                    // Проверяем, есть ли такой товар уже в магазине
                    int shop_index = find_product_by_name(supplier_product.name);
                    
                    if (shop_index != -1) {
                        // Товар уже есть в магазине, увеличиваем количество
                        g_shop.products[shop_index].quantity += quantity;
                        
                        // Можно также обновить наценку, если пользователь хочет
                        char update_markup;
                        cout << "Товар уже есть в магазине. Обновить наценку? (y/n): ";
                        cin >> update_markup;
                        
                        if (update_markup == 'y' || update_markup == 'Y') {
                            g_shop.products[shop_index].markup_percentage = markup;
                            g_shop.products[shop_index].selling_price = selling_price;
                            cout << "Наценка и цена продажи обновлены.\n";
                        }
                        
                        cout << "Количество товара '" << supplier_product.name 
                             << "' увеличено на " << quantity << " единиц.\n";
                        cout << "Новое количество: " << g_shop.products[shop_index].quantity << endl;
                    } else {
                        // Товара нет в магазине, добавляем новый
                        if (g_shop.product_count >= MAX_PRODUCTS) {
                            cout << "Достигнут максимум товаров в магазине!\n";
                            pause_screen();
                            break;
                        }
                        
                        product new_product;
                        strcpy(new_product.name, supplier_product.name);
                        new_product.purchase_price = supplier_product.purchase_price;
                        new_product.markup_percentage = markup;
                        new_product.selling_price = selling_price;
                        new_product.quantity = quantity;
                        new_product.weight = supplier_product.weight;
                        
                        g_shop.products[g_shop.product_count] = new_product;
                        g_shop.product_count++;
                        
                        cout << "Товар '" << new_product.name << "' добавлен в магазин.\n";
                        cout << "Цена закупки: " << fixed << setprecision(2) << new_product.purchase_price << " руб.\n";
                        cout << "Наценка: " << fixed << setprecision(1) << new_product.markup_percentage << "%\n";
                        cout << "Цена продажи: " << fixed << setprecision(2) << new_product.selling_price << " руб.\n";
                        cout << "Количество: " << new_product.quantity << endl;
                    }
                    
                    // Списание денег и уменьшение количества у поставщика
                    g_shop.balance -= cost;
                    g_supplier.products[supplier_index].quantity -= quantity;
                    
                    // Если у поставщика товар закончился, удаляем его из списка
                    if (g_supplier.products[supplier_index].quantity == 0) {
                        for (int i = supplier_index; i < g_supplier.product_count - 1; i++) {
                            g_supplier.products[i] = g_supplier.products[i + 1];
                        }
                        g_supplier.product_count--;
                        cout << "Товар закончился у поставщика и удален из списка.\n";
                    }
                    
                    cout << "Закупка оформлена успешно!\n";
                    cout << "Стоимость: " << fixed << setprecision(2) << cost << " руб.\n";
                    cout << "Новый баланс магазина: " << fixed << setprecision(2) << g_shop.balance << " руб.\n";
                    pause_screen();
                }
                break;
            case 3:
                generate_supplier_products();
                break;
            case 0:
                cout << "Возврат в меню владельца...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause_screen();
        }
    } while (choice != 0);
}