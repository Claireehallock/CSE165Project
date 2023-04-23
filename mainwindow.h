
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>



class MainWindow : public QOpenGLWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
