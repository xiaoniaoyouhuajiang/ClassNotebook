//
// Created by max on 25.03.20.
//

#include "Game.h"
#include "Proxy.h"

void Game::runGame() {
    int x_field,y_field, max_number_of_objects,x,y;
    string filename;
    BaseAction base_action;
    TerminalLog terminal_log;
    FileLog file_log("game_report.txt");
    UnitAction unit_action;
    Proxy proxy;
    cout << "Начало игры\n";
    while (1) {
        cout << "Введите размеры поля:";
        cin >> x_field >> y_field;
        if(x_field >= 5 && y_field >= 5)
            break;
        else
            cout << "Каждая компонента поля должна быть >= 5\n";
    }
    cout << "Введите максимальное количество объектов на поле\n";
    cin >> max_number_of_objects;
    Field f(max_number_of_objects,x_field,y_field);
    proxy.changeLogType(&f,&terminal_log,&file_log);
    f.printField();
    f.getLog()->write("Создали поле\n");
    base_action.setBase(&f);
    f.printField();
    int player_move;
    bool check = false;
    while (1){
        cout << "Сделвйте ход: \n";
        cout << "-1 - завершить игру\n";
        cout << "0 - пропустить ход\n";
        cout << "1 - Выбрать юнита\n";
        cout << "2 - Выбрать базу\n";
        cout << "3 - поменять логирование\n";
        cin >> player_move;
        if(player_move == -1) {
            f.getLog()->write("ИГРА ОКОНЧЕНА\n");
            break;
        }
        switch (player_move){//ход игрока
            case 0:
                check = true;
                break;
            case 1://выбрать юнита
                f.getLog()->write("Опция выбрать юнита\n");
                unit_action.run(check,&f);
                break;
            case 2:
                f.getLog()->write("Опция выбрать базу\n");
                base_action.run(&f,check);
                break;
            case 3:
                f.getLog()->write("Опция поменять лог\n");
                proxy.changeLogType(&f,&terminal_log,&file_log);
                break;
        }
        if(check){
            f.printField();
            f.getLog()->write("Ход закончен\n");
        }
        check = false;
    }
}