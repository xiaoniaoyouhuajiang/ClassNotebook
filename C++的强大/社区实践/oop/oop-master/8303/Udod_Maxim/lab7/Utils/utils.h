//
// Created by shenk on 08.04.2020.
//

#ifndef UNTITLED13_UTILS_H
#define UNTITLED13_UTILS_H

#include <string>
#include "../Logs/log.h"
namespace utils {
    unsigned long int StrToInt(std::string s) {

        try {
            return std::stoull(s);
        } catch (std::invalid_argument) {
            game::log << "Неверный формат. Не число." << game::logend;
            return 0;
        } catch (std::out_of_range) {
            game::log << "Неверный формат. Выход за пределы массива." << game::logend;
            return 0;
        } catch (...) {
            game::log << "Неверный формат. Неизвестная ошибка." << game::logend;
            return 0;
        }

    }
}

#endif //UNTITLED13_UTILS_H
