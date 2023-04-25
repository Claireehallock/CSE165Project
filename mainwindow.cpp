
#include "mainwindow.h"
#include "Objects.h"


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
    resizeGL(this->width(), this->height());
}

void MainWindow::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);



    if(w > h){
        qreal aspectratio = qreal(w)/qreal(h);
        glOrtho(-1*aspectratio, 1*aspectratio, -1, 1, 1, -1);
    }
    else{
        qreal aspectratio = qreal(h)/qreal(w);
        glOrtho(-1, 1,-1*aspectratio, 1*aspectratio, 1, -1);
    }
}

void MainWindow::paintGL()
{
    glClearColor(0.0, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Background B = Background();
    B.paint();

    glFlush();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    paintGL();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(), this->height());
    this->update();
}

void MainWindow::UpdateAnimation()
{
    this->update();
}


