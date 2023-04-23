#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->print->setReadOnly(true);
    ui->print_item->setReadOnly(true);
    QPixmap bkgnd("D:\\prog\\cpp\\OOP\\OOP_4sem\\icons\\land.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    field = new Field(n, m);
    base = new Base(field);
    field->add_item(2, 2, base, logs);
    fence = new Fence;
    field->add_item(4, 3, fence, logs);
    for(unsigned int i = 0; i < n; i++){
        for(unsigned int j = 0; j < m; j++){
            if(j % 3 == 0){
                Land* landsc = new Proxy("R");
                field->add_land(i, j, landsc);
            }
            else if (j % 3 == 1) {
                Land* landsc = new Proxy("F");
                field->add_land(i, j, landsc);
            }
            else {
                Land* landsc = new Proxy("D");
                field->add_land(i, j, landsc);
            }
        }
    }
    /*Field *field2 = new Field(n, m);
    Item* dragon = new Dragons_red;
    field2->add_unit(1, 1, dragon, logs);
    field = new Field(*field2);
    */
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_green_dr_clicked()
{
    base->add_green_dr(ui->set_x->value(), ui->set_y->value(), logs);
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    /*Iterator_field it_field(field);
    while (it_field.xy_in_field()) {//
        if (it_field.operator->() != nullptr){
            //print += it_field->print_who();
        }
        ++it_field;
    }*/
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_add_red_dr_clicked()
{
    base->add_red_dr(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), logs);
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_delete_item_clicked()
{
    if(field->delete_unit(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), logs)){
        //base->delete_unit(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()));
    }
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_move_unit_clicked()
{
    field->move_unit(ui->set_x->value(), ui->set_y->value(), ui->set_x1->value(), ui->set_y1->value(), logs);
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_add_war_fight_clicked()
{
    base->add_war_fight(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), logs);
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_add_war_ronin_clicked()
{
    base->add_war_ronin(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), logs);
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_add_sen_fire_clicked()
{
    base->add_sen_fire(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), logs);
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_add_sen_lion_clicked()
{
    base->add_sen_lion(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), logs);
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}

void MainWindow::on_bonus_clicked()
{
    if((ui->set_x->value()+ui->set_y->value())%3 == 0){
        Item* bonus = new Bonus_all(1);
        if(field->add_item(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), bonus, logs))
            logs += "Add bonus all specifications...\n";
    }
    else if ((ui->set_x->value()+ui->set_y->value())%3 == 1){
        Item* bonus = new Bonus_attack(1);
        if(field->add_item(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), bonus, logs))
            logs += "Add bonus attack...\n";
    }
    else if ((ui->set_x->value()+ui->set_y->value())%3 == 2) {
        Item* bonus = new Bonus_health(1);
        if(field->add_item(static_cast<unsigned int>(ui->set_x->value()),static_cast<unsigned int>(ui->set_y->value()), bonus, logs))
            logs += "Add bonus health...\n";
    }
    field->print_unit(print, n, m);
    ui->print_item->setText(QString::fromStdString(print));
    ui->print->setText(QString::fromStdString(logs));
}
