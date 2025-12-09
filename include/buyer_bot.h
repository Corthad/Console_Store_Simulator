#ifndef BUYER_BOT_H
#define BUYER_BOT_H

#include "structures.h"

// Функции для автоматизированного поведения покупателя (используются в симуляции рабочего дня)
customer_data generate_random_customer(int id);
bool try_add_product_to_customer_basket(customer_data& customer, int product_index);
void process_customer_checkout(customer_data& customer);
void simulate_customer_purchase(customer_data& customer);

#endif // BUYER_BOT_H