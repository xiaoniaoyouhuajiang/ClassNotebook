
#ifndef OOP_RULEFIRST_H
#define OOP_RULEFIRST_H


#include "../../Field/Field.h"
#include "Rule.h"

class RuleFirst : public Rule
{
public:
    Field* createField(int players) override;
    int isLose(Field* field);
    void playerCommand(std::string command, Chain *player) override;

private:
    int players;
};


#endif //OOP_RULEFIRST_H
