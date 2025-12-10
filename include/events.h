#ifndef EVENTS_H
#define EVENTS_H

// Случайные события для владельца
void random_event_owner();
void handle_tax_inspection();
void handle_product_damage();
void handle_supplier_discount();

// Случайные события для покупателя
void random_event_customer();
void handle_customer_discount();
void handle_lost_money();
void handle_special_offer();

#endif // EVENTS_H