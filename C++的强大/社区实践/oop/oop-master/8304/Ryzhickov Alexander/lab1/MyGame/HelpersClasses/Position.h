#ifndef MYGAME_POSITION_H
#define MYGAME_POSITION_H

class Position {
private:
    int x;
    int y;
public:
    Position(int x, int y);

    int getPositionX() const ;
    int getPositionY() const ;
    void setNewPositionX(int newPositionX);
    void setNewPositionY(int newPositionY);
};


#endif //MYGAME_POSITION_H
