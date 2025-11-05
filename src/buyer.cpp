#include "buyer.h"
#include "storage.h"

#include <fstream>
#include <iostream>


std::vector<buyer::item> buyer::cart = {};
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
        buyer::item item = buyer::cart[i];
        std::cout << i << ". " << item.name << " " << item.price << " " << item.qty << " " << item.weight << "\n";
    }
}

void buyer::add_to_cart() {
    int id_item;
    while (true) {
        storage::show_data();
        std::cout << "Для выхода из этого режима введите занчение '-1'. \n";
        std::cout << "Чтобы добавить товар в корзину, введите его индекс: ";
        std::cin >> id_item;
        if (id_item == -1) {
            break;
        }
        else {
            storage::Item storage_item = storage::items[id_item];
            buyer::item item = {
                storage_item.name,
                storage_item.price,
                1,
                storage_item.weight 
            };
            buyer::cart.push_back(item);
            storage::change_item_qty(id_item, -1);
        }
        std::cout << "\033c";
    }
}

// void buyer::del_from_cart() {
//     int id_item;
//     while (true) {
//         buyer::view_cart();
//         std::cout << "Для выхода из этого режима введите занчение '-1'. \n";
//         std::cout << "Чтобы добавить товар в корзину, введите его индекс: ";
//         std::cin >> id_item;
//         if (id_item == -1) {
//             break;
//         }
//         else {
//             buyer::item item = buyer::cart[id_item];
//             buyer::item item = {
//                 storage_item.name,
//                 storage_item.price,
//                 1,
//                 storage_item.weight 
//             };
//             buyer::cart.push_back(item);
//             storage::change_item_qty(id_item, -1);
//         }
//         std::cout << "\033c";
//     }
// }


void buyer::start_buyer() {
    int activity_id;

    storage::load_data();

    while (true) {
        std::cout << "Отладка. Введите номер операции: ";
        std::cin >> activity_id;
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
        default:
            break;
        }
        system("pause");
        std::cout << "\033c";
    }
}