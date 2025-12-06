#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>

namespace utils {
    // Константы для выравнивания текста
    const short LEFT = 0x00;
    const short CENTER = 0x01;
    const short RIGHT = 0x02;

    // Получение длины строки (латиница и кирилица).
    int utf_len(const std::string& str);

    // Получение длины числа (целочисленного).
    int num_len(int num);

    /**
     * @brief Создание окна с выбором.
     * 
     * @param header заголовок "окна".
     * @param choice возможные варианты выбора.
     * @param alignment выравнивание "окна". По умолчанию: LEFT.
     * 
     * @return `idx` - индекс выбранного значения.
    */
    int request(const std::string& header, const std::vector<std::string>& choice, const short alignment = LEFT);

    // Случайное число в установленном диапазоне.
    int randint(int min, int max);
}

#endif // CONSTANTS_H