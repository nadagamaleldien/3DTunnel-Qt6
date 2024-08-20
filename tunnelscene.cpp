#include "tunnelscene.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QMatrix4x4>
#include <QDebug>

TunnelScene::TunnelScene(QWidget *parent)
    : QOpenGLWidget(parent), tunnelRadius(3.0f), tunnelLength(40.0f)
{
    shaderProgram = new QOpenGLShaderProgram(this);
}

TunnelScene::~TunnelScene()
{
    makeCurrent();
    delete shaderProgram;
    doneCurrent();
}

void TunnelScene::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background color
    glEnable(GL_DEPTH_TEST);

    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex.glsl");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment.glsl");
    shaderProgram->link();
    shaderProgram->bind();

    createTunnel();


    // Initialize the camera position at the other end of the tunnel, inside the bounds
    QVector3D initialCameraPosition(0.0f, 0.0f, -1.0f);
    updateCameraPosition(initialCameraPosition);
}

void TunnelScene::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // Set up the projection matrix
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45.0f, static_cast<float>(w) / h, 0.1f, 1000.0f);
}

void TunnelScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply the projection and view matrices
    QMatrix4x4 mvpMatrix = projectionMatrix * viewMatrix;

    shaderProgram->bind();
    shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);

    drawTunnel();
}

void TunnelScene::createTunnel()
{
}

void TunnelScene::drawTunnel()
{
    // Render the tunnel using OpenGL functions, GL_QUAD_STRIP generates quads (rectangles) to fill spaces between inner and outer circles
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * M_PI / 180.0f;
        float nextAngle = (i + 10) * M_PI / 180.0f;

        // Outer circle
        glVertex3f(tunnelRadius * cos(angle), tunnelRadius * sin(angle), 0.0f);
        glVertex3f(tunnelRadius * cos(nextAngle), tunnelRadius * sin(nextAngle), 0.0f);
        glVertex3f(tunnelRadius * cos(angle), tunnelRadius * sin(angle), tunnelLength);
        glVertex3f(tunnelRadius * cos(nextAngle), tunnelRadius * sin(nextAngle), tunnelLength);

        // Inner circle
        glVertex3f((tunnelRadius - 0.5f) * cos(angle), (tunnelRadius - 0.5f) * sin(angle), 0.0f);
        glVertex3f((tunnelRadius - 0.5f) * cos(nextAngle), (tunnelRadius - 0.5f) * sin(nextAngle), 0.0f);
        glVertex3f((tunnelRadius - 0.5f) * cos(angle), (tunnelRadius - 0.5f) * sin(angle), tunnelLength);
        glVertex3f((tunnelRadius - 0.5f) * cos(nextAngle), (tunnelRadius - 0.5f) * sin(nextAngle), tunnelLength);
    }
    glEnd();
}

void TunnelScene::updateCameraPosition(const QVector3D &newPosition)
{
    //calculating distance from z axis
    float distanceFromZAxis = sqrt(newPosition.x() * newPosition.x() + newPosition.y() * newPosition.y());

    if (distanceFromZAxis < tunnelRadius)
    {
        // Update the camera position if it is inside the tunnel
        viewMatrix.setToIdentity();
        viewMatrix.lookAt(newPosition,                        // Updated eye position
                          QVector3D(0.0f, 0.0f, 0.0f),        // Look at the center of the tunnel
                          QVector3D(0.0f, 1.0f, 0.0f));       // Up direction remains unchanged
        qDebug() << "Updated Camera Position:" << newPosition;

    }
    else
    {
        // Optionally handle the case where the camera is out of bounds
        qDebug() << "Camera position out of bounds:" << newPosition;
    }



    update();
}


