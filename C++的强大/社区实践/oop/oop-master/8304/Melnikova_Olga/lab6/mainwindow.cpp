#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memory"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_table(Field& field){

    for(int i = 0; i<ui->table->rowCount();i++){
        for(int j = 0; j<ui->table->columnCount();j++){
            if((field.cells(j + 1, i + 1).innerObject)){
                        QImage *img = new QImage();
                        std::string str= field.cells(j + 1, i + 1).innerObject->symb;
                        QString qText = QString(str.c_str());
                        if (img->load(qText))                //удалился game (если передать по ссылке field), таблицу рисует правильно
                        {
                            QTableWidgetItem *item = new QTableWidgetItem();
                            item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(70,70));
                            ui->table->setItem(i, j, item);
                        }
            }else{
                std::string str= field.cells(j + 1, i + 1).landscape->symb;  //сегфолт если не по ссылке
                QImage *img = new QImage();
                QString qText = QString(str.c_str());
                if (img->load(qText))
                {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    //item->setBackgroundColor(Qt::red);
                    item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(70,70));
                    ui->table->setItem(i, j, item);
                }
            }
        }
    }
}

void MainWindow::show_table(){
    this->ui->table->setRowCount(game->field->H);
    this->ui->table->setColumnCount(game->field->W);
    for(int i = 0; i<ui->table->rowCount();i++){
        for(int j = 0; j<ui->table->columnCount();j++){
            if((game->field->cells(j + 1, i + 1).innerObject)){
                        QImage *img = new QImage();
                        std::string str= game->field->cells(j + 1, i + 1).innerObject->symb;
                        QString qText = QString(str.c_str());
                        if (img->load(qText))                //удалился game (если передать по ссылке field), таблицу рисует правильно
                        {
                            QTableWidgetItem *item = new QTableWidgetItem();
                            item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(70,70));
                            ui->table->setItem(i, j, item);
                        }
            }else{
                std::string str= game->field->cells(j + 1, i + 1).landscape->symb;  //сегфолт если не по ссылке
                QImage *img = new QImage();
                QString qText = QString(str.c_str());
                if (img->load(qText))
                {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    //item->setBackgroundColor(Qt::red);
                    item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(70,70));
                    ui->table->setItem(i, j, item);
                }
            }
        }
    }
}

void MainWindow::del_table(){
    for(int i = 0; i<ui->table->rowCount();i++){
        for(int j = 0; j<ui->table->columnCount();j++){
            QTableWidgetItem *item = new QTableWidgetItem();
            ui->table->setItem(i, j, item);
        }
    }
}

void MainWindow::on_actionCreate_new_triggered()
{
    window = new CreateGameWindow(this);
    connect(window, &CreateGameWindow::window, this, &MainWindow::show);
    window->setModal(true);
    window->show();
}

void MainWindow::slotSetTableHW(int h, int w, bool logToFile, bool logToTerminal, bool withoutLog)
{
    this->ui->table->setRowCount(h);
    this->ui->table->setColumnCount(w);
    this->ui->table->horizontalHeader()->setDefaultSectionSize(70);
    this->ui->table->verticalHeader()->setDefaultSectionSize(70);
    this->logToFile = logToFile;
    this->logToTerminal = logToTerminal;
    this->withoutLog = withoutLog;
    if(logToFile){
        std::ofstream out;
        out.open("./log.txt", std::ios_base::trunc);
        out.close();
    }
    QList<QTableWidgetItem*> pTableItem;
    for(int i = 0; i < h*w; i++)
    {
        QTableWidgetItem* pTableNewItem = new QTableWidgetItem(QTableWidgetItem::Type);
        pTableNewItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        pTableItem << pTableNewItem;
        ui->table->setItem(0, i, pTableItem[i]);
    }
    process(h,w);
}

void MainWindow::process(int h,int w){
    Rule2* rule = new Rule2();
    Game<Rules> game(h,w, *rule);
    *this->game = game;
    ui->H1_archer->setNum(this->game->base1->units.front()->health);   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ui->H2_archer->setNum(this->game->base2->units.front()->health);
    show_table(*game.field);

    connect(ui->table, SIGNAL(cellClicked(int, int)), SLOT(Cliked(int, int)));
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::Cliked(int h, int w){
    //фасад

    if(game->base1->health == 0){
        del_table();
        QMessageBox::information(0, "Внимание", "Конец игры");
        return;
    }else if(game->base2->health == 0){
        del_table();
        QMessageBox::information(0, "Внимание", "Конец игры");
        return;
    }
    if(game->win){
        if((h == game->winH) && (w == game->winW)){
            del_table();
            QMessageBox::information(0, "Внимание", "Конец игры");
            return;
        }
    }
    this->game->isActionDone = false;
    this->game->isAttackDone = 0;
    Facade* facade = new Facade(this->game, h, w, &isUnitSelected, &selectedUnit, &game->currNumBase);
    facade->func(logToFile, logToTerminal, withoutLog);
    show_table();
    if(game->isActionDone){
        if(game->currNumBase || game->isAttackDone==1){
            for (Unit* n : this->game->base1->units){ // не все созданны
                if(n->isArcher){
                    if(n->health == 0){
                        ui->H1_archer->setText("");
                        ui->B1_archer->setText("");
                    }else{
                        if(game->isAttackDone==1){
                            if(n->shieldUsed){
                                ui->B1_archer->setText(ui->B1_archer->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }else{
                            ui->H1_archer->setNum(n->health);

                            if(n->shieldEnabled){
                                 if(!(ui->B1_archer->text().contains("Щит", Qt::CaseInsensitive))){
                                    ui->B1_archer->setText(ui->B1_archer->text()+" Щит");
                                }
                            }
                            if(n->MoveRadiusBetter){
                                QString s = QString::number(n->MoveRadiusBetter);
                                ui->B1_archer->setText(ui->B1_archer->text()+" Р+"+s);
                                n->MoveRadiusBetter = false;
                            }
                            if(n->AttackRadiusBetter){
                                QString s = QString::number(n->AttackRadiusBetter);
                                ui->B1_archer->setText(ui->B1_archer->text()+" A+"+s);
                                n->MoveRadiusBetter = false;
                            }
                        }
                    }
                }else if(n->isCrossBowMan){
                    if(n->health == 0){
                        ui->H1_crossBow->setText("");
                        ui->B1_crossBow->setText("");
                    }else{
                        if(game->isAttackDone==1){
                            if(n->shieldUsed){
                                ui->B1_crossBow->setText(ui->B1_crossBow->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }else{
                            ui->H1_crossBow->setNum(n->health);

                            if(n->shieldEnabled){
                                 if(!(ui->B1_crossBow->text().contains("Щит", Qt::CaseInsensitive))){
                                    ui->B1_crossBow->setText(ui->B1_crossBow->text()+" Щит");
                                }
                            }
                            if(n->MoveRadiusBetter){
                                QString s = QString::number(n->MoveRadiusBetter);
                                ui->B1_crossBow->setText(ui->B1_crossBow->text()+" Р+"+s);
                                n->MoveRadiusBetter = false;
                            }
                            if(n->AttackRadiusBetter){
                                QString s = QString::number(n->AttackRadiusBetter);
                                ui->B1_crossBow->setText(ui->B1_crossBow->text()+" A+"+s);
                                n->MoveRadiusBetter = false;
                            }
                        }
                    }
                }else if(n->isKnight){
                    if(n->health == 0){
                        ui->H1_knight->setText("");
                        ui->B1_knight->setText("");
                    }else{
                        if(game->isAttackDone==1){
                            if(n->shieldUsed){
                                ui->B1_knight->setText(ui->B1_knight->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }else{
                            ui->H1_knight->setNum(n->health);

                            if(n->shieldEnabled){
                                 if(!(ui->B1_knight->text().contains("Щит", Qt::CaseInsensitive))){
                                    ui->B1_knight->setText(ui->B1_knight->text()+" Щит");
                                }
                            }
                            if(n->MoveRadiusBetter){
                                QString s = QString::number(n->MoveRadiusBetter);
                                ui->B1_knight->setText(ui->B1_knight->text()+" Р+"+s);
                                n->MoveRadiusBetter = false;
                            }
                            if(n->AttackRadiusBetter){
                                QString s = QString::number(n->AttackRadiusBetter);
                                ui->B1_knight->setText(ui->B1_knight->text()+" A+"+s);
                                n->MoveRadiusBetter = false;
                            }
                        }
                    }
                }else if(n->isSpearMan){
                    if(n->health == 0){
                        ui->H1_spearman->setText("");
                        ui->B1_spearman->setText("");
                    }else{
                        if(game->isAttackDone==1){
                            if(n->shieldUsed){
                                ui->B1_spearman->setText(ui->B1_spearman->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }else{
                            ui->H1_spearman->setNum(n->health);

                            if(n->shieldEnabled){
                                 if(!(ui->B1_spearman->text().contains("Щит", Qt::CaseInsensitive))){
                                    ui->B1_spearman->setText(ui->B1_spearman->text()+" Щит");
                                }
                            }
                            if(n->MoveRadiusBetter){
                                QString s = QString::number(n->MoveRadiusBetter);
                                ui->B1_spearman->setText(ui->B1_spearman->text()+" Р+"+s);
                                n->MoveRadiusBetter = false;
                            }
                            if(n->AttackRadiusBetter){
                                QString s = QString::number(n->AttackRadiusBetter);
                                ui->B1_spearman->setText(ui->B1_spearman->text()+" A+"+s);
                                n->MoveRadiusBetter = false;
                            }
                        }
                    }
                }else if(n->isHeavyRider){
                    if(n->health == 0){
                        ui->H1_heavy->setText("");
                        ui->B1_heavy->setText("");
                    }else{
                        if(game->isAttackDone==1){
                            if(n->shieldUsed){
                                ui->B1_heavy->setText(ui->B1_heavy->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }else{
                            ui->H1_heavy->setNum(n->health);

                            if(n->shieldEnabled){
                                 if(!(ui->B1_heavy->text().contains("Щит", Qt::CaseInsensitive))){
                                    ui->B1_heavy->setText(ui->B1_heavy->text()+" Щит");
                                }
                            }
                            if(n->MoveRadiusBetter){
                                QString s = QString::number(n->MoveRadiusBetter);
                                ui->B1_heavy->setText(ui->B1_heavy->text()+" Р+"+s);
                                n->MoveRadiusBetter = false;
                            }
                            if(n->AttackRadiusBetter){
                                QString s = QString::number(n->AttackRadiusBetter);
                                ui->B1_heavy->setText(ui->B1_heavy->text()+" A+"+s);
                                n->MoveRadiusBetter = false;
                            }
                        }
                    }
                }else if(n->isLightRider){
                    if(n->health == 0){
                        ui->H1_light->setText("");
                        ui->B1_light->setText("");
                    }else{
                        if(game->isAttackDone==1){
                            if(n->shieldUsed){
                                ui->B1_light->setText(ui->B1_light->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }else{
                            ui->H1_light->setNum(n->health);

                            if(n->shieldEnabled){
                                 if(!(ui->B1_light->text().contains("Щит", Qt::CaseInsensitive))){
                                    ui->B1_light->setText(ui->B1_light->text()+" Щит");
                                }
                            }
                            if(n->MoveRadiusBetter){
                                QString s = QString::number(n->MoveRadiusBetter);
                                ui->B1_light->setText(ui->B1_light->text()+" Р+"+s);
                                n->MoveRadiusBetter = false;
                            }
                            if(n->AttackRadiusBetter){
                                QString s = QString::number(n->AttackRadiusBetter);
                                ui->B1_light->setText(ui->B1_light->text()+" A+"+s);
                                n->MoveRadiusBetter = false;
                            }
                        }
                    }
                }
            }
        }else if(!game->currNumBase || game->isAttackDone==2){
            for (Unit* n : this->game->base2->units){ // не все созданны
                if(n->isArcher){
                    if(n->health == 0){
                        ui->H2_archer->setText("");
                        ui->B2_archer->setText("");

                    }else{
                        if(game->isAttackDone==2){
                            if(n->shieldUsed){
                                ui->B2_archer->setText(ui->B2_archer->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }

                        ui->H2_archer->setNum(n->health);
                        if(n->shieldEnabled){
                            if(!(ui->B2_archer->text().contains("Щит", Qt::CaseInsensitive))){
                               ui->B2_archer->setText(ui->B2_archer->text()+" Щит");
                           }
                        }
                        if(n->MoveRadiusBetter){
                            QString s = QString::number(n->MoveRadiusBetter);
                            ui->B2_archer->setText(ui->B2_archer->text()+" Р+"+s);
                            n->MoveRadiusBetter = false;
                        }
                        if(n->AttackRadiusBetter){
                            QString s = QString::number(n->AttackRadiusBetter);
                            ui->B2_archer->setText(ui->B2_archer->text()+" A+"+s);
                            n->AttackRadiusBetter = false;
                        }
                    }
                }else if(n->isCrossBowMan){
                    if(n->health == 0){
                        ui->H2_crossBow->setText("");
                        ui->B2_crossBow->setText("");
                    }else{
                        if(game->isAttackDone==2){
                            if(n->shieldUsed){
                                ui->B2_crossBow->setText(ui->B2_crossBow->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }

                        ui->H2_crossBow->setNum(n->health);
                        if(n->shieldEnabled){
                            if(!(ui->B2_crossBow->text().contains("Щит", Qt::CaseInsensitive))){
                               ui->B2_crossBow->setText(ui->B2_crossBow->text()+" Щит");
                           }
                        }
                        if(n->MoveRadiusBetter){
                            QString s = QString::number(n->MoveRadiusBetter);
                            ui->B2_crossBow->setText(ui->B2_crossBow->text()+" Р+"+s);
                            n->MoveRadiusBetter = false;
                        }
                        if(n->AttackRadiusBetter){
                            QString s = QString::number(n->AttackRadiusBetter);
                            ui->B2_crossBow->setText(ui->B2_crossBow->text()+" A+"+s);
                            n->AttackRadiusBetter = false;
                        }
                    }
                }else if(n->isKnight){
                    if(n->health == 0){
                        ui->H2_knight->setText("");
                        ui->B2_knight->setText("");
                    }else{
                        if(game->isAttackDone==2){
                            if(n->shieldUsed){
                                ui->B2_knight->setText(ui->B2_knight->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }

                        ui->H2_knight->setNum(n->health);
                        if(n->shieldEnabled){
                            if(!(ui->B2_knight->text().contains("Щит", Qt::CaseInsensitive))){
                               ui->B2_knight->setText(ui->B2_knight->text()+" Щит");
                           }
                        }
                        if(n->MoveRadiusBetter){
                            QString s = QString::number(n->MoveRadiusBetter);
                            ui->B2_knight->setText(ui->B2_knight->text()+" Р+"+s);
                            n->MoveRadiusBetter = false;
                        }
                        if(n->AttackRadiusBetter){
                            QString s = QString::number(n->AttackRadiusBetter);
                            ui->B2_knight->setText(ui->B2_knight->text()+" A+"+s);
                            n->AttackRadiusBetter = false;
                        }
                    }
                }else if(n->isSpearMan){
                    if(n->health == 0){
                        ui->H2_spearman->setText("");
                        ui->B2_spearman->setText("");
                    }else{
                        if(game->isAttackDone==2){
                            if(n->shieldUsed){
                                ui->B2_spearman->setText(ui->B2_spearman->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }

                        ui->H2_spearman->setNum(n->health);
                        if(n->shieldEnabled){
                            if(!(ui->B2_spearman->text().contains("Щит", Qt::CaseInsensitive))){
                               ui->B2_spearman->setText(ui->B2_spearman->text()+" Щит");
                           }
                        }
                        if(n->MoveRadiusBetter){
                            QString s = QString::number(n->MoveRadiusBetter);
                            ui->B2_spearman->setText(ui->B2_spearman->text()+" Р+"+s);
                            n->MoveRadiusBetter = false;
                        }
                        if(n->AttackRadiusBetter){
                            QString s = QString::number(n->AttackRadiusBetter);
                            ui->B2_spearman->setText(ui->B2_spearman->text()+" A+"+s);
                            n->AttackRadiusBetter = false;
                        }
                    }
                }else if(n->isHeavyRider){
                    if(n->health == 0){
                        ui->H2_heavy->setText("");
                        ui->B2_heavy->setText("");
                    }else{
                        if(game->isAttackDone==2){
                            if(n->shieldUsed){
                                ui->B2_heavy->setText(ui->B2_heavy->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }

                        ui->H2_heavy->setNum(n->health);
                        if(n->shieldEnabled){
                            if(!(ui->B2_heavy->text().contains("Щит", Qt::CaseInsensitive))){
                               ui->B2_heavy->setText(ui->B2_heavy->text()+" Щит");
                           }
                        }
                        if(n->MoveRadiusBetter){
                            QString s = QString::number(n->MoveRadiusBetter);
                            ui->B2_heavy->setText(ui->B2_heavy->text()+" Р+"+s);
                            n->MoveRadiusBetter = false;
                        }
                        if(n->AttackRadiusBetter){
                            QString s = QString::number(n->AttackRadiusBetter);
                            ui->B2_heavy->setText(ui->B2_heavy->text()+" A+"+s);
                            n->AttackRadiusBetter = false;
                        }
                    }
                }else if(n->isLightRider){
                    if(n->health == 0){
                        ui->H2_light->setText("");
                        ui->B2_light->setText("");
                    }else{
                        if(game->isAttackDone==2){
                            if(n->shieldUsed){
                                ui->B2_light->setText(ui->B2_light->text().remove(QString("Щит"), Qt::CaseInsensitive));
                                n->shieldUsed = false;
                            }
                        }

                        ui->H2_light->setNum(n->health);
                        if(n->shieldEnabled){
                            if(!(ui->B2_light->text().contains("Щит", Qt::CaseInsensitive))){
                               ui->B2_light->setText(ui->B2_light->text()+" Щит");
                           }
                        }
                        if(n->MoveRadiusBetter){
                            QString s = QString::number(n->MoveRadiusBetter);
                            ui->B2_light->setText(ui->B2_light->text()+" Р+"+s);
                            n->MoveRadiusBetter = false;
                        }
                        if(n->AttackRadiusBetter){
                            QString s = QString::number(n->AttackRadiusBetter);
                            ui->B2_light->setText(ui->B2_light->text()+" A+"+s);
                            n->AttackRadiusBetter = false;
                        }
                    }
                }
            }
        }
    }


}



void MainWindow::on_actionSave_triggered()
{
    Originator* originator = new Originator("./save.txt", 1);
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup(game,isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, game->currNumBase);

}

void MainWindow::on_actionOpen_triggered()
{
    Originator* originator = new Originator("./save.txt", 0);
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Undo(&this->game,isUnitSelected, logToFile, logToTerminal, withoutLog, &selectedUnit, game->currNumBase);
    show_table();
}
