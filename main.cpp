#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include "tunnelscene.h"
#include "controls_class.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    controls_class *window = new controls_class();
    QHBoxLayout layout(window);

    TunnelScene *scene = new TunnelScene();

    QObject::connect(window, &controls_class::motion, scene, &TunnelScene::updateCameraPosition);

    layout.addWidget(scene);

    window->setWindowTitle("OpenGL Tunnel Scene");
    window->resize(800, 600);
    window->show();

    return app.exec();
}
