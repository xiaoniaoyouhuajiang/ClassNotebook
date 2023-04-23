#pragma once

#include <QDialog>

namespace Ui {
class NewGameWindow;
}

class NewGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameWindow(QWidget *parent = nullptr);
    ~NewGameWindow();

    uint16_t getWidth();
    uint16_t getHeight();
    uint16_t getPlayerCount();
    uint16_t getRule();
    bool checkAccept();

private slots:
    void on_closeButton_clicked();
    void on_okButton_clicked();

private:
    Ui::NewGameWindow *ui;

    uint16_t width;
    uint16_t height;
    uint16_t playerCount;
    uint16_t rule;
    bool accept;
};
