#include "global.h"

shop_data g_shop = {{}, 0, 0.0f, 0.0f, 10000.0f, 0};
supplier_data g_supplier = {{}, 0, false};
all_products_data g_all_products = {{}, 0};
customer_data g_customer = {0.0f, MAX_BASKET_CAPACITY, INITIAL_MAX_WEIGHT, 0.0f, {}, 0, 0, 1, 0, 0};