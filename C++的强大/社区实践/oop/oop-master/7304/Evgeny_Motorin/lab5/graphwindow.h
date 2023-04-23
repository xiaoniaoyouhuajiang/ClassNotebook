#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include <QByteArray>
#include <graph.h>
#include <snapshot.h>
#include <log.h>
#include "customexception.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QWidget {
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    explicit GraphWindow(QByteArray data);
    ~GraphWindow();

private Q_SLOTS:
    void on_btn_next_clicked();

    void on_btn_prev_clicked();

    void on_change_vertex_button_clicked();

private:
    Ui::GraphWindow *ui;
    QByteArray _data;
    Graph* graph;
    Command* command;

    void updatelabel(QString new_text);
};

#endif // GRAPHWINDOW_H
