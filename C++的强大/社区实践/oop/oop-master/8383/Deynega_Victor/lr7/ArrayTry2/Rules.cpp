#include "Rules.h"
#include <conio.h>
#include "FieldBlock.h"
#include "mainwindow.h"
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QThread>

Rules::Rules() {
	key = 0;
	checker = nullptr;
	board = nullptr;
	attackBase = nullptr;
	proxyField = nullptr;
    actionType = 0;
}


Rule1::Rule1() {
	key = 0;
    actionType = 0;
    past = 0;
    current = 0;
	board = new GameField();
    exitFlag = false;
    checker = new TypeChecker();
	board = new GameField();
    attackBase = new Base(15); //defolt size = 15
    defBase = new DefBase(15);
    board->defBase = defBase;
    defBase->health = 2; ///////////////////////////////////////////////
    board->attackBase = attackBase;
	proxyField = new Proxy(board);
    visualisingFlag = 100;
	logger.switchLogStream("file");
	logger.turnOnOffLog("off");
    attackFlag = false;
    typeUnit1 = 0;
    typeUnit2 = 0;
}


int Rule1::whoLose() { //1 - attack lose; 2 - defence lose
    if (attackBase->numOfUnits >= 5) return 1;
    if(defBase->health <= 0 ) return 2;
    return 0;
}


int Rule1::action(int& turnCounter, int cell, MainWindow* window) { //1 - new game, chetniy hod - atac nechet - zawita
    window->label->setText("New turn");
    FieldBlock* fieldPtr = board->field;
    //if bad landscape
    if(fieldPtr[cell].landType->getType() == 2){
        window->label->setText("You picked: Lake. No actions with it!");
        //add border to show that button is pressed
        return 0;
    }
    if(fieldPtr[cell].landType->getType() == 1){
        window->label->setText("You picked: Mountain. No actions with it!");
        //add border to show that button is pressed
        return 0;
    }

    if(cell == 5){
        QString str = "You picked Attack Base. Num respawned units: ";
        str+=QString::number(this->attackBase->numOfUnits);
        window->label->setText(str);
        return 0;
    }

    if(cell == (14*15+9)){
        QString str = "You picked Defend Base.";
        //str+=QString::number(this->defBase->maxUnits-this->defBase->numOfUnits);
        str+=" Hp remain:" + QString::number(this->defBase->health);
        window->label->setText(str);
        return 0;
    }
    if(fieldPtr[cell].getUnitType() == 9 || fieldPtr[cell].getUnitType() == 10){ //wall
        if(turnCounter % 2 == 1){
            QString str = "Wall:)";
            str+=QString::number(fieldPtr[cell].unit->health);
            window->label->setText(str);
            return 0;
        }
        else{
            window->label->setText("It's not your's!");
            return 0;
        }
    }



    //if clear cell and landscape is plain
    if(fieldPtr[cell].getUnitType() == 0){
        openMenu(window, turnCounter); //spawn smth, close menu in handler
    }

    if(fieldPtr[cell].getUnitType() >= 1 && fieldPtr[cell].getUnitType() <= 8){
        if(turnCounter % 2 == 1){
            QString str = "You picked atack unit, It's not allowed!";
            window->label->setText(str);
            return 0;
        }
        QString str = "Hp: ";
        str+=QString::number(fieldPtr[cell].unit->health);
        str+=", Attack: ";
        str+=QString::number(fieldPtr[cell].unit->damage);
        window->label->setText(str);
        openActionMenu(window, fieldPtr[cell].getUnitType());
    }

    if(fieldPtr[cell].getUnitType() >= 9){
        if(turnCounter % 2 == 1){
            QString str = "Hp: ";
            str+=QString::number(fieldPtr[cell].unit->health);
            str+=", Attack: ";
            str+=QString::number(fieldPtr[cell].unit->damage);
            window->label->setText(str);
            openActionMenu(window, fieldPtr[cell].getUnitType());
        }
        else{
            QString str = "You picked defend unit, It's not allowed!";
            window->label->setText(str);
            return 0;
        }
    }

    if(whoLose() == 2){
        QString str = "GAME OVER, ATTACK HAS WON!";
        window->gameOver(str);
        showEndGameMenu(window);
    }
    if(whoLose() == 1){
        QString str = "GAME OVER, DEFENCE HAS WON!";
        window->gameOver(str);
        showEndGameMenu(window);
    }
    return 1;
}


void Rules::openMenu(MainWindow* window, int& turnCounter){
    for(int i = 0; i < 225; i++){
       window->buttons->at(i)->setEnabled(false); //make field non active
    }
    if(turnCounter % 2 == 0){ //show attack menu
        for(int i = 225; i < 232; i++){
            window->buttons->at(i)->show();
        }
        for(int i = 232; i < 238; i++){ //show def menu
            window->buttons->at(i)->hide();
        }
    }
    else{
        window->buttons->at(225)->show();
        for(int i = 226; i < 232; i++){
            window->buttons->at(i)->hide();
        }
        for(int i = 232; i < 238; i++){ //show def menu
            window->buttons->at(i)->show();
        }
    }
    window->buttons->at(225)->show();
    window->buttons->at(225)->setEnabled(true);
}


void Rules::openActionMenu(MainWindow *window, int type){
    for(int i = 0; i < 225; i++){
       window->buttons->at(i)->setEnabled(false); //make field non active
    }
    window->buttons->at(225)->show(); //end turn button
    window->buttons->at(239)->show(); //relocate button
    window->buttons->at(225)->setEnabled(true); //end turn button
    window->buttons->at(239)->setEnabled(true); //relocate button
    if(type == 5 || type == 6){ //if bomber
        return;
    }
    window->buttons->at(238)->show(); //atack
    window->buttons->at(238)->setEnabled(true);
    if(type == 8){
        window->buttons->at(240)->show();
        window->buttons->at(240)->setEnabled(true);
        return;
    }
    if(type == 12 || type == 11){
        window->buttons->at(241)->show();
        window->buttons->at(241)->setEnabled(true);
        return;
    }

    if(type == 13){
        window->buttons->at(242)->show();
        window->buttons->at(242)->setEnabled(true);
        return;
    }
    if(type == 14){
        window->buttons->at(243)->show();
        window->buttons->at(244)->show();
        window->buttons->at(243)->setEnabled(true);
        window->buttons->at(244)->setEnabled(true);
        return;
    }

}


void Rule1::unitAction(int cell, MainWindow* window, int& turnCounter){
    if(actionType == 1){ //buffer's buff
        dynamic_cast<Buffer*>(board->field[current].unit)->buff(cell%15, cell/15, *board);
        visualisingFlag = 0;
        turnCounter--;
        return;
    }
    if(actionType == 2){ //healers heal
        if(board->field[current].getUnitType() == 12){
            dynamic_cast<HealUnit*>(board->field[current].unit)->unitHeal(cell, *board);
            visualisingFlag = 0;
            turnCounter--;
            return;
        }
        else{
            if(cell == (14*15+9)){
                defBase->health += dynamic_cast<HealTower*>(board->field[current].unit)->heal;
                visualisingFlag = 0;
                turnCounter--;
                return;
            }
            if(cell == 5){
                attackBase->health += dynamic_cast<HealTower*>(board->field[current].unit)->heal;
                visualisingFlag = 0;
                turnCounter--;
                return;
            }
        }
    }
    if(actionType == 3){ //hook
        visualisingFlag = dynamic_cast<Pudge*>(board->field[current].unit)->hook(cell%15, cell/15, *board);
        turnCounter--;
        if(visualisingFlag != 0){
             typeUnit2 = board->field[current-15].getUnitType();
        }
        return;
    }
    if(actionType == 4){ //comander's buff
        dynamic_cast<Comander*>(board->field[current].unit)->increase(cell%15, cell/15, *board);
        visualisingFlag = 0;
        turnCounter--;
        return;
    }
    if(actionType == 5){ //comader's poision
        dynamic_cast<Comander*>(board->field[current].unit)->poising(cell%15, cell/15, *board);
        visualisingFlag = 0;
        turnCounter--;
        return;
    }
    if(attackFlag){
        visualisingFlag = board->field[current].unit->atack(current, cell, *board);
        if(visualisingFlag == 9){
            int dmg = board->field[current].unit->damage;
            defBase->health -= dmg;
            if(whoLose() == 2){
                QString str = "GAME OVER, ATTACK HAS WON!";
                window->gameOver(str);
                visualisingFlag = 0;
                showEndGameMenu(window);
                return;
               // QThread::msleep(1000);
            }
            if(whoLose() == 1){
                QString str = "GAME OVER, DEFENCE HAS WON!";
                window->gameOver(str);
                visualisingFlag = 0;
                showEndGameMenu(window);
                return;
               // QThread::msleep(5);
            }
            turnCounter--;
            return;
        }

        if(visualisingFlag == 5 || visualisingFlag == 6){
            past = current;
            current = cell;
            turnCounter--;
            return;
        }
    }
    else{
        visualisingFlag = board->field[current].unit->relocate(cell%15, cell/15, *board, 15);
        if(visualisingFlag == 2){
            turnCounter--;
            return;
        }
        if(visualisingFlag == 1){
            this->past = current;
            current = cell;
            this->typeUnit1 = board->field[cell].getUnitType();
            turnCounter--;
            return;
        }
        if(visualisingFlag == 10){
            this->typeUnit1 = board->field[current].getUnitType();
            defBase->health-=board->field[current].unit->damage;
            if(whoLose() == 2){
                QString str = "GAME OVER, ATTACK HAS WON!";
                window->gameOver(str);
                visualisingFlag = 0;
                showEndGameMenu(window);

                return;

            }
            turnCounter--;
            return;
        }
        if(visualisingFlag == 1){
            this->typeUnit1 = board->field[cell].getUnitType();
            past = current;
            current = cell;
            turnCounter--;
            return;
        }
    }
}


int Rules::getType(int cell){
    return board->field[cell].getUnitType();
}


void Rule1::setNumOfUnits(int turnCounter, bool flag){
    if(flag){
        if(turnCounter % 2 == 0){
            attackBase->numOfUnits++;
        }
     else{
            defBase->numOfUnits++;
        }
    }
    else{
        if(turnCounter % 2 == 0){
            attackBase->numOfUnits--;
        }
     else{
            defBase->numOfUnits--;
        }
    }
}


void Rule1::passiveMoves(){
    for (int i = 14; i >= 0; i--) {
        for (int j = 14; j >= 0; j--) {
            int curr = i * 15 + j;
            if ((board->field[curr].getUnitType() == 5) || (board->field[curr].getUnitType() == 6)) {
               visualisingFlag = board->field[curr].unit->relocate(j, i + 1, *board, 15);
               int cell = (i + 1) * 15 + j;
               this->typeUnit1 = board->field[cell].getUnitType();
               if(visualisingFlag != 2){
                   this->typeUnit1 = board->field[cell].getUnitType();
                   past = i*15 + j;
                   current = cell;
               }
            }
        }
    }
}


void Rule1::exitGame(){
    exit(0);
}

void Rule1::showEndGameMenu(MainWindow* window){
    window->newGame->show();
    window->exitGame->show();
}
