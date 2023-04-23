#include <iostream>
#include <ctime>
#include "GameBoardStd.h"

int main(){
    srand(time(0));
    auto city = BoardStd::newBoard();
    return 0;
}