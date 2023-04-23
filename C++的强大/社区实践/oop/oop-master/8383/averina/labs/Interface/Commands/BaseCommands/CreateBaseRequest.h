#ifndef OOP_CREATEBASEREQUEST_H
#define OOP_CREATEBASEREQUEST_H

#include "../IRequest.h"

/*
 * CreateBaseRequest -- класс-команда создания базы.
 */

class CreateBaseRequest : public IRequest
{
public:
    CreateBaseRequest(Field* field) : IRequest(field) {};
    void Command() override;

private:
    int x, y;
    int unitLimit;
};


#endif //OOP_CREATEBASEREQUEST_H
