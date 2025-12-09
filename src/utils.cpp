#include "utils.h"

#include <iostream>
#include <limits>
#include <windows.h>


using namespace std;

void clean_screen() {
    cout << "\033c";
}

void pause_screen() {
    system("pause");
    clean_screen();
}