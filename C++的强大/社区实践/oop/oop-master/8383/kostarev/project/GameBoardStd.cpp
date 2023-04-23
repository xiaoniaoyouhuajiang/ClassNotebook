#include <iostream>
#include "GameBoardStd.h"

Board *BoardStd::newBoard() {
    int width, height;
    std::cout << "Enter width and height:" << std::endl;
    std::cin >> width >> height;
    if (width > 4 && width < 50 && height > 4 && height < 50){
        return new Board(width, height);
    }
    std::cout << "WARNING!" << std::endl;
    return NULL;
}
