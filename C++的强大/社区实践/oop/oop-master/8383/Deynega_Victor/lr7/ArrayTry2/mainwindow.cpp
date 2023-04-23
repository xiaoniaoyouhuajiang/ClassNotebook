#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QPixmap>
#include <QLineEdit>
#include <QThread>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    game = new Game();
    ui->setupUi(this);
    buttons = new QList<QPushButton*>();
    QPixmap pixmap(":/textures_landscape/res/grass.png");
    QIcon ButtonIcon(pixmap);

    QPixmap pixmapMount(":/textures_landscape/res/peaks.png");
    QIcon ButtonIconMount(pixmapMount);

    QPixmap pixmapLake(":/textures_landscape/res/lake.png");
    QIcon ButtonIconLake(pixmapLake);

    QPixmap pixmapAttBase(":/textures_landscape/res/attackBase.png");
    QIcon ButtonIconAttBase(pixmapAttBase);

    QPixmap pixmapDefBase(":/textures_landscape/res/defBase.png");
    QIcon ButtonIconDefBase(pixmapDefBase);

    for(int i = 0 ; i < 15; i++){
        for(int j = 0; j < 15; j++){
             QPushButton* b = new QPushButton("", this);
            // b->setStyleSheet("QPushButton{background: transparent;}");
             b->setGeometry(QRect(QPoint((60*j)+450, (60*i)+90), QSize(59, 59)));
             b->setIcon(ButtonIcon);
             b->setIconSize(pixmap.rect().size());
             connect(b, SIGNAL (clicked()), this, SLOT (handleButton()));
             buttons->append(b);
        }
    }
    buttons->at(2*15+12)->setIcon(ButtonIconLake);
    buttons->at(2*15+12)->setIconSize(pixmapLake.rect().size());
    buttons->at(11*15+6)->setIcon(ButtonIconLake);
    buttons->at(11*15+6)->setIconSize(pixmapLake.rect().size());
    buttons->at(14*15+4)->setIcon(ButtonIconLake);
    buttons->at(14*15+4)->setIconSize(pixmapLake.rect().size());
    buttons->at(8*15+11)->setIcon(ButtonIconLake);
    buttons->at(8*15+11)->setIconSize(pixmapLake.rect().size());
    buttons->at(8*15+12)->setIcon(ButtonIconLake);
    buttons->at(8*15+12)->setIconSize(pixmapLake.rect().size());
    buttons->at(9*15+10)->setIcon(ButtonIconLake);
    buttons->at(9*15+10)->setIconSize(pixmapLake.rect().size());
    buttons->at(9*15+11)->setIcon(ButtonIconLake);
    buttons->at(9*15+11)->setIconSize(pixmapLake.rect().size());
    buttons->at(9*15+12)->setIcon(ButtonIconLake);
    buttons->at(9*15+12)->setIconSize(pixmapLake.rect().size());

    buttons->at(5*15+1)->setIcon(ButtonIconMount);
    buttons->at(5*15+1)->setIconSize(pixmapMount.rect().size());
    buttons->at(5*15+7)->setIcon(ButtonIconMount);
    buttons->at(5*15+7)->setIconSize(pixmapMount.rect().size());
    buttons->at(10*15+1)->setIcon(ButtonIconMount);
    buttons->at(10*15+1)->setIconSize(pixmapMount.rect().size());
    buttons->at(9*15+4)->setIcon(ButtonIconMount);
    buttons->at(9*15+4)->setIconSize(pixmapMount.rect().size());
    buttons->at(8*15+5)->setIcon(ButtonIconMount);
    buttons->at(8*15+5)->setIconSize(pixmapMount.rect().size());
    buttons->at(5*15+7)->setIcon(ButtonIconMount);
    buttons->at(5*15+7)->setIconSize(pixmapMount.rect().size());
    buttons->at(7*15+10)->setIcon(ButtonIconMount);
    buttons->at(7*15+10)->setIconSize(pixmapMount.rect().size());

    buttons->at(5)->setIcon(ButtonIconAttBase);
    buttons->at(5)->setIconSize(pixmapAttBase.rect().size());

    buttons->at(14*15+9)->setIcon(ButtonIconDefBase);
    buttons->at(14*15+9)->setIconSize(pixmapDefBase.rect().size());

    label = new QLabel("You picked:\n", this);
    label->setGeometry(QRect(QPoint(650, 10), QSize(500, 70)));
    makeMenu();
    makeActionMenu();


    newGame = new QPushButton("START NEW GAME", this);
    newGame->setGeometry(QRect(QPoint(800, 400), QSize(200, 190)));
    connect(newGame, SIGNAL (clicked()), this, SLOT (newGameHandle()));
    newGame->hide();

    exitGame = new QPushButton("EXIT GAME", this);
    exitGame->setGeometry(QRect(QPoint(800, 600), QSize(200, 200)));
    connect(exitGame, SIGNAL (clicked()), this, SLOT (exitGameHandle()));
    exitGame->hide();

    infoB = new QPushButton("ATTACK UNIT INFO", this);
    infoB->setGeometry(QRect(QPoint(1560, 800), QSize(120, 60)));
    connect(infoB, SIGNAL (clicked()), this, SLOT (infoHandler1()));

    infoB2 = new QPushButton("DEF UNIT INFO", this);
    infoB2->setGeometry(QRect(QPoint(140, 800), QSize(120, 60)));
    connect(infoB2, SIGNAL (clicked()), this, SLOT (infoHandler2()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::makeMenu() {
    QPushButton* endTurnButton = new QPushButton("End turn", this);
    endTurnButton->setGeometry(QRect(QPoint(1395, 90), QSize(120, 59))); //1395 60 , 1200 59
    connect(endTurnButton, SIGNAL(clicked()), this, SLOT(resMenuHandler()));
    endTurnButton->hide();
    buttons->append(endTurnButton);

    for(int i = 1; i < 7; i++){
        QPushButton* b = new QPushButton("", this);
        b->setGeometry(QRect(QPoint(1395, 125*i+90), QSize(125, 124)));
        connect(b, SIGNAL(clicked()), this, SLOT(resMenuHandler()));
        b->hide();
        buttons->append(b);
    }



    for(int i = 0; i < 6; i++){
        QPushButton* b = new QPushButton("", this);
        b->setGeometry(QRect(QPoint(285, 125*i+90), QSize(125, 124)));
        connect(b, SIGNAL(clicked()), this, SLOT(resMenuHandler()));
        b->hide();
        buttons->append(b);
    }

    buttons->at(226)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/archerRes.png")))));
    buttons->at(226)->setIconSize((*(new QPixmap(":/textures_landscape/res/archerRes.png"))).rect().size());

    buttons->at(227)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/ballistaRes.png")))));
    buttons->at(227)->setIconSize((*(new QPixmap(":/textures_landscape/res/ballistaRes.png"))).rect().size());

    buttons->at(228)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/bombRes.png")))));
    buttons->at(228)->setIconSize((*(new QPixmap(":/textures_landscape/res/bombRes.png"))).rect().size());

    buttons->at(229)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/genRes.png")))));
    buttons->at(229)->setIconSize((*(new QPixmap(":/textures_landscape/res/genRes.png"))).rect().size());

    buttons->at(230)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/assRes.png")))));
    buttons->at(230)->setIconSize((*(new QPixmap(":/textures_landscape/res/assRes.png"))).rect().size());

    buttons->at(231)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/bufferRes.png")))));
    buttons->at(231)->setIconSize((*(new QPixmap(":/textures_landscape/res/bufferRes.png"))).rect().size());



    buttons->at(232)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/wallRes.png")))));
    buttons->at(232)->setIconSize((*(new QPixmap(":/textures_landscape/res/wallRes.png"))).rect().size());

    buttons->at(233)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/immWallRes.png")))));
    buttons->at(233)->setIconSize((*(new QPixmap(":/textures_landscape/res/immWallRes.png"))).rect().size());

    buttons->at(234)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/healTowRes.png")))));
    buttons->at(234)->setIconSize((*(new QPixmap(":/textures_landscape/res/healTowRes.png"))).rect().size());

    buttons->at(235)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/healUnRes.png")))));
    buttons->at(235)->setIconSize((*(new QPixmap(":/textures_landscape/res/healUnRes.png"))).rect().size());

    buttons->at(236)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/pudgeRes.png")))));
    buttons->at(236)->setIconSize((*(new QPixmap(":/textures_landscape/res/pudgeRes.png"))).rect().size());

    buttons->at(237)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/comRes.png")))));
    buttons->at(237)->setIconSize((*(new QPixmap(":/textures_landscape/res/comRes.png"))).rect().size());
}

void MainWindow::makeActionMenu(){
    connect(buttons->at(225), SIGNAL(clicked()), this, SLOT(actionMenuHandler()));
    QPixmap pixmapAtack(":/textures_landscape/res/atack.png");
    QIcon ButtonIcon(pixmapAtack);
    QPixmap pixmapReloc(":/textures_landscape/res/move.png");
    QIcon ButtonIconReloc(pixmapReloc);

    for(int i = 0; i < 2; i++){ //interface 238 - attack and 239 - reloc button, 225 - end turn
        QPushButton* b = new QPushButton("", this);
        b->setGeometry(QRect(QPoint(150*i+75, 90), QSize(149, 149)));
        connect(b, SIGNAL(clicked()), this, SLOT(actionMenuHandler()));
        b->hide();
        buttons->append(b);
    }

    QPushButton* buff = new QPushButton("", this); //buffer's buff 240
    buff->setGeometry(QRect(QPoint(75, 90+150), QSize(149, 149)));
    connect(buff, SIGNAL(clicked()), this, SLOT(actionMenuHandler()));
    buff->hide();
    buttons->append(buff);

    QPushButton* heal = new QPushButton("", this); //healer's heal 241
    heal->setGeometry(QRect(QPoint(75, 90+150), QSize(149, 149)));
    connect(heal, SIGNAL(clicked()), this, SLOT(actionMenuHandler()));
    heal->hide();
    buttons->append(heal);


    QPushButton* pudge = new QPushButton("", this);//pudge's hook 242
    pudge->setGeometry(QRect(QPoint(75, 90+150), QSize(149, 149)));
    connect(pudge, SIGNAL(clicked()), this, SLOT(actionMenuHandler()));
    pudge->hide();
    buttons->append(pudge);

    for(int i = 0; i < 2; i++){//comander 243, 244
        QPushButton* b = new QPushButton("", this);
        b->setGeometry(QRect(QPoint(150*i+75, 240), QSize(149, 149)));
        connect(b, SIGNAL(clicked()), this, SLOT(actionMenuHandler()));
        b->hide();
        buttons->append(b);
    }

    buttons->at(238)->setIcon(ButtonIcon);
    buttons->at(238)->setIconSize(pixmapAtack.rect().size());

    buttons->at(239)->setIcon(ButtonIconReloc);
    buttons->at(239)->setIconSize(pixmapReloc.rect().size());

    buttons->at(240)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/buff.png")))));
    buttons->at(240)->setIconSize((*(new QPixmap(":/textures_landscape/res/buff.png"))).rect().size());

    buttons->at(241)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/heal.png")))));
    buttons->at(241)->setIconSize((*(new QPixmap(":/textures_landscape/res/heal.png"))).rect().size());

    buttons->at(242)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/hookv2.png")))));
    buttons->at(242)->setIconSize((*(new QPixmap(":/textures_landscape/res/hookv2.png"))).rect().size());

    buttons->at(243)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/buff.png")))));
    buttons->at(243)->setIconSize((*(new QPixmap(":/textures_landscape/res/buff.png"))).rect().size());

    buttons->at(244)->setIcon(*(new QIcon(*(new QPixmap(":/textures_landscape/res/poision.png")))));
    buttons->at(244)->setIconSize((*(new QPixmap(":/textures_landscape/res/poision.png"))).rect().size());
}


void MainWindow::handleButton(){
    game->rule->current = buttons->indexOf((QPushButton*)sender());
    game->rule->action(game->turnCounter, game->rule->current, this);
}

void MainWindow::resMenuHandler(){
    prepareResMenu();
}

void MainWindow::actionMenuHandler(){
    prepareActionMenu(game->turnCounter);
    return;
}

void MainWindow::targetHandler(){
    game->rule->unitAction(buttons->indexOf((QPushButton*)sender()), this, game->turnCounter);
    targetVisualising();
    targetReset();
}

void MainWindow::exitGameHandle(){
    game->rule->exitGame();
}

void MainWindow::infoHandler1(){
    QString str = "Archer:\n\tAttack: 1, type attack: diagonal, top down.\n\tHealth: 1.\n\tRelocate: anywhere.\n";
    str+="Ballista:\n\tAttack: 3, type attack: same as archer.\n\tHealth: 2.\n\tRelocate: 4 direction(up, down, left, right) by 1 cell.\n";
    str+="Bomber:\n\tAttack: 5, by relocation(damage when crush into unit.\n\tHealth: 2.\n\tRelocate: 8 direction by 1 cell.\n";
    str+="Big bomber:\n\tAttack: 8, same as bomber.\n\tHealth: 2.\n\tRelocate: back and further by 1 cell.\n";
    str+="Assasin:\n\tAttack: 2, any distance, relocate to victim cell if it dead.\n\tHealth: 1\n\tRelocate: anywhere.\n";
    str+="Buffer:\n\tAttack: 1, 8 direction by 1 cell distance.\n\tHealth: 3.\n\tRelocate: same as attack.\n\tBuff: +1 attack, +1 health to any unit";
    QMessageBox::about(this, "Unit infotmation", str);
}

void MainWindow::infoHandler2(){
    QString str = "Wall:\n\tHealth: 1, can't move and attack.\n";
    str+="Immortal wall:\n\tHealth: inf, can't move and attack.\n";
    str+= "Unit heal:\n\tAttack: 1, 8 direction by 1 cell.\n\tHealth: 2.\n\tRelocate: anywhere.\n\tHeal: 1(units only).\n";
    str+= "Tower heal:\n\tSame as unit heal, but healing only tower.\n";
    str+="Pudge:\n\tAttack: 1, 8 direction by 1 cell.\n\tRelocate: anywhere.\n\tHook: down up, by vertical line\n";
    str+="Comander:\n\tAttack: 2, 8 direction by 1 cell.\n\tRelocate: same as attack.\n\tIncrease: +2 dmg, same distance as attack.\n\tSecret ability: ;)";
    QMessageBox::about(this, "Unit infotmation", str);
}

void MainWindow::newGameHandle(){
    game->startNewGame();
    visualiseNewGame();
}


void MainWindow::setUnitImg(int type, int cell){
    switch (type) {
    case 1: {
        QPixmap pixmap(":/textures_landscape/res/archer.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 2: {
        QPixmap pixmap(":/textures_landscape/res/ballista.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 5: {
        QPixmap pixmap(":/textures_landscape/res/bomber.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 6: {
        QPixmap pixmap(":/textures_landscape/res/general.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 7: {
        QPixmap pixmap(":/textures_landscape/res/assasin.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 8: {
        QPixmap pixmap(":/textures_landscape/res/buffer.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 9: {
        QPixmap pixmap(":/textures_landscape/res/wall.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 10: {
        QPixmap pixmap(":/textures_landscape/res/immWall.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 11: {
        QPixmap pixmap(":/textures_landscape/res/healTower.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 12: {
        QPixmap pixmap(":/textures_landscape/res/healUnit.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 13: {
        QPixmap pixmap(":/textures_landscape/res/pudge.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    case 14: {
        QPixmap pixmap(":/textures_landscape/res/comander.png");
        QIcon button(pixmap);
        buttons->at(cell)->setIcon(button);
        buttons->at(cell)->setIconSize(pixmap.rect().size());
        return;
    }
    }
    return;
}

void MainWindow::offActionButtons(){
    buttons->at(225)->setEnabled(false);
    for(int i = 238 ; i < 245; i++){
        buttons->at(i)->setEnabled(false);
    }
}

void MainWindow::onActionButtons(){
    buttons->at(225)->setEnabled(true);
    for(int i = 238 ; i < 245; i++){
        buttons->at(i)->setEnabled(true);
    }
}

void MainWindow::targetVisualising(){
    QPixmap pixmap(":/textures_landscape/res/grass.png");
    QIcon ButtonIcon(pixmap);
    int res = game->rule->visualisingFlag;
    if(res == 1){
        buttons->at(game->rule->past)->setIcon(ButtonIcon);
        buttons->at(game->rule->past)->setIconSize(pixmap.rect().size());
        setUnitImg(game->rule->typeUnit1, buttons->indexOf((QPushButton*)sender()));
        return;
    }
    if(res == 2 || res == 10){
        buttons->at(game->rule->current)->setIcon(ButtonIcon);
        buttons->at(game->rule->current)->setIconSize(pixmap.rect().size());
        return;
    }
    if(res == 3){
        buttons->at(game->rule->past)->setIcon(ButtonIcon);
        buttons->at(game->rule->past)->setIconSize(pixmap.rect().size());
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIcon(ButtonIcon);
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIconSize(pixmap.rect().size());
        return;
    }
    if(res == 4){
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIcon(ButtonIcon);
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIconSize(pixmap.rect().size());
        return;
    }
    if(res == 5 || res == 6){
        QPixmap pixmapAss(":/textures_landscape/res/assasin.png");
        QIcon buttonAss(pixmapAss);
        buttons->at(game->rule->past)->setIcon(ButtonIcon);
        buttons->at(game->rule->past)->setIconSize(pixmap.rect().size());
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIcon(buttonAss);
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIconSize(pixmapAss.rect().size());
        return;
    }
    if(res == 7){
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIcon(ButtonIcon);
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIconSize(pixmap.rect().size());
        return;
    }
    if(res == 8){
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIcon(ButtonIcon);
        buttons->at(buttons->indexOf((QPushButton*)sender()))->setIconSize(pixmap.rect().size());
        setUnitImg(game->rule->typeUnit2, game->rule->current-15);
    }
}

void MainWindow::targetReset(){
    if(game->rule->whoLose() != 0) return;
    if(game->rule->visualisingFlag == 2){
        label->setText("END TURN!");
        //game->turnCounter--;
        endTurn();
        return;
    }
    for(int i = 238; i < 245; i++){
        if(!buttons->at(i)->isHidden()){
            buttons->at(i)->setEnabled(true);
        }
    }
    buttons->at(225)->setEnabled(true);
    for(int i = 0; i < 225; i++){
        buttons->at(i)->setEnabled(false);
        disconnect(buttons->at(i), SIGNAL (clicked()), this, SLOT (targetHandler()));
        connect(buttons->at(i), SIGNAL (clicked()), this, SLOT (handleButton()));
    }
}

void MainWindow::prepareActionMenu(int& turnCounter){
    if(buttons->indexOf((QPushButton*)sender()) == 225){
        label->setText("END TURN!");
        turnCounter--;
        endTurn();
        return;
    }
    offActionButtons();
    for(int i = 0 ; i < 225; i++){
        disconnect(buttons->at(i), SIGNAL (clicked()), this, SLOT (handleButton()));
        connect(buttons->at(i), SIGNAL (clicked()), this, SLOT (targetHandler()));
        buttons->at(i)->setEnabled(true);
    }
    if(buttons->indexOf((QPushButton*)sender()) == 240){ //buffer's buff
        buttons->at(240)->hide();
        game->rule->actionType = 1;
        return;
    }
    if(buttons->indexOf((QPushButton*)sender()) == 241){ //heal
        buttons->at(241)->hide();
        game->rule->actionType = 2;
        return;
    }
    if(buttons->indexOf((QPushButton*)sender()) == 242){ //hook
        buttons->at(242)->hide();
        game->rule->actionType = 3;
        return;
    }
    if(buttons->indexOf((QPushButton*)sender()) == 243){ //comander's buff
        buttons->at(243)->hide();
        game->rule->actionType = 4;
        return;
    }
    if(buttons->indexOf((QPushButton*)sender()) == 244){ //comander's po
        buttons->at(244)->hide();
        game->rule->actionType = 5;
        return;
    }
    if(buttons->indexOf((QPushButton*)sender()) == 239 || buttons->indexOf((QPushButton*)sender()) == 238){
        game->rule->actionType = 0;
        if(buttons->indexOf((QPushButton*)sender()) == 239){
            game->rule->attackFlag = false;
            buttons->at(239)->hide();
        }
        else{
            buttons->at(238)->hide();
            game->rule->attackFlag =  true;
        }
       // offActionButtons();
        return;
    }
}

void MainWindow::endTurn(){
    for(int i = 0; i < 225; i++){
        buttons->at(i)->setEnabled(true);
        disconnect(buttons->at(i), SIGNAL (clicked()), this, SLOT (targetHandler()));
        connect(buttons->at(i), SIGNAL (clicked()), this, SLOT (handleButton()));
    }
    buttons->at(225)->hide();
    for(int i = 238 ; i < 245; i++){
        buttons->at(i)->hide();
    }
}

void MainWindow::gameOver(QString str){ //ad new game button
    for(int i = 0; i< buttons->size(); i++){
        buttons->at(i)->hide();
    }
    label->setText(str);
}

void MainWindow::visualiseNewGame(){
    QPixmap pixmap(":/textures_landscape/res/grass.png");
    QIcon ButtonIcon(pixmap);
    QPixmap pixmapMount(":/textures_landscape/res/peaks.png");
    QIcon ButtonIconMount(pixmapMount);

    QPixmap pixmapLake(":/textures_landscape/res/lake.png");
    QIcon ButtonIconLake(pixmapLake);

    QPixmap pixmapAttBase(":/textures_landscape/res/attackBase.png");
    QIcon ButtonIconAttBase(pixmapAttBase);

    QPixmap pixmapDefBase(":/textures_landscape/res/defBase.png");
    QIcon ButtonIconDefBase(pixmapDefBase);
    this->newGame->hide();
    this->exitGame->hide();

    for(int i = 0 ; i< 225; i++){
        buttons->at(i)->setIcon(ButtonIcon);
        disconnect(buttons->at(i), SIGNAL (clicked()), this, SLOT (targetHandler()));
        connect(buttons->at(i), SIGNAL (clicked()), this, SLOT (handleButton()));
    }
    buttons->at(2*15+12)->setIcon(ButtonIconLake);
    buttons->at(2*15+12)->setIconSize(pixmapLake.rect().size());
    buttons->at(11*15+6)->setIcon(ButtonIconLake);
    buttons->at(11*15+6)->setIconSize(pixmapLake.rect().size());
    buttons->at(14*15+4)->setIcon(ButtonIconLake);
    buttons->at(14*15+4)->setIconSize(pixmapLake.rect().size());
    buttons->at(8*15+11)->setIcon(ButtonIconLake);
    buttons->at(8*15+11)->setIconSize(pixmapLake.rect().size());
    buttons->at(8*15+12)->setIcon(ButtonIconLake);
    buttons->at(8*15+12)->setIconSize(pixmapLake.rect().size());
    buttons->at(9*15+10)->setIcon(ButtonIconLake);
    buttons->at(9*15+10)->setIconSize(pixmapLake.rect().size());
    buttons->at(9*15+11)->setIcon(ButtonIconLake);
    buttons->at(9*15+11)->setIconSize(pixmapLake.rect().size());
    buttons->at(9*15+12)->setIcon(ButtonIconLake);
    buttons->at(9*15+12)->setIconSize(pixmapLake.rect().size());

    buttons->at(5*15+1)->setIcon(ButtonIconMount);
    buttons->at(5*15+1)->setIconSize(pixmapMount.rect().size());
    buttons->at(5*15+7)->setIcon(ButtonIconMount);
    buttons->at(5*15+7)->setIconSize(pixmapMount.rect().size());
    buttons->at(10*15+1)->setIcon(ButtonIconMount);
    buttons->at(10*15+1)->setIconSize(pixmapMount.rect().size());
    buttons->at(9*15+4)->setIcon(ButtonIconMount);
    buttons->at(9*15+4)->setIconSize(pixmapMount.rect().size());
    buttons->at(8*15+5)->setIcon(ButtonIconMount);
    buttons->at(8*15+5)->setIconSize(pixmapMount.rect().size());
    buttons->at(5*15+7)->setIcon(ButtonIconMount);
    buttons->at(5*15+7)->setIconSize(pixmapMount.rect().size());
    buttons->at(7*15+10)->setIcon(ButtonIconMount);
    buttons->at(7*15+10)->setIconSize(pixmapMount.rect().size());

    buttons->at(5)->setIcon(ButtonIconAttBase);
    buttons->at(5)->setIconSize(pixmapAttBase.rect().size());

    buttons->at(14*15+9)->setIcon(ButtonIconDefBase);
    buttons->at(14*15+9)->setIconSize(pixmapDefBase.rect().size());
    for(int i = 0; i < 225; i++){
        buttons->at(i)->show();
        buttons->at(i)->setEnabled(true);
    }
    for(int i = 225; i < buttons->size(); i++ ){
        buttons->at(i)->hide();
    }
}

void MainWindow::prepareResMenu(){
    for(int i = 225; i< 238; i++){
        buttons->at(i)->hide();
    }
    for(int i = 0; i < 225; i++){
        buttons->at(i)->setEnabled(true);
    }

    int number = buttons->indexOf((QPushButton*)sender());
    int unitType = 0;
    game->rule->exitFlag = true;
    if(number == 225){
        //game->turnCounter--; //????
        endTurn();
        return;
    }
    if(number == 226){
        unitType = 1;
    }
    else{
        if(number == 227){
            unitType = 2;
        }
        else{
            unitType = number - 223;
        }
    }
   if(game->rule->checker->spawnSmth(unitType, *(game->rule->board), game->rule->current)){
       setUnitImg(unitType, game->rule->current);
       game->rule->setNumOfUnits(game->turnCounter, true);
       game->turnCounter--;
       if(game->rule->whoLose() == 1){
           QString str = "GAME OVER, DEFENCE HAS WON!";
           gameOver(str);
           game->rule->showEndGameMenu(this);
       }
   }
}

