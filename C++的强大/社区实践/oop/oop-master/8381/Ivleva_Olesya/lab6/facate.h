#include "ui_mainwindow.h"
#include "game.h"

#include <QMessageBox>

struct GameKeeper {
    int active;
    Game<Easy_rule, 2> *e2game;
    Game<Easy_rule, 3> *e3game;
    Game<Hard_rule, 2> *h2game;
    Game<Hard_rule, 3> *h3game;
    int check_win(unsigned int player){
        if (active == 1)
            return e2game->check_win(player);
        else if (active == 2)
            return e3game->check_win(player);
        else if (active == 3)
            return h2game->check_win(player);
        else if (active == 4)
            return h3game->check_win(player);
        throw logic_error(to_string(active));
    }

    unsigned int next_player(){
        if (active == 1)
            return e2game->next_player();
        else if (active == 2)
            return e3game->next_player();
        else if (active == 3)
            return h2game->next_player();
        else if (active == 4)
            return h3game->next_player();
        throw logic_error(to_string(active));
    }

    unsigned int get_now_player(){
        if (active == 1)
            return e2game->get_now_player();
        else if (active == 2)
            return e3game->get_now_player();
        else if (active == 3)
            return h2game->get_now_player();
        else if (active == 4)
            return h3game->get_now_player();
        throw logic_error(to_string(active));
    }

    void add_unit(){
        cout << "active check" << active << endl;
        if (active == 1)
            e2game->add_unit();
        else if (active == 2)
            e3game->add_unit();
        else if (active == 3)
            h2game->add_unit();
        else if (active == 4)
            h3game->add_unit();
        else
            throw logic_error(to_string(active));
    }

    void update_now_item(vector<unsigned int> now_item){

        if (active == 1)
            e2game->update_now_item(now_item);
        else if (active == 2)
            e3game->update_now_item(now_item);
        else if (active == 3)
            h2game->update_now_item(now_item);
        else if (active == 4)
            h3game->update_now_item(now_item);
        else
            throw logic_error(to_string(active));
    }
};

class Command {
public:
    virtual string exec(string&) = 0;
    virtual ~Command() = default;
};

class Command_Field_Neutrals : public Command{
protected:
    Field *field;
    unsigned int x1;
    unsigned int y1;
    string type;

public:
    Command_Field_Neutrals(Field *field, unsigned int x1, unsigned int y1, string type) :
        field(field), x1(x1), y1(y1), type(type){}

    string exec(string &logs){
        if(type == "B_ALL"){
            Item* bonus = new Bonus_all();
            if(field->add_item(x1, y1, bonus, logs))
                logs += "Add bonus all specifications...\n";
        }
        else if (type == "B_A") {
            Item* bonus = new Bonus_attack();
            if(field->add_item(x1, y1, bonus, logs))
                logs += "Add bonus attack...\n";
        }
        else if (type == "B_H") {
            Item* bonus = new Bonus_health();
            if(field->add_item(x1, y1, bonus, logs))
                logs += "Add bonus health...\n";
        }
    }
};

class Command_Field : public Command{
protected:
    Field *field;
    //Command_Field_Neutrals *comm_f_n;
    unsigned int x1;
    unsigned int y1;
    unsigned int x2;
    unsigned int y2;
    string type;

public:
    Command_Field(Field *field, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, string type) :
        field(field), x1(x1), y1(y1), x2(x2), y2(y2), type(type){
    }

    Command_Field(Field *field, unsigned int x1, unsigned int y1, string type) :
                  field(field), x1(x1), y1(y1), type(type){
    }

    string exec(string &logs){
        if (type == "m"){
            field->move_unit(x1, y1, x2, y2, logs);

        }
        else if (type == "d"){
            field->delete_unit(x1, y1, logs);
        }
        else if (type == "a") {
            logs += "Attack!!!\n";
            field->attack_unit(x1, y1, x2, y2, logs);
            field->get_unit(x2, y2, logs);
        }
        else if(type == "B_ALL" || type == "B_A" || type == "B_H"){
            Command_Field_Neutrals comm_f_n(field, x1, y1, type);
            //comm_f_n = new Command_Field_Neutrals(field, x1, y1, type);
            comm_f_n.exec(logs);
            //delete comm_f_n;
        }
        string print = "";
        field->print_unit(print);
        return print;
    }
};

class Command_Base : public Command{
protected:
    Field *field;
    Base* base;
    unsigned int x;
    unsigned int y;
    string type;

public:
    Command_Base(Field* field, Base* base, unsigned int x, unsigned int y, string type) :
        field(field), base(base), x(x), y(y), type(type){}

    string exec(string &logs){
        if (type == "D_G"){
            base->add_green_dr(x, y, logs);
        }
        else if (type == "D_R"){
            base->add_red_dr(x, y, logs);
        }
        else if (type == "W_R"){
            base->add_war_ronin(x, y, logs);
        }
        else if (type == "W_F"){
            base->add_war_fight(x, y, logs);
        }
        else if (type == "S_L"){
            base->add_sen_lion(x, y, logs);
        }
        else if (type == "S_F") {
            base->add_sen_fire(x, y, logs);
        }
        else if (type == "P_B") {
            logs += "\nOutput the base state:\n ";
            logs += base->get_comp()->getUnits_WhoAmI();
            logs += "\n";
            int health;
            health = base->getHealth();
            logs += "Health : ";
            logs += to_string(health);
            logs += "\n";
            return logs;
        }
        string print = "";
        field->print_unit(print);
        return print;
    }
};

class Facade {
protected:
    Ui::MainWindow *ui;
    Field *field;
    vector<Base *> base;
    Adapter *adapter;
    unsigned int n = 5;
    unsigned int m = 5;
    string logs = "";
    string print = "";
    int flag = 1;
    int form = 1;
    GameKeeper game;

public:
    Facade(Ui::MainWindow *ui, unsigned f_game) : ui(ui){
        adapter = new Adapter(flag);
        if (f_game == 1){
            Game<Easy_rule, 2> *new_game = Game<Easy_rule,2>::getInstance(base, this->field, adapter, logs);
            game.e2game = new_game;
            game.active = 1;
        }
        if (f_game == 2){
            Game<Easy_rule, 3> *new_game = Game<Easy_rule,3>::getInstance(base, this->field, adapter, logs);
            game.e3game = new_game;
            game.active = 2;
        }
        if (f_game == 3){
            Game<Hard_rule, 2> *new_game = Game<Hard_rule, 2>::getInstance(base, this->field, adapter, logs);
            game.h2game = new_game;
            game.active = 3;
        }
        if (f_game == 4){
            Game<Hard_rule, 3> *new_game = Game<Hard_rule, 3>::getInstance(base, this->field, adapter, logs);
            game.h3game = new_game;
            game.active = 4;
        }
        start_game();
    }

    ~Facade(){
        delete adapter;
        delete field;
    }

    void start_game(){
        //field = new Field(n, m, adapter);
        //base = new Base(field, adapter);  //!!!!!!!!
        //field->add_item(2, 2, base, logs);
        //fence = new Fence;
        //field->add_item(4, 3, fence, logs);
       /* for(unsigned int i = 0; i < n; i++){
            for(unsigned int j = 0; j < m; j++){
                if(j % 3 == 0){
                    Land* landsc = new Proxy("R");
                    field->add_land(i, j, landsc);
                }
                else if (j % 3 == 1) {
                    Land* landsc = new Proxy("F");
                    field->add_land(i, j, landsc);
                }
                else {
                    Land* landsc = new Proxy("D");
                    field->add_land(i, j, landsc);
                }
            }
        }
        */
        field->print_unit(print);
        ui->print_item->setText(QString::fromStdString(print));
        adapter->print("Start of game...\n");
    }

    void set_flag(int fl){
        if(fl == 1){
            adapter->print("Logging to file\n");
        }
        else if (fl == 2) {
            adapter->print("Logging to console\n");
        }
        if(flag != fl){
            flag = fl;
            adapter->change_flag(flag);
        }
    }

    void set_form(int fl){
        if(fl == 1){
            adapter->print("Long form\n");
        }
        else if (fl == 2) {
            adapter->print("Short form\n");
        }
        if(form != fl){
            form = fl;
            adapter->change_form(form);
        }
    }

    void add_green_dr(){
        unsigned player = game.get_now_player();
        adapter->print("The button for adding a green dragon is clicked\n");
        logs += to_string(player) + "\n";
        Command_Base comm_b(field, base[player-1], ui->set_x->value(), ui->set_y->value(), "D_G");
        game.add_unit();
        game.next_player();
        print = comm_b.exec(logs);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void add_red_dr(){
        unsigned player = game.get_now_player();
        adapter->print("The button for adding a red dragon is clicked\n");
        logs += to_string(player) + "\n";
        Command_Base comm_b(field, base[player-1], ui->set_x->value(), ui->set_y->value(), "D_R");
        game.add_unit();
        game.next_player();
        print = comm_b.exec(logs);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void add_war_fight(){
        unsigned player = game.get_now_player();
        adapter->print("The button for adding a warrior is clicked\n");
        logs += to_string(player) + "\n";
        Command_Base comm_b(field, base[player-1], ui->set_x->value(), ui->set_y->value(), "W_F");
        game.add_unit();
        game.next_player();
        print = comm_b.exec(logs);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void add_war_ronin(){
        unsigned player = game.get_now_player();
        adapter->print("The button for adding a ronin is clicked\n");
        logs += to_string(player) + "\n";
        Command_Base comm_b(field, base[player-1], ui->set_x->value(), ui->set_y->value(), "W_R");
        game.add_unit();
        game.next_player();
        print = comm_b.exec(logs);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void add_sen_fire(){
        unsigned player = game.get_now_player();
        adapter->print("The button for adding a sentry is clicked\n");
        logs += to_string(player) + "\n";
        Command_Base comm_b(field, base[player-1], ui->set_x->value(), ui->set_y->value(), "S_F");
        game.add_unit();
        game.next_player();
        print = comm_b.exec(logs);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void add_sen_lion(){
        unsigned player = game.get_now_player();
        adapter->print("The button for adding a lion is clicked\n");
        logs += to_string(player) + "\n";
        Command_Base comm_b(field, base[player-1], ui->set_x->value(), ui->set_y->value(), "S_L");
        game.add_unit();
        game.next_player();
        print = comm_b.exec(logs);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void bonus(){
        adapter->print("The button for adding bonus is clicked\n");
        if((ui->set_x->value()+ui->set_y->value())%3 == 0){
            Command_Field comm_f(field, ui->set_x->value(), ui->set_y->value(), "B_ALL");
            adapter->print("Add bonus all specifications\n");
            print = comm_f.exec(logs);
        }
        else if ((ui->set_x->value()+ui->set_y->value())%3 == 1){
            Command_Field comm_f(field, ui->set_x->value(), ui->set_y->value(), "B_A");
            adapter->print("Add bonus attack\n");
            print = comm_f.exec(logs);
        }
        else if ((ui->set_x->value()+ui->set_y->value())%3 == 2) {
            Command_Field comm_f(field, ui->set_x->value(), ui->set_y->value(), "B_H");
            adapter->print("Add bonus health\n");
            print = comm_f.exec(logs);
        }
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void delete_item(){
        adapter->print("The button for deleting unit is clicked\n");
        Command_Field comm_f(field, ui->set_x->value(), ui->set_y->value(), "d");
        print = comm_f.exec(logs);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }

    void move_unit(){
        unsigned player = game.get_now_player();
        adapter->print("The button for moving unit is clicked\n");
        Item *unit = field->who_am_I(ui->set_x->value(), ui->set_y->value());
        for (auto i : base[player-1]->get_units()){
            if (i == unit){
                Command_Field comm_f(field, ui->set_x->value(), ui->set_y->value(), ui->set_x1->value(), ui->set_y1->value(), "m");
                print = comm_f.exec(logs);
                game.next_player();
                ui->print_item->setText(QString::fromStdString(print));
                ui->print->setText(QString::fromStdString(logs));
                return;
            }
        }
        cout << "Wrong player" << endl;
        //ошибка : юнита нет у текущего игрока
    }

    void print_base(){
        adapter->print("The button for showing base is clicked\n");
        Command_Base comm_b(field, base.back(), ui->set_x->value(), ui->set_y->value(), "P_B");
        print = adapter->print(comm_b.exec(logs));
        ui->print->setText(QString::fromStdString(logs));
    }

    bool attack(){
        unsigned player = game.get_now_player();
        adapter->print("The button for attack is clicked\n");
        bool error = true;
        Item *attacker = field->who_am_I(ui->set_x->value(), ui->set_y->value());
        Item *attacked = field->who_am_I(ui->set_x1->value(), ui->set_y1->value());
        for (auto i : base[player-1]->get_units()){
            if (i == attacker)
                error = false;
            if (i == attacked)
                error = true;
        }
        if (error){
            logs += "Another player walks\n";
            ui->print->setText(QString::fromStdString(logs));
            // ошибка
            //cout << "Error while attacking" << endl;
            return false;
        }
        Command_Field comm_f(field, ui->set_x->value(), ui->set_y->value(), ui->set_x1->value(), ui->set_y1->value(), "a");
        print = comm_f.exec(logs);
        vector<unsigned> now_item;
        for (auto i : base){
            now_item.push_back(i->get_units().size());
        }
        game.update_now_item(now_item);
        if (game.check_win(player) == 2){
            ui->print_item->setText(QString::fromStdString(print));
            ui->print->setText(QString::fromStdString(logs));
            QMessageBox win_message;
            win_message.setText(QString::fromStdString("Player " + to_string(player) + " won!!!\nThe end of game!\n"));
            win_message.exec();
            return true;
        }
        game.next_player();
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
        return false;
    }

    void save(){
        unsigned int k = 0;
        S_all s_all;
        s_all.s_field.width = field->get_width();
        s_all.s_field.height = field->get_height();
        for (unsigned int i = 0; i < field->get_height(); i++)
            for(unsigned int j = 0; j < field->get_width(); j++)
                s_all.s_land.type.push_back(field->get_land(i, j));
        s_all.s_base.x = 2;
        s_all.s_base.y = 2;
        s_all.s_base.health = base.back()->getHealth();
        s_all.s_base.max_item = base.back()->get_max_item();
        s_all.s_base.now_item = base.back()->get_now_item();
        for (unsigned int i = 0; i < field->get_height(); i++){
            for(unsigned int j = 0; j < field->get_width(); j++){
                if (field->who_I(i, j) == "B"){
                    s_all.s_bonus.push_back(S_bonus());
                    s_all.s_bonus[k].x = i;
                    s_all.s_bonus[k].y = j;
                    s_all.s_bonus[k].health = field->get_info_bonus_unit(i, j, 1);
                    s_all.s_bonus[k].attack = field->get_info_bonus_unit(i, j, 2);
                    k++;
                }
            }
        }
        k = 0;
        for (unsigned int i = 0; i < field->get_height(); i++){
            for(unsigned int j = 0; j < field->get_width(); j++){
                if (field->who_I(i, j) != "B" && field->who_I(i, j) != "BAS" && field->who_I(i, j) != " "){
                    s_all.s_unit.push_back(S_unit());
                    s_all.s_unit[k].x = i;
                    s_all.s_unit[k].y = j;
                    s_all.s_unit[k].name = field->who_I(i, j);
                    s_all.s_unit[k].health = field->get_info_bonus_unit(i, j, 1);
                    s_all.s_unit[k].nearAttack = field->get_info_bonus_unit(i, j, 3);
                    s_all.s_unit[k].furtherAttack = field->get_info_bonus_unit(i, j, 4);
                    k++;
                }
            }
        }
        Memento memento(s_all, 1);
    }

    void read(){
        S_all s_all;
        string str = "";
        try {
            Memento memento(s_all, 2);
        } catch (logic_error err) {
            logs += err.what();
            logs += "\n";
            ui->print->setText(QString::fromStdString(logs));
            return;
        }
        delete field;
        logs += adapter->print("Load last save...\n");
        field = new Field(s_all.s_field.height, s_all.s_field.width, adapter);
        base.back() = new Base(field, adapter);
        field->add_item(s_all.s_base.x, s_all.s_base.y, base.back(), logs);
        for(unsigned int i = 0; i < s_all.s_field.height; i++){
            for(unsigned int j = 0; j < s_all.s_field.width; j++){
                Land* landsc = new Proxy(s_all.s_land.type[i*s_all.s_field.width+j]);
                field->add_land(i, j, landsc);
            }
        }
        for (unsigned int i = 0; i < s_all.s_bonus.size(); i++){
            if (s_all.s_bonus[i].attack != 0 && s_all.s_bonus[i].health != 0){
                Item* bonus = new Bonus_all();
                field->add_item(s_all.s_bonus[i].x, s_all.s_bonus[i].y, bonus, logs);
            }
            else if (s_all.s_bonus[i].attack != 0 && s_all.s_bonus[i].health == 0) {
                Item* bonus = new Bonus_attack();
                field->add_item(s_all.s_bonus[i].x, s_all.s_bonus[i].y, bonus, logs);
            }
            else {
                Item* bonus = new Bonus_health();
                field->add_item(s_all.s_bonus[i].x, s_all.s_bonus[i].y, bonus, logs);
            }
        }
        for (unsigned int i = 0; i < s_all.s_unit.size(); i++){
            Command_Base comm_b(field, base.back(), s_all.s_unit[i].x, s_all.s_unit[i].y, s_all.s_unit[i].name);
            print = comm_b.exec(str);
            field->set_characteristics(s_all.s_unit[i].x, s_all.s_unit[i].y, s_all.s_unit[i].health,
                                       s_all.s_unit[i].nearAttack, s_all.s_unit[i].furtherAttack);
        }
        field->print_unit(print);
        ui->print_item->setText(QString::fromStdString(print));
        ui->print->setText(QString::fromStdString(logs));
    }


};
