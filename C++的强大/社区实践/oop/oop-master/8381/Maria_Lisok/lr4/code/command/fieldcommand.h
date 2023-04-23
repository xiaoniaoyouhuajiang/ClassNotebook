#ifndef FIELDCOMMAND_H
#define FIELDCOMMAND_H

#include "command.h"

#include "playingfield.h"


class FieldCommand : public Command
{
private:
    map<string, int> landscapeInfo();
    map<string, int> unitsInfo();
    map<string, int> neutralslInfo();
    map<string, int> neutrallInfo();
    map<string, int> unitlInfo();
    map<string, int> landCelllInfo();
    map<string, int> neutralFind();
    map<string, int> unitFind();
    map<string, int> unitMove();
protected:
    map<string, int> noSuchAct();
    PlayingField* field;
    Unit* unit;
    NeutralObj* neutral;
public:
    FieldCommand(PlayingField* field, Actions act, map<string, Data> param);
    FieldCommand(PlayingField* field, Actions act, map<string, Data> param, Unit* u, NeutralObj* n);
    Unit* findItem();
    map<string, int> mainInfoAboutObj();
};

#endif // FIELDCOMMAND_H
