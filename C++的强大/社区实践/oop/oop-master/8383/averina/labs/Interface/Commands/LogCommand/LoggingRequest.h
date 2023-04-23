#ifndef OOP_LOGGINGREQUEST_H
#define OOP_LOGGINGREQUEST_H
#include "../../../Field/Field.h"
#include "../IRequest.h"

/*
 * LoggingRequest -- класс-команда для логирования.
 */

class LoggingRequest : public IRequest
{
public:
    LoggingRequest(Field* field) : IRequest(field) {};
    void Command() override;
};




#endif //OOP_LOGGINGREQUEST_H
