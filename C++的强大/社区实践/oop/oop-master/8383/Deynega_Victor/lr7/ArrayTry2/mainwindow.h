#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Game.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Game* game;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUnitImg(int type, int cell);
    void makeMenu();
    void makeActionMenu();
    void onActionButtons();
    void offActionButtons();
    void targetVisualising();
    void targetReset();
    void prepareResMenu();
    void prepareActionMenu(int& turnCounter);
    void endTurn();
    void gameOver(QString str);
    void visualiseNewGame();
    QList<QPushButton *> *buttons;
    QLabel* label;
    QLabel* info;
    QPushButton* newGame;
    QPushButton* exitGame;
    QPushButton* infoB;
    QPushButton* infoB2;

private:
    Ui::MainWindow *ui;
private slots:
    void handleButton();
    void resMenuHandler();
    void actionMenuHandler();
    void targetHandler();
    void exitGameHandle();
    void infoHandler1();
    void infoHandler2();
    void newGameHandle();
};
#endif // MAINWINDOW_H
