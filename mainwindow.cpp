
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2, 1);
    setFormat(format);

    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    openGLFunctions = context->functions();

}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeGL()
{

}

void MainWindow::resizeGL(int w, int h)
{

}

void MainWindow::paintGL()
{
    glClearColor(1.0, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();

    glFlush();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    paintGL();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}


