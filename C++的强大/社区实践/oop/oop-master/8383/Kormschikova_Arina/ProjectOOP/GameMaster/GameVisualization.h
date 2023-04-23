
#ifndef GameVisualization_h
#define GameVisualization_h

#include "GameBlock.h"
#include "NeutralObject.h"

class GameMap;
class GameUnits;

void update(GameMap &map){
    GameBlock* currentBlock;
    int height = map.getHeight();
    int width = map.getWidth();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            std::cout<<" --- ";
        }
        std::cout<<std::endl;
        for(int j = 0; j < width; j++){
            char type = ' ';
            currentBlock = map.getBlock(i, j);
            if (currentBlock->baseOnBlock != nullptr) {
                type = currentBlock->baseOnBlock->type;
            }
            else if(currentBlock->unitOnBlock != nullptr){
                type = currentBlock->unitOnBlock->type;
            }
            else if(currentBlock->objectOnBlock != nullptr){
                type = currentBlock->objectOnBlock->type;
            }
            else{
                type = currentBlock->landscape->type;
            }
            std::cout<<"| "<< type<<" |";
        }
        std::cout<<std::endl;
        }
    for(int j = 0; j < width; j++){
        std::cout<<" --- ";
    }
    std::cout<<std::endl;
}

#endif
