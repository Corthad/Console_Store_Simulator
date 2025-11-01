#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>

namespace utils
{
    // Константы для выравнивания текста
    const short LEFT = 0x00;
    const short CENTER = 0x01;
    const short RIGHT = 0x02;

    // Получение длины строки (латиница и кирилица)
    int utf_len(const std::string& str);

    // Получение длины числа (целочисленного)
    int num_len(int num);

    /* 
    Создание окна с выбором.

    Args:
    - header: std::string
    Заголовок "окна"
    - choice: std::vector<std::string>
    Возможные варианты выбора
    - alignment: short
    Выравнивание "окна". По умолчанию: LEFT
    */
    int request(const std::string& header, const std::vector<std::string>& choice, const short alignment = LEFT);

    int randint(int min, int max);
}

#endif // CONSTANTS_H