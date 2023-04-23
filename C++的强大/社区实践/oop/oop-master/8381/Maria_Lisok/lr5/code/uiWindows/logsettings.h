#ifndef LOGSETTINGS_H
#define LOGSETTINGS_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class LogSettings;
}

class LogSettings : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit LogSettings(QWidget *parent = nullptr);
    ~LogSettings();
    MainWindow* ptr;
private slots:
    void on_logToFile_clicked();

    void on_logToTerminal_clicked();

    void on_noLogs_clicked();

private:
    Ui::LogSettings *ui;
};

#endif // LOGSETTINGS_H
