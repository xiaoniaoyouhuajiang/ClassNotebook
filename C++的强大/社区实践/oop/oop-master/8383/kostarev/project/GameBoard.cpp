#include <iostream>
#include "GameBoard.h"
#include "Cell.h"

Board::Board(int w, int h){
    objectOnBoard = 0;
    coin = 2000;
    width = w;
    height = h;
    cells = new Cell**[height];
    for (int i = 0; i < height; i++){
        cells[i] = new Cell*[width];
        for (int j = 0; j < width; j++)
            cells[i][j] = new Cell();
    }
}

Board::Board(const Board& old) {
    this->objectOnBoard = old.objectOnBoard;
    this->coin = old.coin;
    this->width = old.width;
    this->height = old.height;
    cells = new Cell**[height];
    for (int i = 0; i < height; i++){
        cells[i] = new Cell*[width];
        for(int j = 0; j < width; j++){
            cells[i][j] = new Cell(*(old.cells[i][j]));
        }
    }
}

Board::Board(Board&& old){
    this->objectOnBoard = old.objectOnBoard;
    this->coin = old.coin;
    this->width = old.width;
    this->height = old.height;
    cells = new Cell**[height];
    for (int i = 0; i < height; i++){
        cells[i] = new Cell*[width];
        for(int j = 0; j < width; j++){
            cells[i][j] = new Cell(*(old.cells[i][j]));
        }
    }
    old.cells = nullptr;
    old.height = old.width = old.coin = old.objectOnBoard = 0;
}

int Board::getWidth() {
    return this->width;
}

int Board::getHeight() {
    return this->height;
}

void Board::newBuild() {
    int x, y;
    char type;
    std::cout << "ADD BUILD, Enter x, y:" << std::endl;
    std::cin >> x >> y;
    if (x > width || y > height || x < 1 || y < 1){
        std::cout << "WARNING!" << std::endl;
        return;
    }
    std::cout << "D, H, F, O, P, S, V:";
    std::cin >> type;
    cells[height-y][x-1]->addBuild(type);
    objectOnBoard++;
    coin -= cells[height-y][x-1]->aboutCell_Saldo();
}

void Board::delBuild() {
    int x, y;
    std::cout << "DEL BUILD, Enter x, y:" << std::endl;
    std::cin >> x >> y;
    if (x > width || y > height || x < 1 || y < 1){
        std::cout << "WARNING!" << std::endl;
        return;
    }
    cells[height-y][x-1]->removeBuild();
    objectOnBoard--;
}

void Board::info() {
    std::cout << "Buildings on board: " << objectOnBoard << std::endl;
    std::cout << "Coin: " << coin << std::endl;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << cells[i][j]->typeBuild() << ' ';
        }
        std::cout << std::endl;
    }
    bool about = true;
    std::cout << "You want to know more about the individual cell? (1 - yes, 0 - no)" << std::endl;
    std::cin >> about;
    while (about){
        int x, y;
        std::cout << "Enter x, y:" << std::endl;
        std::cin >> x >> y;
        cells[height-y][x-1]->aboutCell();
        std::cout << "You want to know more about the individual cell? (1 - yes, 0 - no)" << std::endl;
        std::cin >> about;
    }
}
