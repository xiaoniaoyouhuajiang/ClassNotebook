#include <string>
#include <iostream>
using namespace std;

class Land{
public:
    virtual bool CheckAccess(string type_unit) const = 0;
    virtual string get_type() = 0;
};

class Desert : public Land{
protected:
    string type = "D";

public:
    string get_type(){
        return type;
    }
    bool CheckAccess(string type_unit) const{
        return true;
    }
};

class Forest : public Land{
protected:
    string type = "F";

public:
    string get_type(){
        return type;
    }
    bool CheckAccess(string type_unit) const{
        return true;
    }
};

class Rocks : public Land{
protected:
    string type = "R";

public:
    string get_type(){
        return type;
    }
    bool CheckAccess(string type_unit) const{
        return true;
    }
};

class Proxy : public Land {
private:
    Land *landsc; //Ландшафт

public:

    Proxy(string type){
        if(type == "D"){
            landsc = new Desert;
        }
        else if (type == "R") {
            landsc = new Rocks;
        }
        else if (type == "F"){
            landsc = new Forest;
        }
    }

    bool CheckAccess(string type_unit) const {
        //((map[x1][y1]->print_who() == "D_R" || map[x1][y1]->print_who() == "D_G") && (land[x2][y2]->get_type() == "R"
                    //|| land[x2][y2]->get_type() == "D")) || ((map[x1][y1]->print_who() == "W_F" || map[x1][y1]->print_who() == "W_R") && (land[x2][y2]->get_type() == "F"
                    //|| land[x2][y2]->get_type() == "D")) || ((map[x1][y1]->print_who() == "S_F" || map[x1][y1]->print_who() == "S_L") && (land[x2][y2]->get_type() == "F"
                                                                                                                                       //|| land[x2][y2]->get_type() == "R"))
        if((type_unit == "D_R" || type_unit == "D_G") && ((landsc->get_type() == "R" || landsc->get_type() == "D"))){
            return true;
        }
        if((type_unit == "W_R" || type_unit == "W_F") && ((landsc->get_type() == "F" || landsc->get_type() == "D"))){
            return true;
        }
        if((type_unit == "S_F" || type_unit == "S_L") && ((landsc->get_type() == "R" || landsc->get_type() == "F"))){
            return true;
        }
        return false;
    }

    string get_type(){
        return landsc->get_type();
    }
};
