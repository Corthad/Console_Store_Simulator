#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "structures.h"

void generate_supplier_products();
void show_supplier_products();
void purchase_from_supplier();
int find_supplier_product_by_name(const char* name);
void print_supplier_product(const product& p);

#endif // SUPPLIER_H