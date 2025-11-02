#ifndef CONFIG_H
#define CONFIG_H

namespace config {
    // ITEMS
    const unsigned COLUMNS_COUNT = 3;
    const unsigned ITEMS_COUNT = 5;

    const char ITEMS_NAME[ITEMS_COUNT][20] {
        "Milk", "Bread", "Water", 
        "Salt", "Sugar"
    };
    const unsigned ITEMS_PRICE[ITEMS_COUNT][2] {
        {85, 280}, {45, 115}, {25, 65}, 
        {35, 70}, {45, 90}
    };
    const unsigned ITEMS_WEIGHT[ITEMS_COUNT][2] {
        {200, 1'000}, {200, 350}, {350, 1'500}, 
        {200, 1'000}, {500, 1'000}
    };

    // SUPPLIER
    const unsigned SUPPLIERS_COUNT = 7;
    const char SUPPLIERS_NAME[SUPPLIERS_COUNT][30] {
        "EcoFood", "Prime Pantry Partners", 
        "Golden Berries", "Scarlet Pumpkin",
        "WOF Inc.", "Health Basket", "Food Treasure"
    };

    // BUYER
    const unsigned BUYERS_COUNT = 10;
    const char BUYERS_NAME[BUYERS_COUNT][30] {
        "John", "George", "Anton", "Alice",
        "Lizy", "Jackson", "Peter", "Iris",
        "Subaru", "Helga"
    };

    // SELLER
    const unsigned SELLERS_COUNT = 5;
    const char SELLERS_NAME[SELLERS_COUNT][30] {
        "Astroberry", "Star", "Victorial",
        "Elmur", "Garry`s Store"
    };
}

#endif // CONFIG_H