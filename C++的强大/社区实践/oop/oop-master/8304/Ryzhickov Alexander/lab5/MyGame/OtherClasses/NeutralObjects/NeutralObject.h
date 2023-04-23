//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_NEUTRALOBJECT_H
#define GAME_NEUTRALOBJECT_H


#include <string>

class NeutralObject {
public:
    bool isActive;

    void setIsActive(bool isActive) {
        NeutralObject::isActive = isActive;
    }

    void setCountGameMoves(int countGameMoves) {
        NeutralObject::countGameMoves = countGameMoves;
    }

    int countGameMoves;
    virtual void operator[](int *something) = 0;
    virtual void makeGameMove() = 0;
    virtual std::string getInformationAboutNeutralObject(int *adress1, int *adress2) = 0;
};


#endif //GAME_NEUTRALOBJECT_H
