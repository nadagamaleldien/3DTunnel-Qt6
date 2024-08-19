#ifndef TUNNELSCENE_H
#define TUNNELSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector3D>

class TunnelScene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit TunnelScene(QWidget *parent = nullptr);
    ~TunnelScene();

public slots:
    void updateCameraPosition(const QVector3D &newPosition);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void createTunnel();
    void drawTunnel();

    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;
    float tunnelRadius;
    float tunnelLength;
    QOpenGLShaderProgram *shaderProgram;
};

#endif // TUNNELSCENE_H
