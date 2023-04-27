
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Background* B = new Background();
    w.addObject(B);
    Book* b1 = new Book(-0.85, 0.5, 0.15, 0, 0, 1);//Blue book
    w.addObject(b1);
    Book* b2 = new Book(-0.8, 0.5, 0.13, 1, 0, 0);//Red book
    w.addObject(b2);
    w.setTitle("CSE165Project");
    w.resize(640, 640);
    w.show();

    return a.exec();
}
