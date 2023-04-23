
#ifndef OOP_RULESECOND_H
#define OOP_RULESECOND_H


#include "Rule.h"

class RuleSecond : public Rule
{
public:
    Field* createField(int players) override;
    int isLose(Field* field);
    void playerCommand(std::string command, Chain *player) override;

private:
    int players;
};


#endif //OOP_RULESECOND_H
