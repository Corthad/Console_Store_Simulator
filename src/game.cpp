#include "game.h"

#include <iostream>
#include <windows.h>

#include "buyer.h"
#include "seller.h"
#include "utils.h"

void game() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int action_idx = 0;

    std::cout << "\033c";

    while (true) {
        action_idx = utils::request(header, choice);
        std::cout << "\033c";
        switch(action_idx) {
            case 1: {
                buyer::start_buyer();
                break;
            }
            case 2: {
                //start_seller();
                std::cout << "Этот раздел еще находится в разработке. Прошу проявить терпение.\n";
                system("pause");
                break;
            }
            case 3: {
                seller::loop();
                break;
            }
            case 4: {
                return;
            }
        }
    }
}