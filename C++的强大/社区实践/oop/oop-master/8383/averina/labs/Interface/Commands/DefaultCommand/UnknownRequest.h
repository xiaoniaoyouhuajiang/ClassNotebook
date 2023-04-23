
#ifndef OOP_UNKNOWNREQUEST_H
#define OOP_UNKNOWNREQUEST_H


#include "../IRequest.h"

/*
 * UnknownRequest -- класс-команда для неизвестной команды.
 */

class UnknownRequest : public IRequest
{
public:
    UnknownRequest() : IRequest(nullptr){};
    void Command() override;
};
#endif //OOP_UNKNOWNREQUEST_H
