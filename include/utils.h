#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>
#include <limits>

#include "basics.h"

namespace utils {

    const int NUM_TO_STR_COEF = 48;

    const size_t ERR_VALUE = std::numeric_limits<long long>::max();

    /* Константы для выравнивания текста. */
    const char LEFT = 0x00;
    const char CENTER = 0x01;
    const char RIGHT = 0x02;

    /* Получение длины строки (латиница и кирилица). */
    int utf_len(const std::string& str);

    /* Получение длины числа (целочисленного). */
    int num_len(int num);

    /* Перевод числа в строку. */
    std::string num2str(long long num);
    /* Перевод строки в число. */
    long long str2num(const std::string& str);

    /* Безопасное получение строки из ввода. */
    std::string input(const std::string& header = "");
    /* Безопасное получение числа из ввода. */
    long long get_num(const std::string& header = "");
    unsigned long long get_unum(const std::string& header = "");

    /**
     * @brief Создание окна с выбором.
     * 
     * @param header заголовок "окна".
     * @param choice возможные варианты выбора.
     * @param alignment выравнивание "окна". По умолчанию: LEFT.
     * 
     * @return `idx` - индекс выбранного значения.
     */
    int request(const std::string& header, const std::vector<std::string>& choice, const char alignment = LEFT);

    /**
     * @brief Вспомогательный метод для получения максимальной длины среди имён, цен, количеств и весов. 
     * @param items Список предметов, где нужно найти максимальные значения длины имени, цены, кол-ва и веса.
     * @return Список из 4-х значений (максимальных длин): [имя, цена, кол-во, вес].
     */
    int* max_params_len(const std::vector<Item>& items);

    /**
     * @brief Отображение данных в табличном виде.
     * @param items Список данных.
     */
    void show_data(std::vector<Item>& items);
    
    /* Случайное число в установленном диапазоне. */
    int randint(int min, int max);
}

#endif // CONSTANTS_H