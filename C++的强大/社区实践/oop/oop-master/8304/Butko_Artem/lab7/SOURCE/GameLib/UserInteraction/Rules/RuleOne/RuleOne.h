//
// Created by Artem Butko on 24.05.2020.
//

#ifndef OOP_NEW_RULEONE_H
#define OOP_NEW_RULEONE_H


#include "../Rule.h"

class RuleOne : public Rule
{
public:
    Field* createField(int players) override;
    int isLose(Field* field);
    void playerCommand(std::string command, Chain *player) override;

private:
    int players;
};


#endif //OOP_NEW_RULEONE_H
