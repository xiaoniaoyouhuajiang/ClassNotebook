#include "graphwindow.h"
#include "ui_graphwindow.h"
#include "QDebug"
#include <iostream>
#include <QDebug>
#include <QObject>
#include <customexception.h>
#include <QMessageBox>

GraphWindow::GraphWindow(QWidget *parent) : QWidget(parent), ui(new Ui::GraphWindow) {
    ui->setupUi(this);
}

GraphWindow::GraphWindow(QByteArray data) : QWidget(nullptr), ui(new Ui::GraphWindow) {
    qDebug() <<"input data" << data;
    if (QJsonDocument::fromJson(data).object()["connections"].toArray().size() == 0) {
        qDebug() <<"input empty!";
        throw CustomException("Launching Error", "input data is empty");
    }
    ui->setupUi(this);
    _data = data;

    graph = new Graph(data);
    //graph = Graph::getInstance(data);
    updatelabel(graph->getStringFormatGraph());
    CacheLog::get_instance().log_data("Main Window Created!\n");
    command = new Command();
}

GraphWindow::~GraphWindow() {
    delete ui;
}

void GraphWindow::updatelabel(QString new_text) {
    auto new_label = new QLabel(new_text);
    //new_label->setStyleSheet("QLabel { background-color : black; color : white; }");
    new_label->setFont(QFont( "Arial", 12, QFont::Bold));
    ui->graph_info->setWidget(new_label);

    auto log_label = new QLabel(CacheLog::get_instance().get_session_logs());
    log_label->setStyleSheet("QLabel { background-color : black; color : white; }");
    log_label->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->logs_widget->setWidget(log_label);
}


void GraphWindow::on_btn_next_clicked() {
    command->makeBackup(graph->makeSnapshot());
    graph->move_step();
    updatelabel(graph->getStringFormatGraph());
}

void GraphWindow::on_btn_prev_clicked() {
    try {
        CacheLog::get_instance().log_data("prev button clicked...\n");
        graph->restore(command->undo());
        updatelabel(graph->getStringFormatGraph());
    } catch (CustomException & ex) {
        QMessageBox msgBox;
           msgBox.setInformativeText(ex.get_data_state());

           msgBox.setText(ex.get_action_error());

           msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

           msgBox.setDefaultButton(QMessageBox::Ok);

           int ret = msgBox.exec();
    }
}

void GraphWindow::on_change_vertex_button_clicked() {
    CacheLog::get_instance().log_data("change vertex clicked...\n");

    try {
        int id = ui->pt_id->toPlainText().toInt();
        ui->pt_id->clear();
        VertexType vt = (VertexType)(ui->pt_operation->toPlainText().toInt());
        ui->pt_operation->clear();
        graph->changeVeretex(id, vt);
        updatelabel(graph->getStringFormatGraph());
        CacheLog::get_instance().log_data("vertex successfully changed\n");
    } catch (int e) {
        CacheLog::get_instance().log_data("Exception: " + CustomException("change vertex exception", QString::number(e)).get_action_error() + "\n");
    }
}
