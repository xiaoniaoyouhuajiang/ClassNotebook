
#ifndef OOP_CREATEUNITREQUEST_H
#define OOP_CREATEUNITREQUEST_H

#include "../IRequest.h"

/*
 * CreateUnitRequest -- класс-команда создания юнита.
 */

class CreateUnitRequest : public IRequest
{
public:
    CreateUnitRequest(Field* field, std::string player) : IRequest(field) { this->player = player;}
    void Command() override ;
private:
    char id;
};


#endif //OOP_CREATEUNITREQUEST_H
