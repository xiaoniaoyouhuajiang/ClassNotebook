#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QLayout>
#include <QComboBox>
#include "clientHandler.h"

namespace Ui
{
class GameWindow;
}

class GameWindow : public QMainWindow, public ViewInterface
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void askForBasesPosition() override;
    void update() override;
    void setCurrentPlayerInfo(unsigned int currentPlayer) override;
    void showWinnerInfo(unsigned int winnerPlayer) override;

private slots:



    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

private:
    Ui::GameWindow *ui;
    GameFacade* facade;

    StartGameHandler* chainOfResponsibilities;
};

#endif // GAMEWINDOW_H
