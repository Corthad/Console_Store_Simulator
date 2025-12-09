#ifndef STORAGE_H
#define STORAGE_H

#include "structures.h"

// Инициализация и работа с данными
void initialize();
void save_to_file();
void load_from_file();
void load_all_products_from_file();
void show_all_products_list();

// Функции для товаров
void add_product();
void show_products();
void search_product();
void sort_products(int criteria);
int find_product_by_name(const char* name);
void print_product(const product& p);
void print_product_customer_view(const product& p);
void print_base_product(const base_product& p);

// Утилиты для ввода
bool is_valid_markup(float markup);
float get_markup_percentage();

#endif // STORAGE_H