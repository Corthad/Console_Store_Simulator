#include <iostream>
#include <ctime>
#include <windows.h>

#include "menu.h"
#include "utils.h"
#include "storage.h"

using namespace std;

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand(time(NULL));

    clean_screen();
    initialize();
    main_menu();

    return 0;
}