
#ifndef OOP_GAMESAVEREQUEST_H
#define OOP_GAMESAVEREQUEST_H

#include "../IRequest.h"

/*
 * GameSaveRequest -- класс-команда для сохранения и загрузки.
 */

class GameSaveRequest : public IRequest
{
public:
    GameSaveRequest(Field* field) : IRequest(field) {};
    void Command() override;
};



#endif //OOP_GAMESAVEREQUEST_H
