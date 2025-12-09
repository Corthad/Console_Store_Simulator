#include "storage.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <vector>

#include "utils.h"
#include "constants.h"
#include "global.h"

using namespace std;

void initialize() {
    load_all_products_from_file();
    
    load_from_file();
    
    cout << "=== СИМУЛЯТОР МАГАЗИНА ===\n";
    cout << "Данные загружены\n";
    cout << "Всего товаров в базе: " << g_all_products.product_count << endl;
    cout << "Товаров в магазине: " << g_shop.product_count << endl;
    cout << "Баланс магазина: " << fixed << setprecision(2) << g_shop.balance << " руб.\n";
    cout << "Общая прибыль: " << fixed << setprecision(2) << g_shop.total_profit << " руб.\n";
    pause_screen();
}

void load_all_products_from_file() {
    ifstream file(ALL_PRODUCTS_FILE);
    if (!file) {
        cout << "Файл товаров '" << ALL_PRODUCTS_FILE << "' не найден!\n";
        cout << "Создайте файл " << ALL_PRODUCTS_FILE << " с товарами в формате:\n";
        cout << "Название_товара цена_закупки вес\n";
        cout << "Например:\n";
        cout << "Молоко 50.0 1.0\n";
        cout << "Хлеб 30.0 0.5\n";
        pause_screen();
    }
    
    g_all_products.product_count = 0;
    
    while (!file.eof() && g_all_products.product_count < MAX_PRODUCTS) {
        base_product bp;
        
        // Читаем название (может содержать пробелы)
        file >> ws; // Пропускаем пробелы
        if (file.peek() == EOF) break;
        
        // Читаем название до первого пробела (упрощенный вариант)
        file >> bp.name;
        
        // Читаем цену и вес
        file >> bp.purchase_price >> bp.weight;
        
        if (file.fail()) {
            file.clear();
            // Пропускаем строку
            char buffer[256];
            file.getline(buffer, 256);
            continue;
        }
        
        // Проверяем корректность данных
        if (bp.purchase_price <= 0 || bp.weight <= 0) {
            cout << "Предупреждение: товар '" << bp.name << "' имеет некорректные данные и пропущен.\n";
            continue;
        }
        
        g_all_products.products[g_all_products.product_count] = bp;
        g_all_products.product_count++;
    }
    
    file.close();
    
    if (g_all_products.product_count == 0) {
        cout << "В файле товаров нет данных или файл пустой!\n";
    } else {
        cout << "Загружено " << g_all_products.product_count << " товаров из файла.\n";
    }
}

void save_to_file() {
    ofstream file(DATA_FILE);
    if (!file) {
        cerr << "Ошибка сохранения данных!\n";
        return;
    }
    
    file << g_shop.product_count << " " << g_shop.total_profit << " " << g_shop.balance << "\n";
    for (int i = 0; i < g_shop.product_count; i++) {
        file << g_shop.products[i].name << " "
             << g_shop.products[i].purchase_price << " "
             << g_shop.products[i].selling_price << " "
             << g_shop.products[i].quantity << " "
             << g_shop.products[i].weight << " "
             << g_shop.products[i].markup_percentage << "\n";
    }
    file.close();
}

void load_from_file() {
    ifstream file(DATA_FILE);
    if (!file) {
        cout << "Файл данных магазина не найден. Используются начальные значения.\n";
        return;
    }
    
    file >> g_shop.product_count >> g_shop.total_profit >> g_shop.balance;
    for (int i = 0; i < g_shop.product_count; i++) {
        file >> g_shop.products[i].name 
             >> g_shop.products[i].purchase_price 
             >> g_shop.products[i].selling_price 
             >> g_shop.products[i].quantity
             >> g_shop.products[i].weight
             >> g_shop.products[i].markup_percentage;
    }
    file.close();
}

bool is_valid_markup(float markup) {
    return markup >= 0.0f && markup <= 500.0f; // Максимум 500% наценки
}

float get_markup_percentage() {
    float markup;
    bool valid_input = false;
    
    cout << "Рекомендуемая наценка: " << DEFAULT_MARKUP_PERCENTAGE << "%\n";
    cout << "Минимальная наценка: " << MIN_MARKUP_PERCENTAGE << "%\n";
    cout << "Максимальная наценка: " << MAX_MARKUP_PERCENTAGE << "%\n";
    
    while (!valid_input) {
        cout << "Введите наценку в процентах (например, 30 для 30%): ";
        cin >> markup;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите число.\n";
        } else if (!is_valid_markup(markup)) {
            cout << "Ошибка! Наценка должна быть от 0 до 500%.\n";
        } else {
            valid_input = true;
        }
    }
    
    return markup;
}

int find_product_by_name(const char* name) {
    for (int i = 0; i < g_shop.product_count; i++) {
        if (strcmp(g_shop.products[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void print_product(const product& p) {
    cout << left << setw(20) << p.name 
         << setw(15) << fixed << setprecision(2) << p.purchase_price 
         << setw(15) << fixed << setprecision(2) << p.selling_price 
         << setw(10) << p.quantity 
         << setw(10) << fixed << setprecision(2) << p.weight
         << setw(10) << fixed << setprecision(1) << p.markup_percentage
         << setw(15) << fixed << setprecision(2) << p.selling_price - p.purchase_price << endl;
}

void print_product_customer_view(const product& p) {
    cout << left << setw(20) << p.name 
         << setw(15) << fixed << setprecision(2) << p.selling_price 
         << setw(10) << p.quantity 
         << setw(10) << fixed << setprecision(2) << p.weight << endl;
}

void print_base_product(const base_product& p) {
    cout << left << setw(25) << p.name 
         << setw(15) << fixed << setprecision(2) << p.purchase_price 
         << setw(10) << fixed << setprecision(2) << p.weight << endl;
}

void show_products() {
    clean_screen();
    
    if (g_shop.product_count == 0) {
        cout << "В магазине нет товаров!\n";
        return;
    }
    
    cout << "=== ТОВАРЫ В МАГАЗИНЕ ===\n";
    cout << left << setw(20) << "Название" 
         << setw(15) << "Цена закупки" 
         << setw(15) << "Цена продажи" 
         << setw(10) << "Кол-во" 
         << setw(10) << "Вес (кг)"
         << setw(10) << "Наценка%"
         << setw(15) << "Маржа" << endl;
    cout << string(95, '-') << endl;
    
    for (int i = 0; i < g_shop.product_count; i++) {
        print_product(g_shop.products[i]);
    }
}

void show_all_products_list() {
    clean_screen();
    
    if (g_all_products.product_count == 0) {
        cout << "База товаров пуста!\n";
        return;
    }
    
    cout << "=== ВСЕ ТОВАРЫ ИЗ БАЗЫ ===\n";
    cout << left << setw(25) << "Название" 
         << setw(15) << "Цена закупки" 
         << setw(10) << "Вес (кг)" << endl;
    cout << string(50, '-') << endl;
    
    for (int i = 0; i < g_all_products.product_count; i++) {
        cout << i + 1 << ". ";
        print_base_product(g_all_products.products[i]);
    }
    
    // Показываем, какие из этих товаров уже есть в магазине
    cout << "=== ТОВАРЫ, КОТОРЫЕ УЖЕ ЕСТЬ В МАГАЗИНЕ ===\n";
    if (g_shop.product_count == 0) {
        cout << "В магазине пока нет товаров.\n";
    } else {
        int count_in_shop = 0;
        for (int i = 0; i < g_shop.product_count; i++) {
            // Проверяем, есть ли этот товар в базе
            bool found_in_base = false;
            for (int j = 0; j < g_all_products.product_count; j++) {
                if (strcmp(g_shop.products[i].name, g_all_products.products[j].name) == 0) {
                    found_in_base = true;
                    break;
                }
            }
            
            if (found_in_base) {
                if (count_in_shop == 0) {
                    cout << left << setw(25) << "Название" 
                         << setw(15) << "Цена продажи" 
                         << setw(10) << "Кол-во" 
                         << setw(10) << "Наценка%" << endl;
                    cout << string(60, '-') << endl;
                }
                
                cout << left << setw(25) << g_shop.products[i].name
                     << setw(15) << fixed << setprecision(2) << g_shop.products[i].selling_price
                     << setw(10) << g_shop.products[i].quantity
                     << setw(10) << fixed << setprecision(1) << g_shop.products[i].markup_percentage << "%" << endl;
                count_in_shop++;
            }
        }
        
        if (count_in_shop == 0) {
            cout << "В магазине нет товаров из базы.\n";
        }
    }
}

void search_product() {
    clean_screen();
    
    char search_name[MAX_NAME_LENGTH];
    cout << "Введите название товара для поиска: ";
    cin.ignore();
    cin.getline(search_name, MAX_NAME_LENGTH);
    
    bool found = false;
    for (int i = 0; i < g_shop.product_count; i++) {
        if (strstr(g_shop.products[i].name, search_name) != nullptr) {
            if (!found) {
                clean_screen();
                cout << "=== РЕЗУЛЬТАТЫ ПОИСКА ===\n";
                cout << left << setw(20) << "Название" 
                     << setw(15) << "Цена продажи" 
                     << setw(10) << "Кол-во" 
                     << setw(10) << "Вес (кг)" << endl;
                cout << string(55, '-') << endl;
                found = true;
            }
            print_product_customer_view(g_shop.products[i]);
        }
    }
    
    if (!found) {
        cout << "Товары не найдены!\n";
    }
}

// Функции сравнения для сортировки
bool compare_by_name(const product& a, const product& b) {
    return strcmp(a.name, b.name) < 0;
}

bool compare_by_selling_price(const product& a, const product& b) {
    return a.selling_price < b.selling_price;
}

bool compare_by_purchase_price(const product& a, const product& b) {
    return a.purchase_price < b.purchase_price;
}

bool compare_by_quantity(const product& a, const product& b) {
    return a.quantity < b.quantity;
}

bool compare_by_weight(const product& a, const product& b) {
    return a.weight < b.weight;
}

bool compare_by_markup(const product& a, const product& b) {
    return a.markup_percentage < b.markup_percentage;
}

void sort_products(int criteria) {
    clean_screen();
    
    if (g_shop.product_count == 0) {
        cout << "Нет товаров для сортировки!\n";
        return;
    }
    
    switch (criteria) {
        case 1:
            sort(g_shop.products, g_shop.products + g_shop.product_count, compare_by_name);
            cout << "Товары отсортированы по названию.\n";
            break;
        case 2:
            sort(g_shop.products, g_shop.products + g_shop.product_count, compare_by_selling_price);
            cout << "Товары отсортированы по цене продажи.\n";
            break;
        case 3:
            sort(g_shop.products, g_shop.products + g_shop.product_count, compare_by_purchase_price);
            cout << "Товары отсортированы по цене закупки.\n";
            break;
        case 4:
            sort(g_shop.products, g_shop.products + g_shop.product_count, compare_by_quantity);
            cout << "Товары отсортированы по количеству.\n";
            break;
        case 5:
            sort(g_shop.products, g_shop.products + g_shop.product_count, compare_by_weight);
            cout << "Товары отсортированы по весу.\n";
            break;
        case 6:
            sort(g_shop.products, g_shop.products + g_shop.product_count, compare_by_markup);
            cout << "Товары отсортированы по наценке.\n";
            break;
        default:
            cout << "Неверный критерий сортировки!\n";
            return;
    }
    
    show_products();
}

void add_product() {
    clean_screen();
    
    if (g_all_products.product_count == 0) {
        cout << "База товаров пуста! Сначала загрузите товары в файл " << ALL_PRODUCTS_FILE << ".\n";
        pause_screen();
        return;
    }
    
    if (g_shop.product_count >= MAX_PRODUCTS) {
        cout << "Достигнут максимум товаров в магазине!\n";
        pause_screen();
        return;
    }
    
    show_all_products_list();
    
    cout << "Вы можете:\n";
    cout << "1. Добавить товар из базы\n";
    cout << "2. Добавить новый товар (не из базы)\n";
    cout << "3. Отмена\n";
    cout << "Выберите вариант: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        clean_screen();
        show_all_products_list();
        cout << "Введите номер товара из базы (1-" << g_all_products.product_count << "): ";
        int product_num;
        cin >> product_num;
        
        if (cin.fail() || product_num < 1 || product_num > g_all_products.product_count) {
            cout << "Неверный номер товара!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_screen();
            return;
        }
        
        int base_index = product_num - 1;
        const base_product& bp = g_all_products.products[base_index];
        
        // Проверяем, есть ли такой товар уже в магазине
        int existing_index = find_product_by_name(bp.name);
        if (existing_index != -1) {
            clean_screen();
            cout << "Товар '" << bp.name << "' уже есть в магазине. Обновление количества...\n";
            cout << "Введите количество для добавления: ";
            int add_quantity;
            cin >> add_quantity;
            
            if (cin.fail() || add_quantity <= 0) {
                cout << "Неверное количество!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause_screen();
                return;
            }
            
            g_shop.products[existing_index].quantity += add_quantity;
            clean_screen();
            cout << "Количество товара обновлено. Новое количество: " << g_shop.products[existing_index].quantity << endl;
            pause_screen();
            return;
        }
        
        // Получаем наценку от пользователя
        clean_screen();
        float markup = get_markup_percentage();
        
        // Получаем количество
        int quantity;
        cout << "Введите начальное количество: ";
        cin >> quantity;
        
        if (cin.fail() || quantity <= 0) {
            cout << "Неверное количество!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_screen();
            return;
        }
        
        // Создаем товар для магазина
        product new_product;
        strcpy(new_product.name, bp.name);
        new_product.purchase_price = bp.purchase_price;
        new_product.markup_percentage = markup;
        new_product.selling_price = bp.purchase_price * (1 + markup / 100);
        new_product.quantity = quantity;
        new_product.weight = bp.weight;
        
        g_shop.products[g_shop.product_count] = new_product;
        g_shop.product_count++;
        
        clean_screen();
        cout << "Товар успешно добавлен!\n";
        cout << "Название: " << new_product.name << endl;
        cout << "Цена закупки: " << fixed << setprecision(2) << new_product.purchase_price << " руб.\n";
        cout << "Наценка: " << fixed << setprecision(1) << new_product.markup_percentage << "%\n";
        cout << "Цена продажи: " << fixed << setprecision(2) << new_product.selling_price << " руб.\n";
        cout << "Количество: " << new_product.quantity << endl;
        cout << "Вес: " << fixed << setprecision(2) << new_product.weight << " кг\n";
        pause_screen();
        
    } else if (choice == 2) {
        clean_screen();
        // Добавление нового товара (не из базы)
        product new_product;
        cout << "Введите название товара: ";
        cin.ignore();
        cin.getline(new_product.name, MAX_NAME_LENGTH);
        
        // Проверка существования товара
        for (int i = 0; i < g_shop.product_count; i++) {
            if (strcmp(g_shop.products[i].name, new_product.name) == 0) {
                clean_screen();
                cout << "Товар уже существует. Обновление количества...\n";
                cout << "Введите количество для добавления: ";
                int add_quantity;
                cin >> add_quantity;
                if (cin.fail() || add_quantity <= 0) {
                    cout << "Неверное количество!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pause_screen();
                    return;
                }
                g_shop.products[i].quantity += add_quantity;
                clean_screen();
                cout << "Количество товара обновлено. Новое количество: " << g_shop.products[i].quantity << endl;
                pause_screen();
                return;
            }
        }
        
        cout << "Введите цену закупки: ";
        cin >> new_product.purchase_price;
        if (cin.fail() || new_product.purchase_price <= 0) {
            cout << "Неверная цена закупки!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_screen();
            return;
        }
        
        float markup = get_markup_percentage();
        new_product.markup_percentage = markup;
        new_product.selling_price = new_product.purchase_price * (1 + markup / 100);
        
        cout << "Введите начальное количество: ";
        cin >> new_product.quantity;
        if (cin.fail() || new_product.quantity <= 0) {
            cout << "Неверное количество!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_screen();
            return;
        }
        
        cout << "Введите вес одной единицы товара (кг): ";
        cin >> new_product.weight;
        if (cin.fail() || new_product.weight <= 0) {
            cout << "Неверный вес!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_screen();
            return;
        }
        
        g_shop.products[g_shop.product_count] = new_product;
        g_shop.product_count++;
        
        clean_screen();
        cout << "Товар успешно добавлен!\n";
        pause_screen();
    } else if (choice == 3) {
        // Отмена
        return;
    } else {
        cout << "Неверный выбор!\n";
        pause_screen();
    }
}