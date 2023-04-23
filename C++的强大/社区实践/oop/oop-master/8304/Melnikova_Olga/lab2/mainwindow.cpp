#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
/*
    QTableWidgetItem *i =new QTableWidgetItem("rand");
    i->setBackgroundColor(Qt::red);
    ui->table->setItem(0,0, i);*/

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
                            //item->setBackgroundColor(Qt::red);
                            item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(70,70));
                            ui->table->setItem(i, j, item);
                        }
            }else{
                QImage *img = new QImage();
                QString qText = QString(field.cells(j + 1, i + 1).landscape->symb.c_str());
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

void MainWindow::on_actionCreate_new_triggered()
{
    window = new CreateGameWindow(this);
    connect(window, &CreateGameWindow::window, this, &MainWindow::show);
    window->setModal(true);
    window->show();
}

void MainWindow::slotSetTableHW(int h, int w)
{


    //Field field(h, w);
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
    Game game(h,w);
    show_table(*game.field);
    //test(field);
}

void MainWindow::test(Field& field){
    objectFabric fabric;

    //field.addObject(fabric.createBase(), 5, 5);
    field.addObject(fabric.createArcher(), 3, 2);//столб, стр
    field.addObject(fabric.createCrossbowman(), 2, 2);
    field.addObject(fabric.createLightRider(), 2, 3);
    field.addObject(fabric.createHeavyRider(), 2, 4);
    field.addObject(fabric.createKnight(), 4, 4);
    field.addObject(fabric.createSpearman(), 12, 12);
   // field.addObject(fabric.createBase(0), 0, 0);


    show_table(field);
    //Копирование поля
   // Field field2 = field1;
    //field2.print();
    //перемещение
   // field2.moveUnit(12,12, 11,11);
    //field2.moveUnit(12,12, 11,12);
   // field2.moveUnit(2,4, 3,6);
    //field2.print();
   // field2.deleteObject(3, 2);
    //field1.print();
    //field2.print();
    //Конструкторы
   // Field f(5,5);
    //Field g = f;
   // Cell r(6,6);
   // Cell s(std::move(r));
}
