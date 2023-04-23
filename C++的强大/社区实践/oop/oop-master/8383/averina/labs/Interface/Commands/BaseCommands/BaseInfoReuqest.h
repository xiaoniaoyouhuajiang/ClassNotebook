#ifndef OOP_BASEINFOREUQEST_H
#define OOP_BASEINFOREUQEST_H


#include "../IRequest.h"

/*
 * BaseInfoReuqest -- класс-команда получения информации от базы.
 */

class BaseInfoReuqest : public IRequest
{
public:
    BaseInfoReuqest(Field* field, std::string player):
            IRequest(field) { this->player = player;};
    void Command() override;
};

#endif //OOP_BASEINFOREUQEST_H
