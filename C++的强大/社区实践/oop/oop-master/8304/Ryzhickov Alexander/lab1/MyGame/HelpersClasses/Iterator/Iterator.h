//
// Created by Alex on 05.03.2020.
//

#ifndef MYGAME_ITERATOR_H
#define MYGAME_ITERATOR_H
/*class Iterator {
private:
    GameCell **iteratorGameCell;
    int count;
    int my_Width;
public:


    Iterator(GameCell **gameCell, int width) {
        iteratorGameCell = gameCell;
        count = 0;
        my_Width = width;
    };

    GameCell& operator+(int number) {
        count = count + number;
        return *(iteratorGameCell[count / my_Width] + count / my_Width);
    };

    GameCell& operator-(int number) {
        count = count - number;
        return *(iteratorGameCell[count / my_Width] + count / my_Width);

    };

    GameCell& operator++() {
        count++;
        return *(iteratorGameCell[count / my_Width] + count / my_Width);

    };

    GameCell& operator--() {
        count--;
        return *(iteratorGameCell[count / my_Width] + count / my_Width);

    };

    bool operator!=(const Iterator &it) {
        return count != it.count;
    }

    bool operator==(const Iterator &it) {
        return count == it.count;
    };

    GameCell begin() {
        return *(iteratorGameCell[count / my_Width] + count / my_Width);
    }

    GameCell end() {
        return *(iteratorGameCell[count / my_Width] + count / my_Width);
    }
};*/
#endif //MYGAME_ITERATOR_H
