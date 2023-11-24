#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget {
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize sizeHint() const {  return QSize(1000, 1000); }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
};

#endif // GLWIDGET_H
