#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memory"

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
                        QString qText = QString(field.cells(j + 1, i + 1).innerObject->symb.c_str());
                        if (img->load(qText))
                        {
                            QTableWidgetItem *item = new QTableWidgetItem();

                            item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(65,65));
                            /*if(field.cells(j + 1, i + 1).innerObject->numBase == 0){
                                item->setBackgroundColor(Qt::red);
                            }else if(field.cells(j + 1, i + 1).innerObject->numBase == 1){
                                item->setBackgroundColor(Qt::green);
                            }else{
                                item->setBackgroundColor(Qt::yellow);
                            }*/

                            ui->table->setItem(i, j, item);

                        }
            }else{
                QImage *img = new QImage();
                QString qText = QString(field.cells(j + 1, i + 1).landscape->symb.c_str());
                if (img->load(qText))
                {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    //item->setBackgroundColor(Qt::red);
                    item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(65,65));
                    ui->table->setItem(i, j, item);
                }
            }
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

void MainWindow::slotSetTableHW(int h, int w)
{
    this->ui->table->setRowCount(h);
    this->ui->table->setColumnCount(w);
    this->ui->table->horizontalHeader()->setDefaultSectionSize(70);
    this->ui->table->verticalHeader()->setDefaultSectionSize(70);
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
    Game game(h,w);
    *this->game = game;
    
    show_table(*game.field);

    connect(ui->table, SIGNAL(cellClicked(int, int)), SLOT(Cliked(int, int)));
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::Cliked(int h, int w){
    //фасад
    Facade* facade = new Facade(game, h, w, &isUnitSelected, &selectedUnit, &currNumBase);
    facade->func();
    show_table(*game->field);

}


