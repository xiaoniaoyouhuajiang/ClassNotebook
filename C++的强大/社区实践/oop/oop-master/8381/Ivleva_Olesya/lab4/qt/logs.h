#include <string>
#include <iostream>
#include <fstream>

#include <mediator.h>


class Logs{
public:
    virtual string get_log() = 0;
    virtual void write(string logs) = 0;
    virtual ~Logs() = default;
};

class Logs_file : public Logs{
    string log;
    ofstream log_wr; // создаем объект класса оfstream (запись)

public:    
    friend ostream& operator << (ostream& os, Logs& log){
        os << "Game:   " << log.get_log();
        return os;
    }
    Logs_file(){
        log_wr.open("logs.txt"); // открываем файл
        //logs += "File for writing is open...\n";
    }

    string get_log(){
        return log;
    }

    void write(string logs){
        log = logs;
        log_wr << *this << "\n";
    }

    ~Logs_file(){
        log_wr << "Closing the program....................\n";
        log_wr.close();
    }
};

class Logs_Cons : public Logs{
    string log;
public:

    string get_log(){
        return log;
    }

    friend ostream& operator << (ostream& os, Logs& log);

    void write(string logs){
        log = logs;
        cout << *this << "\n";
    }
};


class Proxy_logs : public Logs{
protected:
    Logs *c_logs;

public:
    Proxy_logs(int flag){
        if (flag == 1){
            c_logs = new Logs_file;
        }
        else if (flag == 2){
            c_logs = new Logs_Cons;
        }
        else if (flag == 0) {
            c_logs = nullptr;
        }
    }

    ~Proxy_logs(){
        delete c_logs;
    }

    void write(string logs){
        if (c_logs != nullptr)
            c_logs->write(logs);
    }

    string get_log(){ //Last log
        return c_logs->get_log();
    }
};

class Adapter{
protected:
    int flag = 1;
    int form = 1;
    string logs;
    Logs *proxy_l;

public:
    Adapter(int flag) : flag(flag){
        proxy_l = new Proxy_logs(flag);
    }

    ~Adapter(){
        delete proxy_l;
    }

    void change_flag(int fl){
        if (flag != fl){
            flag = fl;
            delete proxy_l;
            proxy_l = new Proxy_logs(flag);
        }
    }

    void change_form(int fl){
        form = fl;
    }

    string add_unit(unsigned int x, unsigned int y, string type){
        if (form == 1){
            logs = "\nAdd " + type + ":" + "  x:" + to_string(x) + "   y: " + to_string(y) + "   base №1\n";
        }
        else if (form == 2) {
            logs = "\nAdd " + type + "\n";
        }
        proxy_l->write(logs);
        return logs;
    }

    string get_unit(unsigned int x, unsigned int y, int health, int n_attack, int f_attack, string type){
        if (form == 1){
            logs = "x: " + to_string(x) + "   y: " + to_string(y) + "\nHealth: " +
                    to_string(health) +  "\nNear attack: " + to_string(n_attack) +
                    "\nFurther attack: " + to_string(f_attack) + "\n";
        }
        else if (form == 2) {
            logs = "Add " + type + ":" + "  x: " + to_string(x) + "   y: " + to_string(y) + "\n";
        }
        proxy_l->write(logs);
        return logs;
    }

    string delete_unit(unsigned int x, unsigned int y, string type){
        if (form == 1){
            logs = "Delete " + type + ":" + "  x: " + to_string(x) + "   y: " + to_string(y) + "\n";
        }
        else if (form == 2) {
            logs = "Delete " + type + "\n";
        }
        proxy_l->write(logs);
        return logs;
    }

    string print(string log){
        proxy_l->write(log);
        return log;
    }

};

/*ostream &operator << (ostream &os, Logs &log){
    os << "Game:   " << log.get_log();
    return os;
}*/
