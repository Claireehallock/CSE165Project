
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setTitle("CSE165Project");
    w.resize(640, 640);
    w.show();
    return a.exec();
}
