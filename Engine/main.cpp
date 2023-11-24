#include <GL/glew.h>
#include <QApplication>
#include "glwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GLWidget glWidget;
    glWidget.show();
    return app.exec();
}
