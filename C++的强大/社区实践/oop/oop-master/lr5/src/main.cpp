#include <QCoreApplication>
#include <QMediaPlayer>
#include <QDir>
#include <QUrl>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include "field.h"

using namespace std;

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int rows, columns;
    cout << "Set the field size(rows and columns across the space): " << endl;
    cin >> rows;
    cin >> columns;
    Field gameField(rows, columns, rows*columns);
    Unit* unit = nullptr;
    gameField.createBase(0, rows/2);
    gameField.createBase(columns-1, rows/2);
    int keyGet;
    vector<Command*> commands;
    Command* command;

    /* музло */

    /*

    QMediaPlayer *chelhok;
    chelhok =new QMediaPlayer;
    const QString putii = "D:/proga/C++/OOP/OOP/battle.mp3";
  //  const QString putii = "D:/proga/C++/OOP/OOP/peace.mp3";
  //  const QString putii = "D:/proga/C++/OOP/OOP/ww1.mp3";
    QUrl adresok(QFileInfo(putii).absoluteFilePath());
    chelhok->setMedia(adresok);
    chelhok->setVolume(50);
    chelhok->play();

    */

    TerminalLog termLog;
    FileLog fileLog("log.txt");
    int logFlag = 0;
    string saveFile = "save.txt";
    string loadFile = "load.txt";
    Memento* snap = nullptr;
    do{
        system("cls");
        cout << "Change type of logging - '+'(no logging, logging in terminal, logging in file\n";
        cout << "To save the game use 's', to load use 'd'\n";
        cout << "   Player 1 keys:\n";
        cout << "Create unit - 'u'\n";
        cout << "Delete unit - 'f'\n";
        cout << "Change current unit - 'TAB'\n";
        cout << "Base info - 'm'\n\n";
        cout << "   Player 2 keys:\n";
        cout << "Create unit - 'n'\n";
        cout << "Delete unit - ']'\n";
        cout << "Change current unit - '-'\n";
        cout << "Base info - 'l'\n\n";
        cout << "Use arrows to move units, 'q' to quit\n\n";
        if (unit)
            gameField.printField(unit);
        keyGet = getch();
        if (keyGet == 's'){
            cout << "Would you like to create quick save or write your save in file(1 - quick, 2 - file): ";
            int fl = 0;
            cin >> fl;
            if (fl == 1){
                snap = new Memento(saveFile);
                snap = gameField.quickSave(snap);
            }
            if (fl == 2){
                cout << "Write file that you want to use to save: ";
                cin >> saveFile;
                snap = new Memento(saveFile);
                snap = gameField.quickSave(snap);
                snap->fileSave();
            }
        }
        if (keyGet == 'd'){
            cout << "Choose the way to load(1 - from quicksave, 2 - from file): ";
            int fl2 = 0;
            cin >> fl2;
            if (fl2 == 1){
                gameField.quickLoad(snap);
                unit = new Unit;
                unit = gameField.changeUnit1(unit);
             //   delete snap;
            }
            if (fl2 == 2){
                Memento* snap2 = new Memento();
                snap2->fileLoad();
                gameField.quickLoad(snap2);
                unit = new Unit;
                unit = gameField.changeUnit1(unit);
            }
        }
        if (keyGet == '+'){
            logFlag++;
            if (logFlag == 1){
                cout << "\nNow its a logging in terminal!\n";
            }
            if (logFlag == 2){
                cout << "\nNow its a logging in file!\n";
            }
            if (logFlag > 2){
                cout << "\nNow its no logging\n";
                logFlag = 0;
            }
        }
        if (keyGet == 'u'){
            cout << "choose the type of unit (from 0 to 5):" << endl;
            int code;
            cin >> code;
            if(code < 0 || code > 5){
                cout << "Wrong, moron. Can you read at least, are you? I said FROM 0 TO 5. Try again:" << endl;
                cin >> code;
            }
            if(code < 0 || code > 5){
                cout << "Okey, I just give up, you are so stupid donkey, that it actually look like harassment from my side.\n I'll write instead of you, don't please me\n" << endl;
                code = 4;
            }
            Player1Factory factory;
            gameField.setUnitFromBase(factory, 0, rows/2, code);
            if (logFlag == 1){
                termLog.log("Unit of Player1 was created");
            }
            if (logFlag == 2){
                fileLog.log("Unit of Player1 was created");
            }
            if(gameField.getLastUnit(code)){
                unit = gameField.getLastUnit(code);
                continue;
            }
            else {
                continue;
            }
        }
        if (keyGet == 'n'){
            cout << "choose the type of unit (from 0 to 5):" << endl;
            int code;
            cin >> code;
            if(code < 0 || code > 5){
                cout << "Wrong, moron. Can you read at least, are you? I said FROM 0 TO 5. Try again:" << endl;
                cin >> code;
            }
            if(code < 0 || code > 5){
                cout << "Okey, I just give up, you are so stupid donkey, that it actually look like harassment from my side.\n I'll write instead of you, don't please me\n" << endl;
                code = 11;
            }
            code += 6;
            Player2Factory factory;
            gameField.setUnitFromBase(factory, columns-1, rows/2, code);
            if (logFlag == 1){
                termLog.log("Unit of Player2 was created");
            }
            if (logFlag == 2){
                fileLog.log("Unit of Player2 was created");
            }
            if(gameField.getLastUnit(code)){
                unit = gameField.getLastUnit(code);
                continue;
            }
            else {
                continue;
            }
        }
        if (keyGet == 'm'){
            cout << "\nPlayer 1 base gold: " << gameField.getBaseGold(0, rows/2) << " | Count of units: " << gameField.getBaseCountOfUnits(0, rows/2);
            if (logFlag == 1){
                termLog.log("Check info of Player1 base");
            }
            if (logFlag == 2){
                fileLog.log("Check info of Player1 base");
            }
            keyGet = getch();
        }
        if (keyGet == 9){
            unit = gameField.changeUnit1(unit);
            if (logFlag == 1){
                termLog.log("Change Player1 current unit");
            }
            if (logFlag == 2){
                fileLog.log("Change Player1 current unit");
            }
        }
        if (keyGet == 'f'){
            Unit* unit2;
            unit2 = unit;
            unit = gameField.changeUnit1(unit2);
            gameField.deleteUnit1(unit2);
            if (logFlag == 1){
                termLog.log("Deleting Player1 unit");
            }
            if (logFlag == 2){
                fileLog.log("Deleting Player1 unit");
            }
        }
        if (keyGet == 'l'){
            cout << "\nPlayer 2 base gold: " << gameField.getBaseGold(columns-1, rows/2) << " | Count of units: " << gameField.getBaseCountOfUnits(columns-1, rows/2);
            if (logFlag == 1){
                termLog.log("Check info of Player2 base");
            }
            if (logFlag == 2){
                fileLog.log("Check info of Player2 base");
            }
            keyGet = getch();
        }
        if (keyGet == '-'){
            unit = gameField.changeUnit2(unit);
            if (logFlag == 1){
                termLog.log("Change Player2 current unit");
            }
            if (logFlag == 2){
                fileLog.log("Change Player2 current unit");
            }
        }
        if (keyGet == ']'){
            Unit* unit3;
            unit3 = unit;
            unit = gameField.changeUnit2(unit3);
            gameField.deleteUnit2(unit3);
            if (logFlag == 1){
                termLog.log("Deleting Player2 unit");
            }
            if (logFlag == 2){
                fileLog.log("Deleting Player2 unit");
            }
        }
        if (keyGet == 224){
            keyGet = getch();
            switch(keyGet){
            case UP_ARROW:
                command = new MoveUpCommand(&gameField);
                command->execute(unit, &termLog, &fileLog, logFlag);
                if (logFlag == 1){
                    termLog.log("Current unit goes up");
                }
                if (logFlag == 2){
                    fileLog.log("Current unit goes up");
                }
               // gameField.move(unit, unit->x, unit->y-1);
                break;
            case DOWN_ARROW:
                command = new MoveDownCommand(&gameField);
                command->execute(unit, &termLog, &fileLog, logFlag);
                if (logFlag == 1){
                    termLog.log("Current unit goes down");
                }
                if (logFlag == 2){
                    fileLog.log("Current unit goes down");
                }
               // gameField.move(unit, unit->x, unit->y+1);
                break;
            case LEFT_ARROW:
                command = new MoveLeftCommand(&gameField);
                command->execute(unit, &termLog, &fileLog, logFlag);
                if (logFlag == 1){
                    termLog.log("Current unit goes left");
                }
                if (logFlag == 2){
                    fileLog.log("Current unit goes left");
                }
              //  gameField.move(unit, unit->x-1, unit->y);
                break;
            case RIGHT_ARROW:
                command = new MoveRightCommand(&gameField);
                command->execute(unit, &termLog, &fileLog, logFlag);
                if (logFlag == 1){
                    termLog.log("Current unit goes right");
                }
                if (logFlag == 2){
                    fileLog.log("Current unit goes right");
                }
              //  gameField.move(unit, unit->x+1, unit->y);
                break;
            default:
                break;
            }
        }

    }while (keyGet != 'q');
   // delete chelhok;
   // delete snap;
    cout << "\nGame Over!";
    return a.exec();
}
