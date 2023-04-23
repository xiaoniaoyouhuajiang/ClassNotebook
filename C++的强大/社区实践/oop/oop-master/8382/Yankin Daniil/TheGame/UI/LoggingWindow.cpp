#include "LoggingWindow.h"
#include "ui_LoggingWindow.h"
#include "Log/LogAdapter.h"


LoggingWindow::LoggingWindow(QWidget *parent) : QDialog(parent), ui(new Ui::LoggingWindow), loggingDirection(LOGGING_DIR_NO), loggingMode(LOGGING_MODE_DEFAULT){
    ui->setupUi(this);

    ui->directionBox->addItem("No Logging");
    ui->directionBox->addItem("File Logging");
    ui->directionBox->addItem("Terminal Logging");

    ui->formatBox->addItem("Default");
    ui->formatBox->addItem("Odd");

    setWindowFlags(Qt::CustomizeWindowHint);
}

LoggingWindow::~LoggingWindow() {
    delete ui;
}

uint16_t LoggingWindow::getLoggingDirection() {
    return loggingDirection;
}

uint16_t LoggingWindow::getLoggingMode() {
    return loggingMode;
}

void LoggingWindow::setLoggingDirection(uint16_t value) {
    loggingDirection = value;

    if (value == LOGGING_DIR_NO)
        ui->directionBox->setCurrentIndex(0);
    else if (value == LOGGING_DIR_FILE)
        ui->directionBox->setCurrentIndex(1);
    else if (value == LOGGING_DIR_TERMINAL)
        ui->directionBox->setCurrentIndex(2);
}

void LoggingWindow::setLoggingMode(uint16_t value) {
    loggingMode = value;

    if (value == LOGGING_MODE_DEFAULT)
        ui->formatBox->setCurrentIndex(0);
    else if (value == LOGGING_MODE_ODD)
        ui->formatBox->setCurrentIndex(1);
}

bool LoggingWindow::checkAccept() {
    return accept;
}


void LoggingWindow::on_closeButton_clicked() {
    accept = false;
    close();
}

void LoggingWindow::on_okButton_clicked() {
    if (ui->directionBox->currentIndex() == 0)
        loggingDirection = LOGGING_DIR_NO;
    else if (ui->directionBox->currentIndex() == 1)
        loggingDirection = LOGGING_DIR_FILE;
    else if (ui->directionBox->currentIndex() == 2)
        loggingDirection = LOGGING_DIR_TERMINAL;

    if (ui->formatBox->currentIndex() == 0)
        loggingMode = LOGGING_MODE_DEFAULT;
    else if (ui->formatBox->currentIndex() == 1)
        loggingMode = LOGGING_MODE_ODD;

    accept = true;
    close();
}
