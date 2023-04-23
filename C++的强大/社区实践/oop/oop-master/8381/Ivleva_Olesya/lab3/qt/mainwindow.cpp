#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->print->setReadOnly(true);
    ui->print_item->setReadOnly(true);
    QPixmap bkgnd(":/icons/land.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ui->menu->setPalette(QPalette(QColor(248, 251, 234)));
    facade = new Facade(ui, field);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_green_dr_clicked()
{
    facade->add_green_dr();
}

void MainWindow::on_add_red_dr_clicked()
{
    facade->add_red_dr();
}

void MainWindow::on_delete_item_clicked()
{
    facade->delete_item();
}

void MainWindow::on_move_unit_clicked()
{
    facade->move_unit();
}

void MainWindow::on_add_war_fight_clicked()
{
    facade->add_war_fight();
}

void MainWindow::on_add_war_ronin_clicked()
{
    facade->add_war_ronin();
}

void MainWindow::on_add_sen_fire_clicked()
{
    facade->add_sen_fire();
}

void MainWindow::on_add_sen_lion_clicked()
{
    facade->add_sen_lion();
}

void MainWindow::on_bonus_clicked()
{
    facade->bonus();
}

void MainWindow::on_action_triggered()
{
    facade->print_base();
}

void MainWindow::on_attack_clicked()
{
    facade->attack();
}
