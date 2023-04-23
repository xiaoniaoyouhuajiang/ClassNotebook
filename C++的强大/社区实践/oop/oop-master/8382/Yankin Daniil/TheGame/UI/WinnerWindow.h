#pragma once

#include <QDialog>

namespace Ui {
class WinnerWindow;
}

class WinnerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WinnerWindow(std::vector<uint16_t>& winners, QWidget *parent = nullptr);
    ~WinnerWindow();

private slots:
    void on_okButton_clicked();

private:
    Ui::WinnerWindow *ui;
};
