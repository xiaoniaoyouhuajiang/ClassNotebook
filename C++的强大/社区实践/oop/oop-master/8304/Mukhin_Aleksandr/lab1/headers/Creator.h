#ifndef LAB1_CREATOR_H
#define LAB1_CREATOR_H
#include "Unit.h"
#include <iostream>
#include <memory>

class Unit;
/*!
 * @brief Класс-фабрика по созданию юнитов различного типа
 */
class Creator {
public:
    virtual ~Creator() {};
    /*!
     * @brief Возвращает указатель на созданного юнита
     * @details Определена в каждом классе потомке
     * @return указатель на созданного юнита
     */
    virtual std::shared_ptr<Unit> make_unit() const = 0;
    char SomeOperation() const;
};


#endif
