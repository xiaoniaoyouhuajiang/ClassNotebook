#pragma once

#include <QGraphicsView>


class ModifiedView : public  QGraphicsView
{
public:
    ModifiedView(QGraphicsScene* scene, QWidget* parent = nullptr);
    ModifiedView(QWidget* parent = nullptr);

private slots:
    void wheelEvent(QWheelEvent* event);
    void enterEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};
