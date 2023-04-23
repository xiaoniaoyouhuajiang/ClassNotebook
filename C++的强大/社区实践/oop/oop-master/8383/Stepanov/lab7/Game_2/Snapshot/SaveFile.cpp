//
//  SaveFile.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 03.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "SaveFile.hpp"

SaveFile::SaveFile(bool writeFile){
    
    if (writeFile){
        fileIn.open("./SaveGame");
    } else {
        fileOut.open("./SaveGame");
    }
    
}

SaveFile::~SaveFile(){
    if (fileIn.is_open()){
        fileIn.close();
    }

    if (fileOut.is_open()){
        fileOut.close();
    }
    
}

void SaveFile::write(BaseSnapshot* first, BaseSnapshot* second, FieldSnapshot* field){
    
    if (fileIn.is_open() == false) {
        std::cout << "Фаил записи не открыт" << std::endl;
        return;
    }
    
    fileIn << field->width << " " << field->height << std::endl;
    
    for (int i = 0; i < field->height; i++){
   
        for (int j = 0; j < field->width; j++){
            fileIn << field->place[i][j];
        }
        fileIn << std::endl;
    }

    
    fileIn << first->name << " "
            << first->x << " "
            << first->y << " "
            << first->numberUnit << " "
            << first->countUnit << std::endl
    << first->concretCountUnit[0] << " "
    << first->concretCountUnit[1] << " "
    << first->concretCountUnit[2] << " ";
    
    if (first->isProtect) {fileIn << 1 << std::endl;}
    else {fileIn << 0 << std::endl;}
    
    for (int i = 0; i < first->names.size(); i++){
        fileIn << first->names[i] << " "
                << first->h[i] << " "
                << first->a[i] << " "
                << first->p[i] << " "
                << first->ux[i] << " "
                << first->uy[i] << " ";
        
        if (first->blocAtt[i]) fileIn << 1 << std::endl;
        else                fileIn << 0 << std::endl;
    }
    
    fileIn << second->name << " "
            << second->x << " "
            << second->y << " "
            << second->numberUnit << " "
            << second->countUnit << std::endl
    << second->concretCountUnit[0] << " "
    << second->concretCountUnit[1] << " "
    << second->concretCountUnit[2] << std::endl;
    
    if (second->isProtect) {fileIn << 1 << std::endl;}
    else {fileIn << 0 << std::endl;}
    
    for (int i = 0; i < second->names.size(); i++){
        fileIn << second->names[i] << " "
                << second->h[i] << " "
                << second->a[i] << " "
                << second->p[i] << " "
                << second->ux[i] << " "
                << second->uy[i] << " ";
        
        if (second->blocAtt[i]) fileIn << 1 << std::endl;
        else                fileIn << 0 << std::endl;
    }
}



bool SaveFile::reed(BaseSnapshot* first, BaseSnapshot* second, FieldSnapshot* field){
    
    if (fileOut.is_open() == false) {
        std::cout << "Фаил записи не открыт" << std::endl;
        return false;
    }
    
    fileOut >> field->width >> field->height;
    
    if (field->width != field->height || field->height < 6 || field->width < 6 ){
        return false;
    }
    
    if (fileOut.get() != '\n') return false;
    
    field->place = new char *[field->height];
    
    for (int i = 0; i < field->height; i++){
        
        field->place[i] = new char[field->width];
    
         for (int j = 0; j < field->width; j++){
             field->place[i][j] = fileOut.get();
             
             if (field->place[i][j] != ' ' && field->place[i][j] != '#' && field->place[i][j] != '('){
                 return false;
             }
         }
        
        if (fileOut.get() != '\n') return false;
     }
    
    
    fileOut >> first->name
            >> first->x
            >> first->y
            >> first->numberUnit
            >> first->countUnit
    >> first->concretCountUnit[0]
    >> first->concretCountUnit[1]
    >> first->concretCountUnit[2];
    
    int isProt;
    
    fileOut >> isProt;
    if (isProt == 1 ) first->isProtect = true;
    else first->isProtect = false;
    
    if (first->name != "B1" || first->x != field->width-1 || first->y != 0 || first->countUnit > 9 || first->countUnit < 1 || first->numberUnit < 0 || first->concretCountUnit[0] > 9 || first->concretCountUnit[0] < 1 || first->concretCountUnit[1] > 9 || first->concretCountUnit[1] < 1 || first->concretCountUnit[2] > 9 || first->concretCountUnit[2] < 1) {return false;}
    
    
    std::string names;
    int h, a, p, ux, uy, blocAtt;

    for (int i = 0; i < first->countUnit; i++){
       
        fileOut >> names >> h >> a >> p >> ux >> uy >> blocAtt;
        
        if ((names[0] != '!' && names[0] != '<' && names[0] != '$') || (names[1] > '9' || names[1] < '1') || h < 1 || a < 1 || p < 1 || ux >= field->height || ux < 0 || uy >= field->width || uy < 0 || (blocAtt != 1 && blocAtt != 0) ) return false;
        
        
        first->names.push_back(names);
        first->h.push_back(h);
        first->a.push_back(a);
        first->p.push_back(p);
        first->ux.push_back(ux);
        first->uy.push_back(uy);
        
        if (blocAtt == 1) first->blocAtt.push_back(true);
        else              first->blocAtt.push_back(false);
    }
    
    
    fileOut >> second->name
            >> second->x
            >> second->y
            >> second->numberUnit
            >> second->countUnit
    >> second->concretCountUnit[0]
    >> second->concretCountUnit[1]
    >> second->concretCountUnit[2];
    
    fileOut >> isProt;
    if (isProt == 1 ) second->isProtect = true;
    else second->isProtect = false;
    
    if (second->name != "B2" || second->x != 0 || second->y != field->height-1 || second->countUnit > 9 || second->countUnit < 1 || second->numberUnit < 0 || second->concretCountUnit[0] > 9 || second->concretCountUnit[0] < 1 || second->concretCountUnit[1] > 9 || second->concretCountUnit[1] < 1 || second->concretCountUnit[2] > 9 || second->concretCountUnit[2] < 1 ) {return false;}

    for (int i = 0; i < second->countUnit; i++){
       
        fileOut >> names >> h >> a >> p >> ux >> uy >> blocAtt;
        
        if ((names[1] != '!' && names[1] != '>' && names[1] != '$') || (names[0] > '9' || names[0] < '1') || h < 1 || a < 1 || p < 1 || ux >= field->height || ux < 0 || uy >= field->width || uy < 0 || (blocAtt != 1 && blocAtt != 0) ) return false;
        
        second->names.push_back(names);
        second->h.push_back(h);
        second->a.push_back(a);
        second->p.push_back(p);
        second->ux.push_back(ux);
        second->uy.push_back(uy);
        
        if (blocAtt == 1) second->blocAtt.push_back(true);
        else              second->blocAtt.push_back(false);
    }
    
    return true;
}
