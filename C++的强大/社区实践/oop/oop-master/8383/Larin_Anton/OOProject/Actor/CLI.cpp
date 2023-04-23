//
// Created by anton on 5/31/20.
//

#include "CLI.h"

void CLI::notify(std::string str) {
    std::cout<<"Notify:"<<std::endl<<str<<std::endl;
}

void CLI::turn() {
    std::cout<<"Turn "<<name<<std::endl;
    draw();
    std::cout<<"0:summon"<<std::endl;
    std::cout<<"1:select"<<std::endl;
    std::cout<<"2:Interact"<<std::endl;
    std::cout<<"3:exit"<<std::endl;
    std::cout<<"4:restart"<<std::endl;
    std::cout<<"5:save"<<std::endl;
    //std::cout<<""<<std::endl;

    int x;
    std::cin>>x;
    switch (x){
        case 0:{
            iSummon();
            break;
        }
        case 1:{
            iSelect();
            break;
        }
        case 2:{
            iInteract();
            break;
        }
        case 3:{
            iExit();
            break;
        }
        case 4:{
            iRestart();
            break;
        }
        case 5:{
            if(save(name))std::cout<<"Saved"<<std::endl;
            else std::cout<<"Not saved"<<std::endl;
            turn();
            break;
        }
    }
}


void CLI::sel() {

}

void CLI::draw() {
    std::vector<std::vector<FlyCell>> vec;
    std::wstring str = L"";
    vec = getFW();
    int height = vec.size();
    int width = vec.begin()->size();

    for (int j = height; j >= -1; j--) {
        for (int i = -1; i <= width; i++) {
            if (i == -1 || i == width) {
                if (j == -1 || j == height) str += L"#";//Corner element
                else {//Left/right Border
                    str += L'0' + j;
                }
            } else if (j == -1 || j == height) {
                str += L'0' + i;
            } else {
                auto ptr = vec[i][j].getUnit();
                if(ptr){
                    str += ptr->symbol;
                }else{
                    auto ePtr = vec[i][j].getEntity();
                    if(ePtr){
                        str += ePtr->symbol;
                    } else{
                        str += vec[i][j].getTerrain()->symbol;
                    }
                }
            }
        }
        str += L"\n";
    }
    std::wcout<<str<<std::endl;
}

//CLI::CLI() {name = "noname";}

CLI::CLI(const std::string &name):Actor(name) {}

void CLI::iSelect() {
    int x;
    int y;
    bool flagA;
    std::cout<<"0:A"<<std::endl;
    std::cout<<"1:B"<<std::endl;
    std::cin>>x;
    if(x)flagA= false;
    else flagA= true;


    std::cout<<"X:"<<std::endl;
    std::cin>>x;
    std::cout<<x<<std::endl;
    std::cout<<"Y:"<<std::endl;
    std::cin>>y;
    std::cout<<y<<std::endl;
    std::cout<<""<<std::endl;

    if(flagA){
        setSelectionA({x,y});
    }else{
        setSelectionB({x,y});
    }
}

void CLI::iInteract() {
    int x;
    bool flagAct;
    std::cout<<"0:Act"<<std::endl;
    std::cout<<"1:Step"<<std::endl;
    std::cin>>x;
    if(x)flagAct= false;
    else flagAct= true;

    if(flagAct){
        act();
    }else{
        step();
    }
}

void CLI::iExit() {
    exit();
}

void CLI::iRestart() {
    restart();
}

void CLI::iSummon() {
    int x;
    int y;
    std::cout<<"0:TheRanger"<<std::endl;
    std::cout<<"1:ThePowerful"<<std::endl;
    std::cout<<"2:TheAgile"<<std::endl;
    std::cout<<"3:TheMarathoner"<<std::endl;
    std::cout<<"4:TheTough"<<std::endl;
    std::cout<<"5:TheVampire"<<std::endl;

    std::cin>>x;

    UnitClass unitClass =(UnitClass)x;
    /*
    switch ((UnitClass)x){
        case UnitClass::TheRanger:break;
        case UnitClass::ThePowerful:break;
        case UnitClass::TheAgile:break;
        case UnitClass::TheMarathoner:break;
        case UnitClass::TheTough:break;
        case UnitClass::TheVampire:break;
    }
     */

    std::cout<<"X:"<<std::endl;
    std::cin>>x;
    std::cout<<x<<std::endl;
    std::cout<<"Y:"<<std::endl;
    std::cin>>y;
    std::cout<<y<<std::endl;
    std::cout<<""<<std::endl;

    summon(x,y,unitClass);
}

