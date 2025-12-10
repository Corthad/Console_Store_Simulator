#include "menu.h"

#include <iostream>
#include <iomanip>
#include <limits>

#include "storage.h"
#include "buyer.h"
#include "seller.h"
#include "supplier.h"    
#include "utils.h"
#include "constants.h"
#include "global.h"
#include "structures.h"
#include "events.h"      

using namespace std;

void main_menu() {
    int choice;
    do {
        clean_screen();
        cout << MAIN_MENU;
        cin >> choice;
        
        switch (choice) {
            case 1:
                owner_menu();
                break;
            case 2:
                {
                    reset_customer_data();
                    float initial_money = get_customer_money_input();
                    g_customer.money = initial_money;
                    customer_menu();
                }
                break;
            case 0:
                save_to_file();
                clean_screen();
                cout << "Данные сохранены. Выход...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause_screen();
        }
    } while (choice != 0);
}

void owner_menu() {
    int choice;
    do {
        clean_screen();
        cout << OWNER_MENU;
        cin >> choice;
        
        switch (choice) {
            case 1:
                add_product();
                break;
            case 2:
                show_products();
                pause_screen();
                break;
            case 3:
                show_all_products_list();
                pause_screen();
                break;
            case 4:
                search_product();
                pause_screen();
                break;
            case 5:
                {
                    int sort_choice;
                    clean_screen();
                    cout << SORTING_CRITERIA_MENU;
                    cin >> sort_choice;
                    sort_products(sort_choice);
                    pause_screen();
                }
                break;
            case 6:
                purchase_from_supplier();
                break;
            case 7:
                clean_screen();
                cout << "=== СТАТИСТИКА МАГАЗИНА ===\n";
                cout << "Количество товаров: " << g_shop.product_count << endl;
                cout << "Баланс магазина: " << fixed << setprecision(2) << g_shop.balance << " руб.\n";
                cout << "Общая прибыль: " << fixed << setprecision(2) << g_shop.total_profit << " руб.\n";
                cout << "Прибыль за день: " << fixed << setprecision(2) << g_shop.daily_profit << " руб.\n";
                cout << "Обслужено покупателей: " << g_shop.customers_served << endl;
                pause_screen();
                break;
            case 8:
                simulate_business_day();
                pause_screen();
                break;
            case 9:
                random_event_owner();
                pause_screen();
                break;
            case 0:
                cout << "Возврат в главное меню...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause_screen();
        }
    } while (choice != 0);
}

void customer_menu() {
    int choice;
    do {
        clean_screen();
        cout << "=== РЕЖИМ ПОКУПАТЕЛЯ ===\n";
        cout << "Деньги: " << fixed << setprecision(2) << g_customer.money << " руб.\n";
        cout << "Вместимость корзины: " << g_customer.capacity << " единиц\n";
        cout << "Товаров в корзине: " << g_customer.total_items << "/" << g_customer.capacity << "\n";
        cout << "Макс. вес: " << fixed << setprecision(1) << g_customer.max_weight << " кг (куплено пакетов: " << g_customer.bags_bought << ")\n";
        cout << "Текущий вес корзины: " << fixed << setprecision(1) << g_customer.current_weight << " кг\n";
        cout << CUSTOMER_MENU;
        cin >> choice;
        
        switch (choice) {
            case 1:
                view_available_products();
                pause_screen();
                break;
            case 2:
                add_to_basket();
                break;
            case 3:
                show_basket();
                pause_screen();
                break;
            case 4:
                checkout();
                break;
            case 5:
                clear_basket();
                pause_screen();
                break;
            case 6:
                clean_screen();
                cout << "Выберите способ оплаты:\n";
                cout << "1. Наличные (" << fixed << setprecision(2) << g_customer.money << " руб.)\n";
                cout << "2. Кредитка (без ограничений)\n";
                cout << "Выберите: ";
                cin >> g_customer.payment_method;
                if (g_customer.payment_method == 1 || g_customer.payment_method == 2) {
                    cout << "Способ оплаты изменен.\n";
                } else {
                    cout << "Неверный выбор. Установлен способ оплаты по умолчанию (наличные).\n";
                    g_customer.payment_method = 1;
                }
                pause_screen();
                break;
            case 7:
                buy_bag();
                break;
            case 8:
                random_event_customer();
                pause_screen();
                break;
            case 0:
                cout << "Возврат в главное меню...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause_screen();
        }
    } while (choice != 0);
}