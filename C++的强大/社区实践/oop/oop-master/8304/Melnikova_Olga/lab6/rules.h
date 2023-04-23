#ifndef RULES_H
#define RULES_H

/*
 * Правила игры должны определять начальное состояние игры
 * Правила игры должны определять условия выигрыша игроков
 * Правила игры должны определять очередность ходов игрока
*/

class Rules
{
public:
    bool first;
    bool end;
    bool currNumBase;
};

#endif // RULES_H
