
#include "mainwindow.h"

#include <QApplication>

int Book::numSelected = 0;
int Button::numButtons = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Add "Background" (1 Nonclickable Object) d[0]
    Background* B = new Background();
    w.addObject(B);

    //Add books to shelf (6 Clickable Objects) d[1] c[0]
    Book* b0 = new Book(-0.85, 0.5, 0.16, 0, 0, 1);//Blue book
    w.addObject(b0);
    Book* b1 = new Book(-0.79, 0.5, 0.15, 1, 0, 0);//Red book
    w.addObject(b1);
    Book* b2 = new Book(-0.715, 0.5, 0.18, 1, 1, 0);//Yellow book
    w.addObject(b2);
    Book* b3 = new Book(-0.65, 0.5, 0.14, 1, 1, 1);//White book
    w.addObject(b3);
    Book* b4 = new Book(-0.575, 0.5, 0.12, 0, 0.8, 0);//Green book
    w.addObject(b4);
    Book* b5 = new Book(-0.5, 0.5, 0.15, 0.7, 0, 1);//Purple book
    w.addObject(b5);

    //Add tv button (1 Clickable Object) d[7] c[6]
    Button* tvButton = new Button(0.05, 0.4, 0.05, 0.025);//Button to toggle TV
    w.addObject(tvButton);

    //Add screen (1 Nonclickable Object) d[8]
    Screen* screen = new Screen();//TV screen
    w.addObject(screen);

    //Add mouse (1 Clickable Object) d[9] c[7]
    Mouse* mouse = new Mouse();//mouse
    w.addObject(mouse);

    //Add cheese (1 Clickable Object) d[10] c[8]
    Cheese* cheese = new Cheese(-0.55, 0, 0.1, 0.1);//cheese
    w.addObject(cheese);

    //Add key (1 Clickable Object) d[11] c[9]
    Key* key = new Key(-0.15, -0.65);//key
    w.addObject(key);

    //Add KeyBox (1 Clickable Object) d[12] c[10]
    KeyBox* box1 = new KeyBox(-0.7, 0.2, 0.35, 0.25);//key
    w.addObject(box1);

    //Add BookBox (1 Clickable Object) d[13] c[11]
    BookBox* box2 = new BookBox(-0.7, -0.4, 0.2, 0.2);//key
    w.addObject(box2);


    w.setTitle("CSE165Project");
    w.resize(640, 640);
    w.show();

    return a.exec();
}
