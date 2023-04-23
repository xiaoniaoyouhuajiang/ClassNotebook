#include "ModifiedView.h"
#include "QWheelEvent"

ModifiedView::ModifiedView(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent) {}
ModifiedView::ModifiedView(QWidget* parent) : QGraphicsView(parent) {}

void ModifiedView::wheelEvent(QWheelEvent* event) {
    if (!(event->modifiers() & Qt::AltModifier)) {
        event->ignore();
        return;
    }

    if (event->delta() > 0) {
        scale(1.1, 1.1);
    }
    if (event->delta() < 0) {
        scale(1 / 1.1, 1 / 1.1);
    }
    scene()->update(sceneRect());
}

void ModifiedView::enterEvent(QEvent *event) {
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void ModifiedView::mousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void ModifiedView::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}
