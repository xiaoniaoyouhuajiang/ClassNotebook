//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_NEUTRALOBJECT_H
#define GAME_NEUTRALOBJECT_H


class NeutralObject {
public:
    bool isActive;
    int countGameMoves;
private:
    virtual void operator[](unsigned *something) = 0;
    virtual void makeGameMove() = 0;
};


#endif //GAME_NEUTRALOBJECT_H
