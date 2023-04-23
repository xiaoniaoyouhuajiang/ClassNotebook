#include "logsettings.h"
#include "ui_logsettings.h"

LogSettings::LogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogSettings)
{
    ui->setupUi(this);
}

LogSettings::~LogSettings()
{
    delete ui;
}

void LogSettings::on_logToFile_clicked()
{
    ptr->facade->setLogger(TOFILE);
}

void LogSettings::on_logToTerminal_clicked()
{
    ptr->facade->setLogger(TOTERMINAL);
}

void LogSettings::on_noLogs_clicked()
{
    ptr->facade->setLogger(NOLOG);
}
