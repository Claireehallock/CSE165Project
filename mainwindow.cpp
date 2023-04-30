
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

    executeCommand = Nothing;

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateAnimation()));

    timer->start();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete context;
    for(int i = 0; i < d.size(); i++){
        delete d.at(i);
    }
}

void MainWindow::click(float x, float y)
{
    int i = 0;
    bool check = false;
    while(!check && i < c.size()){
        if (c.at(i)->inside(x, y)){
            executeCommand = command(c.at(i)->press());
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
        float x = ((float)event->pos().x()-wExtraPixels/2)/windowSize*2-1;
        float y = (0-(float)event->pos().y()-hExtraPixels/2)/windowSize*2+1;
        click(x, y);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mousePressed = false;
        unclick();
    }
}


//Note:
//c[0]->c[5] are books
void MainWindow::UpdateAnimation()//Used to check for any updates
{
    if(executeCommand != Nothing){
        switch((int)executeCommand){
        case 1://Books
            //Checks for correct order of selected books
            if(dynamic_cast<Book*>(c[0])->getSelected() == 3 &&
               dynamic_cast<Book*>(c[1])->getSelected() == 2 &&
               dynamic_cast<Book*>(c[2])->getSelected() == 6 &&
               dynamic_cast<Book*>(c[3])->getSelected() == 5 &&
               dynamic_cast<Book*>(c[4])->getSelected() == 1 &&
               dynamic_cast<Book*>(c[5])->getSelected() == 4)
            {
                //What to do if correct order selected
                dynamic_cast<Book*>(c[0])->numSelected = -1;
            }
            else{
                //
            }
            for(int i = 0; i < 6; i++){
                dynamic_cast<Book*>(c[i])->setSelected(0);
            }
            break;
        case 2:
            break;
        case 101: //button 1 (TV Button)
            d[8]->toggleShow();
            break;
        }
        executeCommand = Nothing;
    }
    if(time < INT_MAX){
        time++;
    }
    else{
        time = 0;
    }
    if (time%60 == 0){
        dynamic_cast<Mouse*>(c[7])->move();
    }
    this->update();
}


