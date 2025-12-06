#ifndef GAME_H // Если макрос GAME_H не определён...
#define GAME_H // ...определить его и продолжить компиляцию.

#include <string>
#include <vector>

void game();

const std::string header {
    "Добро пожаловать в консольный симулятор магазина.\n"
    "Выберете тип пользователя:\n"
};

const std::vector<std::string> choice {
    "Покупатель",
    "Продавец",
    "Разработчик (отладка функций склада)",
    "Выход из игры."
};

#endif // GAME_H