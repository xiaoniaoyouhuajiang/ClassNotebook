//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_VILLAGE_H
#define GAME_VILLAGE_H


#include "../NeutralObject.h"

class Village : public NeutralObject {
private:
    unsigned goldPoints = 50;
    unsigned *addressMoney = nullptr;
public:
    Village();

    void operator[](unsigned *something) override;

    void makeGameMove() override;
};


#endif //GAME_VILLAGE_H
