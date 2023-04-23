#ifndef ATTACK_H
#define ATTACK_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class Attack;
}

class Attack : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:

    explicit Attack(QWidget *parent = nullptr);
    ~Attack();
    MainWindow* ptr;
private slots:

    void on_attackButton_accepted();

private:
    Ui::Attack *ui;
};

#endif // ATTACK_H
