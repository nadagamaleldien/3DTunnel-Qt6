#ifndef CONTROLS_CLASS_H
#define CONTROLS_CLASS_H

#include <QObject>
#include <QWidget>
#include <QVector3D>
#include <QWheelEvent>


class controls_class : public QWidget
{
    Q_OBJECT
public:
    explicit controls_class(QWidget *parent = nullptr);

private:
    QVector3D cameraPosition;
    float movementSpeed;
    float zoomSpeed;

signals:
    void motion(const QVector3D &newPosition);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // CONTROLS_CLASS_H
