#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include <base.h>

struct S_field{
    unsigned int width;
    unsigned int height;
};

struct S_land{
    vector<string> type;
};

struct S_base{
    unsigned int x;
    unsigned int y;
    unsigned int max_item;
    unsigned int now_item;
    int health;
};

struct S_bonus{
    unsigned int x;
    unsigned int y;
    int health = 0;
    int attack = 0;
};

struct S_unit{
    string name;
    unsigned int x;
    unsigned int y;
    int health;
    int nearAttack = 0;
    int furtherAttack = 0;
    int radius_attack = 0;
    int accuracy = 0;
    int attack_speed = 0;
};

struct S_all{
    vector<S_bonus> s_bonus;
    vector<S_unit> s_unit;
    S_field s_field;
    S_land s_land;
    S_base s_base;
};


class Memento_write{
    ofstream log_wr;
public:
    Memento_write(){
        log_wr.open("memento.txt"); // открываем файл
    }

    void write_all(struct S_all s_all){
        log_wr << "Field\n";
        log_wr << s_all.s_field.width << " " << s_all.s_field.height << "\n";
        log_wr << "Land\n";
        for (unsigned int i = 0; i < s_all.s_land.type.size(); i++) {
            log_wr << s_all.s_land.type[i] << " ";
        }
        log_wr << "\nBase\n";
        log_wr << s_all.s_base.x << " " << s_all.s_base.y << " " << s_all.s_base.health << " " <<
                  s_all.s_base.max_item << " " << s_all.s_base.now_item << "\n";
        log_wr << "Bonus\n" << s_all.s_bonus.size() << "\n";
        for (unsigned int i = 0; i < s_all.s_bonus.size(); i++) {
            log_wr << s_all.s_bonus[i].x << " " << s_all.s_bonus[i].y << " " <<
                      s_all.s_bonus[i].health << " " << s_all.s_bonus[i].attack << "\n";
        }
        log_wr << "Units\n" << s_all.s_unit.size() << "\n";
        for (unsigned int i = 0; i < s_all.s_unit.size(); i++) {
            log_wr << s_all.s_unit[i].x << " " << s_all.s_unit[i].y << " " <<
                      s_all.s_unit[i].name << " " << s_all.s_unit[i].health << " " <<
                      s_all.s_unit[i].nearAttack << " " << s_all.s_unit[i].furtherAttack << " " <<
                      s_all.s_unit[i].radius_attack << " " << s_all.s_unit[i].accuracy << " " <<
                      s_all.s_unit[i].attack_speed << "\n";
        }
    }

    ~Memento_write(){
        log_wr.close();
    }
};

class Memento_read{
    ifstream log_wr;
    string correct;
    int number;
public:
    Memento_read(){
        log_wr.open("memento.txt"); // открываем файл
    }

    S_all read_all(){
        S_all s_all;
        if (!(log_wr >> correct && correct == "Field")){
            throw logic_error("Error in read Field");
        }
        if (!(log_wr >> s_all.s_field.width >> s_all.s_field.height))
            throw logic_error("Error in read data field");
        if (!(log_wr >> correct && correct == "Land"))
            throw logic_error("Error in read Land");
        for(unsigned int i = 0; i < s_all.s_field.width*s_all.s_field.height; i++){
            log_wr >> correct;
            s_all.s_land.type.push_back(correct);
        }
        //cout << s_all.s_land.type[5];
        if (!(log_wr >> correct && correct == "Base"))
            throw logic_error("Error in read Base");
        if(!(log_wr >> s_all.s_base.x >> s_all.s_base.y >> s_all.s_base.health >>
             s_all.s_base.max_item >> s_all.s_base.now_item))
            throw logic_error("Error in read data base");
        //cout << s_all.s_base.max_item;
        if(!(log_wr >> correct && correct == "Bonus"))
            throw logic_error("Error in read Bonus");
        //cout << correct;
        if(!(log_wr >> number) || number < 0){
            throw logic_error("Error in read num or bon < 0");
        }
        //cout << number;
        else if (number > 0){
            for (unsigned int i = 0; i < number; i++){
                s_all.s_bonus.push_back(S_bonus());
                if(!(log_wr >> s_all.s_bonus[i].x >> s_all.s_bonus[i].y >>
                               s_all.s_bonus[i].health >> s_all.s_bonus[i].attack))
                    throw logic_error("Error in read data bonus");
            }
        }
        //cout << s_all.s_bonus[0].health;
        if(!(log_wr >> correct && correct == "Units"))
            throw logic_error("Error in read Units");
        //cout << correct;
        if(!(log_wr >> number) || number < 0){
            throw logic_error("Error in read un_num or un < 0");
        }
        else if (number > 0){
            for (unsigned int i = 0; i < number; i++){
                s_all.s_unit.push_back(S_unit());
                if(!(log_wr >> s_all.s_unit[i].x >> s_all.s_unit[i].y >>
                               s_all.s_unit[i].name >> s_all.s_unit[i].health >>
                               s_all.s_unit[i].nearAttack >> s_all.s_unit[i].furtherAttack >>
                               s_all.s_unit[i].radius_attack >> s_all.s_unit[i].accuracy >>
                               s_all.s_unit[i].attack_speed))
                    throw logic_error("Error in read data units");
            }
        }
        //cout << s_all.s_unit[0].name;

        return s_all;
    }

    ~Memento_read(){
        log_wr.close();
    }

};

class Memento{
public:
    Memento(struct S_all &s_all, int flag){
        if (flag == 1){
            Memento_write memento_write;
            memento_write.write_all(s_all);
        }
        else if (flag == 2){
            Memento_read memento_read;
            s_all = memento_read.read_all();
        }
    }
};
