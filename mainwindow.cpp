
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

    selected = NULL;

    executeCommand = Nothing;
    hasCheese = false;
    mouseGone = false;

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateAnimation()));

    timer->start(1);

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
        if (c.at(i)->inside(x, y)&&c.at(i)!=selected){
            executeCommand = command(c.at(i)->press());
            if(selected){//deselect current object
                if(selected->Movable()){
                    dynamic_cast<MovableObject*>(selected)->drop();
                }
                unclick();
            }
            selected = c.at(i);//Set new selected
            if(selected->Movable()){
                if(dynamic_cast<MovableObject*>(selected)->isCheese()){
                    dynamic_cast<Mouse*>(d[9])->selectCheese();
                }
                if(dynamic_cast<MovableObject*>(selected)->isKey()){
                    dynamic_cast<KeyBox*>(d[10])->selectKey();
                }
            }
            UpdateAnimation();
            check = true;
        }
        i++;
    }
}

void MainWindow::unclick()
{
    if(selected){
        if(selected->Movable()){
            if(dynamic_cast<MovableObject*>(selected)->isCheese()){
                dynamic_cast<Mouse*>(d[9])->unselectCheese();
            }
            if(dynamic_cast<MovableObject*>(selected)->isKey()){
                dynamic_cast<KeyBox*>(d[10])->unselectKey();
            }
        }
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

    if (event->button() == Qt::RightButton) {
        if(selected && selected->Movable()){
            dynamic_cast<MovableObject*>(selected)->drop();
            unclick();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(selected && !selected->Movable()){
            mousePressed = false;
            unclick();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(selected && selected->Movable()){
        float x = ((float)event->pos().x()-wExtraPixels/2)/windowSize*2-1;
        float y = (0-(float)event->pos().y()-hExtraPixels/2)/windowSize*2+1;
        dynamic_cast<MovableObject*>(selected)->setPosition(x, y);
    }
}

void MainWindow::giveKey(){
    c[11]->show();
}

//Note:
//c[0]->c[5] are books
void MainWindow::UpdateAnimation()//Used to check for any updates
{
    bool check = true;
    while(check && executeCommand != Nothing){
        check = false;
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
                dynamic_cast<BookBox*>(d[11])->open();
                d[13]->show();
                redShown = true;
                if(greenShown){
                    winnable = true;
                    check = true;
                    executeCommand = Dials;
                }
            }
            else{
                //If correct order is not selected
            }
            for(int i = 0; i < 6; i++){
                dynamic_cast<Book*>(c[i])->setSelected(0);
            }
        break;

        case 2://Mouse Cheese
            hasCheese = true;
        break;

        case 3://Key Box
            c[11]->hide();
            d[12]->show();
            greenShown = true;
            if(redShown){
                winnable = true;
                check = true;
                executeCommand = Dials;
            }
        break;

        case 4://Dials
        std::cout << "test";
            if(winnable){
                std::cout << "winnable";
                if(dynamic_cast<CodeInput*>(d[17])->getNum() == 9 &&
                   dynamic_cast<CodeInput*>(d[18])->getNum() == 12 &&
                    dynamic_cast<CodeInput*>(d[19])->getNum() == 3){
                    d[20]->show();
                }
            }
        break;
        case 101: //button 1 (TV Button)
            d[8]->toggleShow();
            break;
        }
        if(!check){
            executeCommand = Nothing;
        }
    }
    if(time < 100){
        time++;
    }
    else{
        time = 0;
    }
    if (time%6 == 0){
        dynamic_cast<Mouse*>(c[7])->move();
    }

    if(hasCheese){
        Mouse* m = dynamic_cast<Mouse*>(c[7]);
        int p = (int)m->getPosition();
        if(p == 0){//Mouse inside hole
            if(!mouseGone){
                c[10]->hide();
                if(m->getWaitTime()==100){
                    giveKey();
                    mouseGone = true;
                }
            }
        }
        else if(p == 1){//Left
            dynamic_cast<MovableObject*>(c[10])->setPosition(m->getX()-0.07, m->getY()+0.05);
        }
        else if(p == 2){//upLeft
            dynamic_cast<MovableObject*>(c[10])->setPosition(m->getX()+0.05, m->getY()+0.07);
        }

    }

    this->update();
}




