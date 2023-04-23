#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QSettings>
#include <QFileDialog>
#include "LoggingWindow.h"
#include "NewGameWindow.h"

#include "AttributeWidget.h"
#include "ModifiedScene.h"
#include "Field/Field.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void showWinners(std::vector<uint16_t>& winners);

private slots:
    void keyPressEvent(QKeyEvent *event);

    void on_buttonNewGame_clicked();
    void on_buttonMap_clicked();
    void on_buttonSave_clicked();
    void on_buttonLoad_clicked();
    void on_buttonLogging_clicked();
    void on_buttonExit_clicked();

private:
    Ui::MainWindow* ui;
    std::shared_ptr<ModifiedScene> gameScene;

    LoggingWindow* loggingWindow;
    uint16_t loggingDirection;
    uint16_t loggingMode;

    QSettings* settings;
};
