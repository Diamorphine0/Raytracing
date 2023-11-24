#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget(){ }

void GLWidget::initializeGL() {
    glClearColor(1, 0, 1, 1); //define blue color as background color
}

void GLWidget::paintGL()
{
    //For anca: this is the beginning of your approach
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);



    /* This is the triangle drawing from before. Let's disregard this!

    QSize viewport_size = size();
    glViewport(0, 0, viewport_size.width(), viewport_size.height());

    //the matrix we work with now is the projection matrix. it is responsible for the projection 3D -> 2D
    glMatrixMode(GL_PROJECTION);

    //reset the current matrix to the identity matrix
    glLoadIdentity();

    //load the rpojection matrix
    glFrustum(-1, 1, -1, 1, 5, 7); // near and far match your triangle Z distance


    //the matrix we work with now is the modelview matrix. It is responsible for rotations etc.
    glMatrixMode(GL_MODELVIEW);

    //the color buffer and depth buffer are cleared
    //color buffer - basically processes colour?
    //depth buffer - basically keeps the depth of the objects?
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //reset the Modelview matrix to indentity
    glLoadIdentity();

    //moving the camera (Modelview matrix) 5 units back (zooming out)
    glTranslatef(0.0f, 0.0f, -5.0f);

    //we draw a triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f); // set color to blue
        glVertex3f( 0.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f,-1.0f, -1.0f);
        glVertex3f( 1.0f,-1.0f, -1.0f);
    glEnd();


    //another one - in front of the previous one
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
        glVertex3f( 0.0f, 0.5f, 0.0f);
        glVertex3f(-0.5f,-0.5f, 0.0f);
        glVertex3f( 0.5f,-0.5f, 0.0f);
    glEnd();

    //another one - this is not visible!
    //why?
    //because the z coordinates are positive, so its behind the camera~!
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 0.1f); // Set color to yellow
        glVertex3f( 0.0f, 0.25f, 0.1f);
        glVertex3f(-0.25f,-0.25f, 0.1f);
        glVertex3f( 0.25f,-0.25f, 0.1f);
    glEnd();

*/
}

void GLWidget::resizeGL(int w, int h)
{
    QOpenGLWidget::resize(w,h);
}
