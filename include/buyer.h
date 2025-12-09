#ifndef BUYER_H
#define BUYER_H

#include "structures.h"

void reset_customer_data();
bool is_valid_money_input(float money);
float get_customer_money_input();
void view_available_products();
void add_to_basket();
void show_basket();
void checkout();
void clear_basket();
void buy_bag();
bool can_carry_weight(float additional_weight);

#endif // BUYER_H