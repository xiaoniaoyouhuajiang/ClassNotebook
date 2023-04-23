#pragma once

#include <QWidget>


namespace Ui {
class TurnButton;
}

class TurnButton : public QWidget
{
    Q_OBJECT

public:
    explicit TurnButton(QWidget *parent = nullptr);
    ~TurnButton();

private slots:
    void on_turnButton_clicked();

private:
    Ui::TurnButton *ui;
};
