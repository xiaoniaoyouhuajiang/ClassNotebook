#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class LogWindow;
}

class LogWindow : public QDialog
{
    friend class MainWindow;
    Q_OBJECT
    MainWindow* ptr;
public:
    explicit LogWindow(QWidget *parent = nullptr);
    ~LogWindow();

private:
    Ui::LogWindow *ui;
};

#endif // LOGWINDOW_H
