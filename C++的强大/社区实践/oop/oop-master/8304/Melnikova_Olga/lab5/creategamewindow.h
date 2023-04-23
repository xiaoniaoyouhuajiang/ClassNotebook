#ifndef CREATEGAMEWINDOW_H
#define CREATEGAMEWINDOW_H

#include <QDialog>


namespace Ui {
class CreateGameWindow;
}

class CreateGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGameWindow(QWidget *parent = nullptr);
    ~CreateGameWindow();
    int H = 0;
    int W = 0;
    int flag = 0;

private slots:
    void on_pushButton_clicked();

signals:
    void signalSetTableHW(int, int, bool, bool, bool);

private:
    Ui::CreateGameWindow *ui;
};

#endif // CREATEGAMEWINDOW_H
