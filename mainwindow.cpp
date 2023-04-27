
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

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateAnimation()));

    timer->start();

}

MainWindow::~MainWindow()
{
}

void MainWindow::click(float x, float y)
{
    int i = 0;
    bool check = false;
    while(!check && i < c.size()){
        if (c.at(i)->inside(x, y)){
            c.at(i)->press();
            std::cout <<"depth: "<< c.at(i)->getDepth()<<std::endl;
            selected = c.at(i);
            UpdateAnimation();
            check = true;
        }
        i++;
    }
}

void MainWindow::unclick()
{
    if(selected){
        selected->release();
        selected = NULL;
    }
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

        windowSize = h;
        hExtraPixels = 0;
        wExtraPixels = w-h;
    }
    else{
        qreal aspectratio = qreal(h)/qreal(w);
        glOrtho(-1, 1,-1*aspectratio, 1*aspectratio, 1, -1);

        windowSize = w;
        hExtraPixels = h-w;
        wExtraPixels = 0;
    }
}

void MainWindow::paintGL()
{
    glClearColor(0.0, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < d.size(); i++){
        d.at(i)->paint();
    }

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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mousePressed = true;
        std::cout << "x: " << event->pos().x() << " y: " << event->pos().y() << std::endl;
//        dynamic_cast<ClickableObject*> (d.at(1))->press();
        float x = ((float)event->pos().x()-wExtraPixels/2)/windowSize*2-1;
        float y = (0-(float)event->pos().y()-wExtraPixels/2)/windowSize*2+1;
        click(x, y);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mousePressed = false;
        std::cout << "Released\n";
        unclick();
//        dynamic_cast<ClickableObject*> (d.at(1))->release();
    }
}

void MainWindow::UpdateAnimation()
{
    this->update();
}


