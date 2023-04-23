//
// Created by Artem Butko on 24.05.2020.
//

#ifndef OOP_NEW_RULETWO_H
#define OOP_NEW_RULETWO_H

#include "../Rule.h"

class RuleTwo : public Rule
{
public:
    Field* createField(int players) override;
    int isLose(Field* field);
    void playerCommand(std::string command, Chain *player) override;

private:
    int players;
};


#endif //OOP_NEW_RULETWO_H
