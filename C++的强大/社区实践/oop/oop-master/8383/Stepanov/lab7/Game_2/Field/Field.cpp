//
//  Field.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Field.hpp"


Field::Field () {
        width = 0;
        height = 0;
        place = nullptr;
        maxBusyCells = 0;
        
    }
 
    Field::~Field () {

        if (place == nullptr) return;

        for (int i = 0; i < width; i++){
           
            for (int j = 0; j < height; j++) {
                
                delete place[i][j].landscape;
            }
            
            delete [] place[i];
        }
        delete [] place;
        
    }
    
    bool Field::createField(int width, int height){
 
        if (width < 7){
        
            std::cout << "Размер должен быть не менее 7x7" << std::endl;
            return false;
        
        } else {
        
            this->width = width;
            this->height = height;
        }
        
        
        srand(static_cast<unsigned int>(time(0)));
        
        ConcreteGround gr;
        ConcreteBush br;
        ConcreteDeepPuddel dp;
        
        this->place = new Cell*[this->width];
              
        for (int i = 0; i < this->width; i++) {
            place[i] = new Cell[this->height];
            
            for (int j = 0; j < this->height; j++){
                          int n = rand()%10;

                          if ((i > width - 5 && j < 4) || (j > height - 5 && i < 4 )
                              || (i <= 1 && j <= 1) || (i >= width-2 && j >= height-2)){
                               
                              place[i][j].landscape = gr.CreateLandscap();

                          } else {

                              if (n == 0){
                                  place[i][j].landscape = br.CreateLandscap();
                              } else if (n == 1) {
                                  place[i][j].landscape = dp.CreateLandscap();
                              } else {
                                  place[i][j].landscape = gr.CreateLandscap();
                              }

                          }

                      }
        }
    
        maxBusyCells = width*height;

        return true;
    }
     
    
    int Field::checkXY (int x, int y) {
        
        if (x > width && y > height) return 0;
        
            return 1;
        
    }

    void Field::setBase(std::string b, int x, int y) {
        place[x][y].base.push_back(b[0]);
        place[x][y].base.push_back(b[1]);
    }

    void Field::setUnit (Unit* u, int x, int y){
        place[x][y].unit = u;
    }

void Field::setNeutralObject (NeutralObject *n, int x, int y){
    place[x][y].neutralObject = n;
}



    int Field::whatInCell (int x, int y) {

        if (x < width && y < height && y > -1 && x > -1)
        return place[x][y].whatHere();

        return -1;
    }


    bool Field::replaceUnit(int fromX, int fromY, int toX, int toY) {
        
        if (place[toX][toY].whatHere() != 4) return false;
        if (toX >= width || toY >= height || toY <= -1 || toX <= -1) return false;

        Unit * u = getUnit(fromX, fromY);
        place[toX][toY].unit = u;
        place[fromX][fromY].unit = nullptr;
        
        return true;
    }


    Unit * Field::getUnit(int x, int y){
        if (x < width && y < height && y > -1 && x > -1)
            return place[x][y].unit;

        return nullptr;
    }

    int Field::getWidth () {return width;}
    int Field::getHeight () {return height;}




std::string Field::getBase(int x, int y){
    return place[x][y].base;
}

Landscape * Field::getLandscape (int x, int y){
    
    return place[x][y].landscape;
}

NeutralObject * Field::getNeutralObject (int x, int y) {
    
    return place[x][y].neutralObject;
}

FieldSnapshot* Field::saveField (){
    
    char **f = new char*[height];
    
    for (int i = 0; i < height; i++){
        f[i] = new char[width];
        for (int j = 0; j < width; j++){
            f[i][j] = place[i][j].landscape->getName();
            
        }
    }
    
    return new FieldSnapshot(height, width, f, busyCells, maxBusyCells);
    
}
   
void Field::restore (FieldSnapshot* snap){
    
    
    this->width = snap->width;
    this->height = snap->height;
    this->busyCells = snap->busyCells;
    this->maxBusyCells = snap->maxBusyCells;
    
    place = new Cell*[height];
    
    ConcreteGround gr;
    ConcreteBush br;
    ConcreteDeepPuddel dp;
       
       for (int i = 0; i < height; i++){
           place[i] = new Cell[width];
           for (int j = 0; j < width; j++){
               
               if (snap->place[i][j] == '#'){
                   place[i][j].landscape = br.CreateLandscap();
               } else if (snap->place[i][j] == '('){
                   place[i][j].landscape = dp.CreateLandscap();
               } else {
                   place[i][j].landscape = gr.CreateLandscap();
               }
               
           }
       }
}
