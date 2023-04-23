#include <iostream>
#include <string>
#include <vector>
#include "memento.h"
using namespace std;

template <class R>
class Player_state {
public:
    virtual ~Player_state() = default;
    virtual Player_state<R> *next_player(bool hard) = 0;
    virtual unsigned get_number() = 0;
};

template <class R>
class Player1_state : public Player_state<R> {
protected:
    R *rule;
public:
    Player1_state(R *rule) : rule(rule) {}
    virtual Player_state<R> *next_player(bool hard);
    virtual unsigned get_number() {return 1;}
};

template <class R>
class Player2_state : public Player_state<R> {
protected:
    R *rule;
public:
    Player2_state(R *rule) : rule(rule) {}
    virtual Player_state<R> *next_player(bool hard);
    virtual unsigned get_number() {return 2;}
};

template <class R>
class Player3_state : public Player_state<R> {
protected:
    R *rule;
public:
    Player3_state(R *rule) : rule(rule) {}
    virtual Player_state<R> *next_player(bool hard);
    virtual unsigned get_number() {return 3;}
};

class Easy_rule{
protected:
    Player_state<Easy_rule> *player;
    unsigned int players;
    unsigned int now_player;
    vector<string> type;
    unsigned int max_item;
    vector<unsigned int> now_item;
    bool maxed = false;
    unsigned int n;
    unsigned int m;

public:

    Easy_rule(unsigned int players) : players(players), now_player(1), max_item(3), n(5), m(5){
        player = new Player1_state<Easy_rule>(this);
        for (unsigned i=0; i<players; i++)
            now_item.push_back(0);
        for(unsigned int i = 0; i < n; i++){
            for(unsigned int j = 0; j < m; j++){
                if(j % 3 == 0){
                    type.push_back("R");
                }
                else if (j % 3 == 1) {
                    type.push_back("F");
                }
                else {
                    type.push_back("D");
                }
            }
        }
    }

    void update_now_item(vector<unsigned int> now_item){
        this->now_item = now_item;
    }

    void add_unit(){
        now_item[now_player-1]++;
    }

    void delete_unit(){
        now_item[now_player-1]--;
    }

    unsigned int get_width(){
        return n;
    }
    unsigned int get_height(){
        return m;
    }
    vector<string> get_type(){
        return type;
    }

    int check_win(unsigned int player){
        if (now_item[player-1] == 0)  //Проигрыш
            return 0;
        for (unsigned int i = 0; i < players; i++) {  //Никто не выиграл
            if(i != player-1 && now_item[i] != 0){
                return 1;
            }
        }
        return 2; //Выигрыш
    }

    unsigned int next_player(){
        do{
            player = player->next_player(players == 3);
        } while (check_win(player->get_number()) == 0 && maxed == true);
        return player->get_number();
    }

    unsigned int get_now_player(){
        return player->get_number();
    }
};

class Hard_rule{
protected:
    Player_state<Hard_rule> *player;
    unsigned int players;
    bool maxed = false;
    unsigned int now_player;
    vector<string> type;
    unsigned int max_item;
    vector<unsigned int> now_item;
    unsigned int n;
    unsigned int m;

public:
    Hard_rule(unsigned int players) : players(players), now_player(1), max_item(5), n(7), m(7){
        player = new Player1_state<Hard_rule>(this);
        for (unsigned int i=0; i<players; i++)
            now_item.push_back(0);
        for(unsigned int i = 0; i < n; i++){
            for(unsigned int j = 0; j < m; j++){
                if(j % 3 == 0){
                    type.push_back("R");
                }
                else if (j % 3 == 1) {
                    type.push_back("F");
                }
                else {
                    type.push_back("D");
                }
            }
        }
    }

    unsigned int get_width(){
        return n;
    }
    unsigned int get_height(){
        return m;
    }
    vector<string> get_type(){
        return type;
    }

    void add_unit(){
        now_item[now_player-1]++;
    }

    void delete_unit(){
        now_item[now_player-1]--;
    }

    void update_now_item(vector<unsigned int> now_item){
        this->now_item = now_item;
    }

    int check_win(unsigned int player){
        for (unsigned int i = 0; i < players; i++) {
            if(i != player-1 && now_item[i] != 0){
                return 0;
            }
            else if (i == player-1 && now_item[i] == 0){
                return 1;
            }
        }
        return 2;
    }

    unsigned int next_player(){
        do{
            player = player->next_player(players == 3);
        } while (check_win(player->get_number()) == 0 && maxed == true);
        return player->get_number();
    }

    unsigned int get_now_player(){
        return player->get_number();
    }
};



template <class R, int players>
class Game;


template <class R> //rule and number of players
class Game<R,2>{
protected:
    vector<Base*> base;
    Field *field;
    Adapter *adapter;
    string logs = "";
    R *rule;
    static Game<R,2> *singleton_;
    Game(vector<Base*> &base, Field *&field, Adapter *adapter, string &logs) : base(base), field(field){
        rule = new R(2);
        int n = rule->get_width();
        int m = rule->get_height();
        field = new Field(n, m, adapter);
        base.push_back(new Base(field, adapter));
        field->add_item(0, 0, base.back(), logs);
        base.push_back(new Base(field, adapter));
        field->add_item(n-1, m-1, base.back(), logs);
        vector<string> type = rule->get_type();
        for(int i = n-1; i >= 0; i--){
            for(int j = m-1; j >= 0; j--){
                Land* landsc = new Proxy(type.back());
                field->add_land(i, j, landsc);
                type.pop_back();
            }
        }
    }
public:
    static Game<R,2> *getInstance(vector<Base*> &base, Field *&field, Adapter *adapter, string &logs) {
        singleton_ = new Game<R,2>(base,field, adapter, logs);
        return singleton_;
    }
    int check_win(unsigned int player){
        return rule->check_win(player);
    }

    unsigned int next_player(){
        return rule->next_player();
    }

    unsigned int get_now_player(){
        return rule->get_now_player();
    }

    void add_unit(){
        rule->add_unit();
    }

    void delete_unit(){
        rule->delete_unit;
    }

    void update_now_item(vector<unsigned int> now_item){
        rule->update_now_item(now_item);
    }
};

template <class R>

Game<R,2>* Game<R,2>::singleton_= nullptr;



template <class R> //rule and number of players
class Game<R,3>{
protected:
    Field *field;
    vector<Base*> base;
    Adapter *adapter;
    string logs = "";
    R *rule;
    static Game<R,3> *singleton_;
    Game(vector<Base*> &base, Field *&field, Adapter *adapter, string &logs) : base(base), field(field){
        rule = new R(3);
        int n = rule->get_width();
        int m = rule->get_height();
        field = new Field(n, m, adapter);
        base.push_back(new Base(field, adapter));
        field->add_item(0, 0, base.back(), logs);
        base.push_back(new Base(field, adapter));
        field->add_item(n-1, m-1, base.back(), logs);
        base.push_back(new Base(field, adapter));
        field->add_item(0, m-1, base.back(), logs);
        vector<string> type = rule->get_type();
        for(int i = n-1; i >= 0; i--){
            for(int j = m-1; j >= 0; j--){
                Land* landsc = new Proxy(type.back());
                field->add_land(i, j, landsc);
                type.pop_back();
            }
        }
    }
public:
    static Game<R,3>* getInstance(vector<Base*> &base, Field *&field, Adapter *adapter, string &logs) {
        singleton_ = new Game<R,3>(base,field, adapter, logs);
        return singleton_;
    }

    int check_win(unsigned int player){
        return rule->check_win(player);
    }

    unsigned int next_player(){
        return rule->next_player();
    }

    unsigned int get_now_player(){
        return rule->get_now_player();
    }

    void add_unit(){
        rule->add_unit();
    }

    void delete_unit(){
        rule->delete_unit;
    }

    void update_now_item(vector<unsigned int> now_item){
        rule->update_now_item(now_item);
    }
};

template <class R>

Game<R,3>* Game<R,3>::singleton_= nullptr;
