#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QBoxLayout>
#include "Demo.h"
#include "gamewindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton* buttonNewGame;
    QPushButton* buttonNewSoloGame;
    QPushButton* buttonLoadGame;
    QVBoxLayout* layout;
    QWidget* centralWidget;
    GameWindow* gameWindow;

private slots:
    void newGameButtonClicked();
    void loadGameButtonClicked();
    void soloGameButtonClicked();
};

#endif // MAINWINDOW_H
