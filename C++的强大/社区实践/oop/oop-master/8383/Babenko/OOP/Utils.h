#ifndef LAB2_OOP_UTILS_H
#define LAB2_OOP_UTILS_H

#include <string>
#include "Logging/Log.h"

namespace Utils {
unsigned long int StrToInt(std::string string) {
  try {
    return std::stoull(string);
  } catch (std::invalid_argument) {
    game::log << "[Utils] Неверный формат. Не число." << game::logend;
    return 0;
  } catch (std::out_of_range) {
    game::log << "[Utils] Неверный формат. Выход за пределы массива." << game::logend;
    return 0;
  } catch (...) {
    game::log << "[Utils] Неверный формат. Неизвестная ошибка." << game::logend;
    return 0;
  }
}

}

#endif //LAB2_OOP_UTILS_H
