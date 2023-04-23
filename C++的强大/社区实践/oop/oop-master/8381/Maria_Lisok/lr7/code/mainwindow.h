#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "facade.h"
#include <uiWindows/addbase.h>
#include <uiWindows/addneutral.h>
#include <uiWindows/baseinfo.h>
#include <uiWindows/gameinfo.h>
#include <uiWindows/landinfo.h>
#include <uiWindows/neutralinfo.h>
#include <uiWindows/move.h>
#include <uiWindows/attack.h>
#include "uiWindows/AddUnit.h"
#include <uiWindows/unitinfo.h>
#include <uiWindows/logsettings.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AddUnit;
class AddNeutral;
class AddBase;
class BaseInfo;
class LandInfo;
class NeutralInfo;
class UnitInfo;
class GameInfo;
class Move;
class Attack;
class LogSettings;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Game* game = nullptr);
    ~MainWindow();

   friend class AddUnit;
   friend class AddNeutral;
   friend class AddBase;
   friend class BaseInfo;
   friend class LandInfo;
   friend class UnitInfo;
   friend class NeutralInfo;
   friend class GameInfo;
   friend class Move;
   friend class Attack;
   friend class LogSettings;
private slots:
    void on_gameInfoButton_clicked();

    void on_actionsave_game_triggered();

    void on_actionload_game_triggered();

    void on_actiongame_info_triggered();

    void on_actionadd_neutral_triggered();

    void on_actionadd_base_triggered();

    void on_actionland_info_triggered();

    void on_actionneutral_info_triggered();

    void on_actionbase_info_triggered();

    void on_actionMove_triggered();

    void on_actionAttack_triggered();

    void on_actionsetting_for_adding_triggered();

    void on_actionInfo_triggered();

    void on_action_logs_settings_triggered();

private:
    Ui::MainWindow *ui;
    Facade *facade;
};
#endif // MAINWINDOW_H
