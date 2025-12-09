#ifndef CONSTANTS_H
#define CONSTANTS_H

// "Общие" константы
const int MAX_PRODUCTS = 200;
const int MAX_NAME_LENGTH = 50;
const int MAX_BASKET_CAPACITY = 10;
const char DATA_FILE[] = "../data/shop_data.txt";
const char ALL_PRODUCTS_FILE[] = "../data/all_products.txt";
const int MAX_BASKET_ITEMS = 20;
const float MAX_TOTAL_WEIGHT = 20.0f;      // Максимальный вес с учетом пакетов
const float BAG_WEIGHT_INCREASE = 5.0f;    // Увеличение веса при покупке пакета
const float BAG_PRICE = 50.0f;             // Цена пакета
const float INITIAL_MAX_WEIGHT = 5.0f;     // Начальный максимальный вес без пакетов

const char MAIN_MENU[] =    "=== ГЛАВНОЕ МЕНЮ ===\n" 
                            "1. Режим владельца магазина\n"
                            "2. Режим покупателя\n"
                            "0. Выход\n"
                            "Выберите роль: ";

const char OWNER_MENU[] =   "=== РЕЖИМ ВЛАДЕЛЬЦА ===\n"
                            "1. Добавить товар\n"
                            "2. Показать товары в магазине\n"
                            "3. Показать все товары из базы\n"
                            "4. Поиск товара в магазине\n"
                            "5. Сортировать товары\n"
                            "6. Закупка у поставщика\n"
                            "7. Статистика магазина\n"
                            "8. Симуляция рабочего дня\n"
                            "9. Случайное событие\n"
                            "0. Вернуться в главное меню\n"
                            "Выберите действие: ";

const char SORTING_CRITERIA_MENU[] =  "Сортировать по:\n"
                                    "1. Названию\n"
                                    "2. Цене продажи\n"
                                    "3. Цене закупки\n"
                                    "4. Количество\n"
                                    "5. Весу\n"
                                    "6. Наценке\n"
                                    "Выберите критерий: ";

const char CUSTOMER_MENU[] =    "1. Просмотреть товары\n"
                                "2. Добавить в корзину\n"
                                "3. Показать корзину\n"
                                "4. Оформить покупку\n"
                                "5. Очистить корзину\n"
                                "6. Выбрать способ оплаты\n"
                                "7. Купить пакет\n"
                                "8. Случайное событие\n"
                                "0. Вернуться в главное меню\n"
                                "Выберите действие: ";

const char SUPPLIER_MENU[] =    "=== ЗАКУПКА У ПОСТАВЩИКА ===\n"
                                "1. Показать товары у поставщика\n"
                                "2. Купить товар\n"
                                "3. Обновить ассортимент поставщика (генерация новых товаров)\n"
                                "0. Вернуться в меню владельца\n"
                                "Выберите действие: ";
 
// Константы для симуляции дня
const int MIN_CUSTOMERS_PER_DAY = 3;       // Минимальное количество покупателей в день
const int MAX_CUSTOMERS_PER_DAY = 10;      // Максимальное количество покупателей в день
const float MIN_CUSTOMER_MONEY = 100.0f;   // Минимальные деньги у покупателя
const float MAX_CUSTOMER_MONEY = 5000.0f;  // Максимальные деньги у покупателя
const int MIN_CUSTOMER_CAPACITY = 1;       // Минимальная вместимость корзины
const int MAX_CUSTOMER_CAPACITY = 8;       // Максимальная вместимость корзины
const float MIN_CUSTOMER_WEIGHT = 2.0f;    // Минимальный вес, который может унести покупатель
const float MAX_CUSTOMER_WEIGHT = 8.0f;    // Максимальный вес, который может унести покупатель

// Константы для поставщика
const int MIN_SUPPLIER_PRODUCTS = 5;       // Минимальное количество всех товаров у поставщика
const int MAX_SUPPLIER_PRODUCTS = 15;      // Максимальное количество всех товаров у поставщика
const int MIN_SUPPLIER_QUANTITY = 10;      // Минимальное количество единиц товара у поставщика
const int MAX_SUPPLIER_QUANTITY = 100;     // Максимальное количество единиц товара у поставщика
const float DEFAULT_MARKUP_PERCENTAGE = 30.0f; // Стандартная наценка (30%)
const float MIN_MARKUP_PERCENTAGE = 10.0f; // Минимальная наценка
const float MAX_MARKUP_PERCENTAGE = 100.0f; // Максимальная наценка

#endif // CONSTANTS_H