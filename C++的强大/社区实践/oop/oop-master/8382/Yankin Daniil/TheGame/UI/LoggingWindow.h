#pragma once

#include <QDialog>

namespace Ui {
class LoggingWindow;
}

class LoggingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoggingWindow(QWidget *parent = nullptr);
    ~LoggingWindow();

    uint16_t getLoggingDirection();
    uint16_t getLoggingMode();
    void setLoggingDirection(uint16_t);
    void setLoggingMode(uint16_t);
    bool checkAccept();

private slots:
    void on_closeButton_clicked();
    void on_okButton_clicked();

private:
    Ui::LoggingWindow *ui;
    uint16_t loggingDirection;
    uint16_t loggingMode;
    bool accept;
};
