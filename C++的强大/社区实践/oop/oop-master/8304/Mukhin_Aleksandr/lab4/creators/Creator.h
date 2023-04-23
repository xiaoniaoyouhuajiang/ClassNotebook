#ifndef LAB1_CREATOR_H
#define LAB1_CREATOR_H

#include "Unit.h"
#include <iostream>
#include <string.h>
#include <memory>

class Unit;
/*!
 * @brief Класс-фабрика по созданию юнитов различного типа
 * @var Creator::attack величина атаки
 * @var Creator::defense величина защиты
 * @var Creator::health величина здоровья
 */
class Creator {
public:
    Creator() = default;
    virtual ~Creator() {};
    /*!
     * @brief Возвращает указатель на созданного юнита
     * @details Определена в каждом классе потомке
     * @return указатель на созданного юнита
     */
    virtual std::shared_ptr<Unit> make_unit() const = 0;
    void greeting() const;
};


#endif
