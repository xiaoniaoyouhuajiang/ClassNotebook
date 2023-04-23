
#ifndef OOP_SKIPREQUEST_H
#define OOP_SKIPREQUEST_H


#include "../IRequest.h"

class SkipRequest : public IRequest
{
public:
SkipRequest(Field* field, std::string player) : IRequest(field) { this->player = player;}
void Command() override;
};



#endif //OOP_SKIPREQUEST_H
