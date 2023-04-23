#ifndef MOVE_H
#define MOVE_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class move;
}

class Move : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit Move(QWidget *parent = nullptr);
    ~Move();
    MainWindow* ptr;
private slots:
    void on_moveButton_accepted();

private:
    Ui::move *ui;
};

#endif // MOVE_H
