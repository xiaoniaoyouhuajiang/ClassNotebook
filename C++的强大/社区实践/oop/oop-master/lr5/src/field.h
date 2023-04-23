#include "unit.h"
#include "landscape.h"
#include "nitralobject.h"
#include "base.h"
#include <fstream>
#include <cstdlib>
#ifndef FIELD_H
#define FIELD_H
#define COUNT_OF_UNITS_TYPE 6

struct Cell{
    Unit* unit = nullptr;
    Base* base = nullptr;
    NitralObject* nObject = nullptr;
    Landscape* landScape = nullptr;
};

/* Паттерн "Снимок" для сохранения/загрузки игры */

class Memento{
private:
    friend class Field;
    int rows;
    int columns;
    int countOfObjects;
    int maxNumOfObjects = rows*columns;
    Cell*** field;
    Unit*** units;
    ofstream* saveFile;
    ifstream* loadFile;
public:
    int snapFlag = 0;
    Memento(string saveFileName){
        saveFile = new ofstream;
        saveFile->open(saveFileName);
    }
    Memento(){
        loadFile = new ifstream;
        loadFile->open("load.txt");
    }
    void fileSave();
    void fileLoad();
    ~Memento(){
        if (saveFile->is_open()){
            saveFile->close();
            delete saveFile;
        }
        if (loadFile->is_open()){
            loadFile->close();
            delete loadFile;
        }
    }
};

/* Прокси для логирования действий пользователя */

class RealLog {
public:
    RealLog(){}
    void operator<< (string str){
        cout << "\n" << str << "\n";
    }
    void logFile(string str, ofstream* file){
        *file << "\n" << str;
    }
};

class TerminalLog{
    RealLog* proxy;
public:
    TerminalLog(){}
    void log(string str){
        proxy = new RealLog;
        proxy->operator<<(str);
    }
    ~TerminalLog(){
        delete proxy;
    }
};

class FileLog{
    ofstream* file;
    RealLog* proxy;
public:
    FileLog(string str){
        file = new ofstream;
        file->open(str);
    }
    void log(string str){
        proxy = new RealLog;
        proxy->logFile(str, file);
    }
    ~FileLog(){
        file->close();
        delete file;
        delete proxy;
    }
};



/* отдел поля */



class Field{
private:
 //   TerminalLog* termLog;
 //   FileLog* fileLog;
    int countOfDiffUnits = COUNT_OF_UNITS_TYPE;
    int rows;
    int columns;
    int countOfObjects;
    int maxNumOfObjects;
    Cell*** field;
    Unit*** units;                              // либо пофиксить эту матрицу и сделать её нормальным стеком, либо мараться с каждой функцией, ищущей юнита
public:
    Field(int M, int N, int maxNumOfObjects);
    Field(const Field& field);
    Field& operator= (const Field& field);
    Field(Field&& field);
    Field& operator=(Field&& field);
    int checkEmptySpace(int code);
    void setUnit1(Unit* unit);
    void deleteUnit1(Unit* unit);
    Unit* changeUnit1 (Unit* unit);
    void setUnit2(Unit* unit);
    void deleteUnit2(Unit* unit);
    Unit* changeUnit2(Unit* unit);
    void move(Unit* unit, int x, int y, TerminalLog* termLog, FileLog* fileLog, int logFlag);
    void createBase(int x, int y);
    void setUnitFromBase(ArmyFactory& factory, int x, int y, int code);
    Unit* getLastUnit(int code);
    int getBaseGold(int x, int y);
    int getBaseCountOfUnits(int x, int y);
   // void attack(Unit* unit1, Unit* unit2);
    void printField(Unit* unit);
    Memento* quickSave (Memento* snapShot);
    void quickLoad (Memento* snap);
    ~Field();
};

/* Паттерн команда */

class Command{
public:
    virtual void execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag) = 0;
protected:
    Command(Field* gameField) : gField(gameField){}
    Field* gField;
};

class MoveUpCommand: public Command{
public:
    MoveUpCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag);
};

class MoveDownCommand: public Command{
public:
    MoveDownCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag);
};

class MoveLeftCommand: public Command{
public:
    MoveLeftCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag);
};

class MoveRightCommand: public Command{
public:
    MoveRightCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag);
};

class AttackCommand: public Command{
public:
    AttackCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag);
};

#endif // FIELD_H
