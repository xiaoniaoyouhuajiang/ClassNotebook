#ifndef OOP_MOVEUNITREQUEST_H
#define OOP_MOVEUNITREQUEST_H

#include "../IRequest.h"

/*
 * MoveUnitRequest -- класс-команда создания юнита.
 */

class MoveUnitRequest : public IRequest
{
public:
    MoveUnitRequest(Field* field, std::string player) : IRequest(field) { this->player = player;};
    void Command() override;
private:
    int x, y, i, j;
};

#endif //OOP_MOVEUNITREQUEST_H
