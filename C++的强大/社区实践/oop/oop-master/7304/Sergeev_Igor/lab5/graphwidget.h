#ifndef GRAPHWIDGET_H
 #define GRAPHWIDGET_H

 #include <QtGui>
 #include <QGraphicsView>

 class Node;

 class GraphWidget : public QGraphicsView
 {
     Q_OBJECT

 public:
     GraphWidget(QWidget *parent = 0);
        QGraphicsScene *my_scene;

     void itemMoved();

 protected:
     void keyPressEvent(QKeyEvent *event);
     void timerEvent(QTimerEvent *event);
     void wheelEvent(QWheelEvent *event);
     void drawBackground(QPainter *painter, const QRectF &rect);

     void scaleView(qreal scaleFactor);

 private:
     int timerId;
     Node *centerNode;
 };

 #endif
