
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Objects.h"
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/GLU.h>
#include <iostream>


class MainWindow : public QOpenGLWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addObject(DrawableObject* o){
        o->setDepth((float)d.size()/100+0.01);
        d.push_back(o);
        std::cout <<"depth: "<< o->getDepth()<<std::endl;
        if(o->Clickable()){
            c.push_back(dynamic_cast<ClickableObject*>(o));
        }
    }

    void click(float x, float y);
    void unclick();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
//    void mouseMoveEvent(QMouseEvent* event) override;

public slots:
    void UpdateAnimation();

private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;

    QTimer* timer;

    std::vector<DrawableObject*> d;
    std::vector<ClickableObject*> c;

    ClickableObject* selected;

    int windowSize;
    int wExtraPixels = 0;
    int hExtraPixels = 0;

    bool mousePressed;

};

#endif // MAINWINDOW_H
