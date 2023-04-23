#ifndef OOP_GETUNITREQUEST_H
#define OOP_GETUNITREQUEST_H

#include "../IRequest.h"

/*
 * GetUnitRequest -- класс-команда создания юнита.
 */

class GetUnitRequest : public IRequest
{
public:
    GetUnitRequest(Field* field, std::string player) : IRequest(field) { this->player = player;}
    void Command() override ;
private:
    char id;
    int x, y;
};


#endif //OOP_GETUNITREQUEST_H
