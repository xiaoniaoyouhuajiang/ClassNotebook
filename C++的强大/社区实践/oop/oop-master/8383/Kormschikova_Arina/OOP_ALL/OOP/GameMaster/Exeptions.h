
#ifndef Exeptions_h
#define Exeptions_h
#include <iostream>
#include <cstdlib>
#include <sstream>
class GameException{
private:
    int code;
    std::string baseInfo;
    
public:
    GameException(int code):code(code){
        switch (code) {
            case 1:
                baseInfo = "LoadException";
                break;
            case 2:
                baseInfo = "BlockAccessException";
            default:
                break;
        }
    };
    
    virtual std::string message(){
        std::stringstream mes;
         mes<<"Error code "<<code<<" "<<baseInfo;
        return mes.str();
    }
    virtual void what(){
        std::cout<<message();
    }
};

class LoadException: public GameException{
private:
    int addСode;
    int errorSet;
    std::string extendedInfo;
public:
    LoadException(int addCode, int errorSet = 0):GameException(1), errorSet(errorSet){
       switch (addCode) {
           case 1:
                extendedInfo = "wrong count team load ";
                break;
           case 2:
               extendedInfo = "wrong energy for step load ";
               break;
           case 3:
               extendedInfo = "wrong map load ";
               break;
           case 4:
               extendedInfo = "wrong NPC load ";
               break;
           case 5:
               extendedInfo = "wrong units load ";
               break;
           case 6:
               extendedInfo = "wrong enemies load ";
               break;
           case 7:
               extendedInfo = "wrong neutrl objects load ";
               break;
            default:
               extendedInfo = "";
               break;
                break;
        }
        switch (errorSet){
            case 0:
                break;
            case 1:
                extendedInfo+=" error set unit on map";
                break;
            case 2:
                extendedInfo+=" error set base on map";
                break;
            case 3:
                extendedInfo+=" error set neutral object on map";
                break;
            default:
                extendedInfo += "";
                break;
        }
    }
    std::string message() override{
        std::stringstream mes;
        mes<<GameException::message();
        mes<<"Add code "<<addСode<<"."<<errorSet<<" "<<extendedInfo;
        return mes.str();
    }
    void what() override{
        std::cout<<message();
    }
};

class BlockAccessException: public GameException{
private:
    int x;
    int y;
public:
    BlockAccessException(int x, int y):GameException(2),x(x),y(y){};
    std::string message() override{
            std::stringstream mes;
            mes<<GameException::message();
            mes<<" Attempt to access coordinates on a map("<<x<<","<<y<<")";
            return mes.str();
        }
        void what() override{
            std::cout<<message();
        }
};

#endif /* Exeptions_h */

