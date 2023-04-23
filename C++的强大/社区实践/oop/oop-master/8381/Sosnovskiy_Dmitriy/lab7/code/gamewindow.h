#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QLayout>
#include <QFileDialog>
#include <QComboBox>
#include "client_handler.h"


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow, public IView
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void askForBasesPosition() override;
    void update(UPDATE_UI_TYPE type) override;
    void setCurrentPlayerInfo(unsigned int currentPlayer) override;
    void showWinnerInfo(unsigned int winnerPlayer) override;
    void showError(Exception* exc) override;
    void onLoadingSucceed() override;

private slots:

    void on_startGameButton_clicked();

    void on_addUnitButton_clicked();

    void on_baseInfoButton_clicked();

    void on_setLoggingTypeButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::GameWindow *ui;
    GameFacade* facade;

    StartGameHandler* chainOfResponsibilities;

    void setEnableButtons();
};

#endif // GAMEWINDOW_H
