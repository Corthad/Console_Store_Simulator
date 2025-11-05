#ifndef BUYER_H // Если макрос BUYER_H не определён...
#define BUYER_H // ...определить его и продолжить компиляцию.

#include <string>
#include <vector>

namespace buyer {
    struct inventory {
        int paper_money;
        int digit_money;
        int hand_capacity;
    };

    struct item {
        std::string name;
        unsigned price;
        unsigned qty;
        unsigned weight;
    };

    extern std::vector<item> cart;
    extern inventory inv;

    void start_buyer();
    void load_data();
    void save_data();
    void view_inventory();
    void view_cart();
    void add_to_cart();
    void del_from_cart();
    void go_to_checkout();
}

#endif // Конец блока #ifndef