#include "buyer.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "storage.h"
#include "basics.h"
#include "utils.h"

std::vector<Item> buyer::cart = {};
buyer::inventory buyer::inv;

void buyer::load_data() {
	std::ifstream file;
	std::string path = "../data/buyer.txt";
	
	file.open(path);
	if(!file.is_open()) {
		std::cout << "ERROR: Не удалось получить данные с файла.\n";
	}
    else {
        file >> buyer::inv.paper_money >> buyer::inv.digit_money >> buyer::inv.hand_capacity;
    }
    file.close();
}

void buyer::save_data() {
	std::ofstream file;
	std::string path = "../data/buyer.txt";
	
	file.open(path);
	if(!file.is_open()) {
		std::cout << "ERROR: Не удалось cохранить данные с файла.\n";
	}
    else {
        file << buyer::inv.paper_money << " " << buyer::inv.digit_money << " " << buyer::inv.hand_capacity;
    }
    file.close();	
}

void buyer::view_inventory() {
    std::cout << "У вас при себе бумажных денег: " << buyer::inv.paper_money << "; На карте: " << buyer::inv.digit_money << "; \n";
    std::cout << "За раз вы можете унести товаров, общим весом: " << buyer::inv.hand_capacity << "\n"; 
}

void buyer::view_cart() {
    for (int i = 0; i < buyer::cart.size(); ++i) {
        Item item = buyer::cart[i];
        std::cout << i << ". " << item.name << " " << item.price << " " << item.qty << " " << item.weight << "\n";
    }
}

void buyer::add_to_cart() {
    int id_item;
    bool match_found;
    while (true) {
        match_found = false;
        utils::show_data(buyer::cart);
        std::cout << "Для выхода из этого режима введите значение '-1'. \n";
        std::cout << "Чтобы добавить товар в корзину, введите его индекс: ";
        std::cin >> id_item;
        if (id_item == -1) {
            break;
        }
        else {
            Item storage_item = storage::items[id_item];
            Item item = {
                storage_item.name,
                storage_item.price,
                1,
                storage_item.weight 
            };
            for (Item& item : buyer::cart) {
                if (item.name == storage_item.name && item.price == storage_item.price && item.weight == storage_item.weight) {
                    item.qty += 1;
                    match_found = true;
                }
            }
            if (!match_found) {
                buyer::cart.push_back(item);
            }
            storage::change_item_qty(id_item, -1);
        }
        std::cout << "\033c";
    }
}

void buyer::del_from_cart(bool one_time_launch) {
    int id_item;
    do {
        buyer::view_cart();
        std::cout << "Для выхода из этого режима введите занчение '-1'. \n";
        std::cout << "Чтобы удалить товар из корзины (вренуть его на полку), введите его индекс: ";
        std::cin >> id_item;
        if (id_item == -1) {
            break;
        }
        else {
            Item item = buyer::cart[id_item];
            storage::add_item(item.name, item.price, 1, item.weight);
            if (item.qty == 1) {
                buyer::cart.erase(buyer::cart.begin() + id_item);
            }
            else {
                buyer::cart[id_item].qty -= 1;
            }
        }
        std::cout << "\033c";
    } while(!one_time_launch);
}

void buyer::go_to_checkout() {
    short payment_type;
    bool can_take_it;
    bool can_pay_it;
    int total_weight;
    int total_price = 0; 
    bool try_pay_it[4] {0};   
    do {
        total_weight = 0;
        for (Item &item : buyer::cart) {
            total_weight += (item.weight * item.qty);
        }
        if (total_weight > buyer::inv.hand_capacity) {
            std::cout << "Общий вес корзины: " << total_weight << "\n";
            std::cout << "Вместимость рук: " << buyer::inv.hand_capacity << "\n";
            can_take_it = false;
            std::cout << "Вы не можете унести столько товара. Необходимо выложить часть товаров.\n";
            buyer::del_from_cart(true);
        
        }
        else {
            can_take_it = true;
            std::cout << "Ура. У Вас достаточно сил, чтобы унести все товары.\n";
            system("pause");
            std::cout << "\033c";
            
        }
    } while(!can_take_it);
    do {
        total_price = 0;
        for (Item &item : buyer::cart) {
            total_price += (item.price * item.qty);
        }
        std::cout << "Бумажных денег: " << buyer::inv.paper_money << ". Денег на карте: " << buyer::inv.digit_money << ".\n";
        std::cout << "Итоговая цена товара: " << total_price << ".\n";
        if (try_pay_it[2] || try_pay_it[3]) {
            std::cout << "У Вас недостаточно средств для оплаты текущей корзины. Необходимо убрать часть товаров из корзины.\n";
            buyer::del_from_cart();
            try_pay_it[4] = {0};
            total_price = 0;
        }
        else {


            std::cout << "Выберете способ оплаты.\n";
            std::cout << "1. Наличный расчёт;\n";
            std::cout << "2. Безналичный расчёт;\n";
            std::cout << "3. Смешанный расчёт (приоритет: наличный);\n";
            std::cout << "4. Смешанный расчёт (приоритет: безналичный);\n";
            std::cin >> payment_type;

            switch (payment_type) {
                case 1:
                    if (try_pay_it[payment_type - 1]) {
                        std::cout << "Вы уже пытались оплатить этим способом. У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                    }
                    else {
                        if (buyer::inv.paper_money >= total_price) {
                            buyer::inv.paper_money -= total_price;
                            can_pay_it = true;
                        }
                        else {
                            std::cout << "У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                            try_pay_it[payment_type - 1] = 1;
                        }

                    }
                    break;
                case 2:
                    if (try_pay_it[payment_type - 1]) {
                        std::cout << "Вы уже пытались оплатить этим способом. У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                    }
                    else {
                        if (buyer::inv.digit_money >= total_price) {
                            buyer::inv.digit_money -= total_price;
                            can_pay_it = true;
                        }
                        else {
                            std::cout << "У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                            try_pay_it[payment_type - 1] = 1;
                        }

                    }
                    break;
                case 3:
                    if (try_pay_it[payment_type - 1]) {
                        std::cout << "Вы уже пытались оплатить этим способом. У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                    }
                    else {
                            if (buyer::inv.paper_money >= total_price) {
                                buyer::inv.paper_money -= total_price;
                                can_pay_it = true;
                            }
                            else if ((buyer::inv.digit_money + buyer::inv.paper_money) >= total_price) {
                                total_price -= buyer::inv.paper_money;
                                buyer::inv.paper_money = 0;
                                buyer::inv.digit_money -= total_price;
                                can_pay_it = true;
                            }
                            else {
                            std::cout << "У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                            try_pay_it[payment_type - 1] = 1;
                            }
                        }
                    break;
                case 4:
                    if (try_pay_it[payment_type - 1]) {
                        std::cout << "Вы уже пытались оплатить этим способом. У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                    }
                    else {
                            if (buyer::inv.digit_money >= total_price) {
                                buyer::inv.digit_money -= total_price;
                                can_pay_it = true;
                            }
                            else if ((buyer::inv.digit_money + buyer::inv.paper_money) >= total_price) {
                                total_price -= buyer::inv.digit_money;
                                buyer::inv.digit_money = 0;
                                buyer::inv.paper_money -= total_price;
                                can_pay_it = true;
                            }
                            else {
                            std::cout << "У Вас недостаточно средств. Попробуйте другой тип оплаты.\n";
                            try_pay_it[payment_type - 1] = 1;
                            }
                        }
                    break;
                default:
                    std::cout << "Введен невеный тип оплаты.\n";
            }
        }
        system("pause");
        std::cout << "\033c";
        if (can_pay_it) {
            buyer::cart = {};
            std::cout << "Ура. Вы успешно совершили покупку.\n";
            system("pause");
            std::cout << "\033c";
        }
    } while(!can_pay_it);

    }

void buyer::edit_inventory() {
    int new_digit_money;
    int new_paper_money;
    int new_hand_capacity;
    std::cout << "Введите новые значения для инвентаря в следующем порядке: [Цифровые карте] [Бумажные деньги] [Вместимость рук]\n";
    std::cin >> new_digit_money >> new_paper_money >> new_hand_capacity;
    buyer::inv.digit_money = new_digit_money;
    buyer::inv.paper_money = new_paper_money;
    buyer::inv.hand_capacity = new_hand_capacity;
}

void buyer::start_buyer() {
    int activity_id;
    bool exit_to_main_menu = false;
    storage::load_data();

    while (true) {
        for (const std::string &row : buyer::buyer_activity) {
            std::cout << row << "\n";
        }
        std::cout << "Введите номер активности продавца: ";
        std::cin >> activity_id;
        std::cout << "\033c";
        switch (activity_id)
        {
        case 1:
            buyer::load_data();
            break;
        case 2:
            buyer::save_data();
            break;
        case 3:
            buyer::view_inventory();  
            break; 
        case 4:
            buyer::view_cart();
            break;
        case 5:
            buyer::add_to_cart();
            break;
        case 6:
            buyer::del_from_cart();
            break;
        case 7:
            buyer::go_to_checkout();
            break;
        case 8:
            buyer::edit_inventory();
            break;
        case 9:
            exit_to_main_menu = true;
            break;
        default:
            break;
        }
        system("pause");
        std::cout << "\033c";
        if (exit_to_main_menu) {
            break;
        }
    }
}