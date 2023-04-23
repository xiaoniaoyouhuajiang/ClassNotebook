#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_nextNode_clicked();

    void on_prevNode_clicked();

    void on_initNode_clicked();

    void on_newNode_clicked();

    void on_changeNode_clicked();

    void on_saveButton_clicked();

    void on_swapButton_clicked();

    void on_cacheSaveButton_clicked();

    void on_newNextNode_clicked();

    void on_newStart_clicked();

    void on_pushButton_clicked();

    void on_openGraph_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
