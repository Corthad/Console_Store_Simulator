#include <iostream>
#include <vector>
#include <limits>
#include <windows.h>

#include "seller.h"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Запуск "Продавца"
    seller::loop();
    return 0;
}
