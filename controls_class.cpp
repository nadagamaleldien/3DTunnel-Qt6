#include "controls_class.h"
#include <QKeyEvent>
#include <QDebug>
#include <QWheelEvent>

controls_class::controls_class(QWidget *parent)
    : QWidget(parent), cameraPosition(0.0f, 0.0f, -1.0f), movementSpeed(0.1f), zoomSpeed(0.5f)
{
}

void controls_class::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        qDebug() << "W pressed";
        cameraPosition += QVector3D(0.0f, 0.0f, +movementSpeed);
        break;
    case Qt::Key_S:
        qDebug() << "S pressed";
        cameraPosition += QVector3D(0.0f, 0.0f, -movementSpeed);
        break;
    case Qt::Key_A:
        qDebug() << "A pressed";
        cameraPosition += QVector3D(-movementSpeed, 0.0f, 0.0f);
        break;
    case Qt::Key_D:
        qDebug() << "D pressed";
        cameraPosition += QVector3D(movementSpeed, 0.0f, 0.0f);
        break;
    case Qt::Key_Q:
        qDebug() << "Q pressed";
        cameraPosition += QVector3D(0.0f, +movementSpeed, 0.0f);
        break;
    case Qt::Key_E:
        qDebug() << "E pressed";
        cameraPosition += QVector3D(0.0f, -movementSpeed, 0.0f);
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }

    emit motion(cameraPosition);
}

void controls_class::wheelEvent(QWheelEvent *event)
{
    float zoomDelta = event->angleDelta().y() > 0 ? zoomSpeed : -zoomSpeed;
    cameraPosition += QVector3D(0.0f, 0.0f, zoomDelta);

    qDebug() << "Zoom changed:" << cameraPosition;

    emit motion(cameraPosition);
}
