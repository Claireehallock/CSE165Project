
#ifndef OBJECTS_H
#define OBJECTS_H

#include <QObject>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/GLU.h>
#include <climits>
#include <iostream>

//Abstract methods: void paint()
class DrawableObject : public QObject{//Abstract class for all visible objects
protected:
    float depth;
    bool shown = true;
public:
    virtual void paint() = 0;

    virtual int compareTo(DrawableObject* a){
        if (depth > a->getDepth())
            return 1;
        else if (a->getDepth() > a->getDepth())
            return -1;
        else
            return 0;
    }

    float getDepth(){
        return depth;
    }

    void setDepth(float d){
        depth = d;
    }

    virtual bool Clickable(){
        return false;
    }

    virtual bool Movable(){
        return false;
    }

    virtual void show(){
        shown = true;
    }

    virtual void hide(){
        shown = false;
    }

    virtual void toggleShow(){
        if (shown){
            shown = false;
        }
        else{
            shown = true;
        }
    }
};

//Abstract methods: bool inside()
class ClickableObject : public DrawableObject{//Abstract class for all objects that can be interacted with
protected:
    bool pressed;
public:
    virtual int press(){
        pressed = true;
        return 0;
    }; //Returns the an int representing if something needs to happen
    virtual void release(){
        pressed = false;
    };

    virtual bool inside(float x1, float y1) = 0;

    virtual bool Clickable(){
        return true;
    }
};

class MovableObject : public ClickableObject{
protected:
    float x;
    float y;

    float xSet;//Default spot for object to return to
    float ySet;

    bool selected;

public:
    virtual int press(){
        pressed = true;
        return 0;
    };

    virtual void drop(){
        selected = false;
        x = xSet;
        y = ySet;
    }

    virtual void setPosition(float x1, float y1){
        x = x1;
        y = y1;
    }

    virtual bool Movable(){
        return true;
    }

    virtual bool isCheese(){
        return false;
    }

    virtual bool isKey(){
        return false;
    }
};

class Background : public DrawableObject{
public:
    Background(){
        depth = -0.90;
        shown = TRUE;
    }
    void paint(){
        //wall
        glColor3f(1.0f, 0.85f, 0.51f);
        glBegin(GL_QUADS);
            glVertex3f(-1, -1, depth);
            glVertex3f(1, -1, depth);
            glVertex3f(1, 1, depth);
            glVertex3f(-1, 1, depth);
        glEnd();

        //Carpet
        glColor3f(0.96f, 0.4f, 0.28f);
        glBegin(GL_QUADS);
            glVertex3f(-1, -1, depth);
            glVertex3f(1, -1, depth);
            glVertex3f(1, -0.6, depth);
            glVertex3f(-1, -0.6, depth);
        glEnd();

        //Main part of Bookshelf
        glColor3f(0.69f, 0.43f, 0.035f);
        glBegin(GL_QUADS);
            glVertex3f(-0.9, 0.8, depth);
            glVertex3f(-0.2, 0.8, depth);
            glVertex3f(-0.2, -0.75, depth);
            glVertex3f(-0.9, -0.75, depth);
        glEnd();

        //Bookshelf shelves
        glColor3f(0.53f, 0.33f, 0.027f);
        glBegin(GL_QUADS);//Highest Shelf
            glVertex3f(-0.85, 0.75, depth);
            glVertex3f(-0.25, 0.75, depth);
            glVertex3f(-0.25, 0.5, depth);
            glVertex3f(-0.85, 0.5, depth);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3f(-0.85, 0.45, depth);
            glVertex3f(-0.25, 0.45, depth);
            glVertex3f(-0.25, 0.2, depth);
            glVertex3f(-0.85, 0.2, depth);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3f(-0.85, 0.15, depth);
            glVertex3f(-0.25, 0.15, depth);
            glVertex3f(-0.25, -0.1, depth);
            glVertex3f(-0.85, -0.1, depth);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3f(-0.85, -0.15, depth);
            glVertex3f(-0.25, -0.15, depth);
            glVertex3f(-0.25, -0.4, depth);
            glVertex3f(-0.85, -0.4, depth);
        glEnd();
        glBegin(GL_QUADS);//Lowest Shelf
            glVertex3f(-0.85, -0.45, depth);
            glVertex3f(-0.25, -0.45, depth);
            glVertex3f(-0.25, -0.7, depth);
            glVertex3f(-0.85, -0.7, depth);
        glEnd();

        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);//Final Box
            glVertex3f(-0.75, -0.5, depth);
            glVertex3f(-0.35, -0.5, depth);
            glVertex3f(-0.35, -0.7, depth);
            glVertex3f(-0.75, -0.7, depth);
         glEnd();

        //Plate for cheese
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
            glVertex3f(-0.65, -0.1, depth);
            glVertex3f(-0.45, -0.1, depth);
            glVertex3f(-0.35, -0.05, depth);
            glVertex3f(-0.75, -0.05, depth);
        glEnd();

        //Cabinet for TV
        glColor3f(0.69f, 0.43f, 0.035f);
        glBegin(GL_QUADS);
            glVertex3f(-0.1, -0.2, depth);
            glVertex3f(0.9, -0.2, depth);
            glVertex3f(0.9, -0.75, depth);
            glVertex3f(-0.1, -0.75, depth);
        glEnd();

        //Cabinet shelves
        glColor3f(0.62f, 0.38f, 0.05f);
        glBegin(GL_QUADS);
            glVertex3f(-0.05, -0.25, depth);
            glVertex3f(0.85, -0.25, depth);
            glVertex3f(0.85, -0.45, depth);
            glVertex3f(-0.05, -0.45, depth);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3f(-0.05, -0.5, depth);
            glVertex3f(0.85, -0.5, depth);
            glVertex3f(0.85, -0.7, depth);
            glVertex3f(-0.05, -0.7, depth);
        glEnd();

        //TV
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_QUADS);//Base
            glVertex3f(0.1, -0.2, depth);
            glVertex3f(0.15, -0.125, depth);
            glVertex3f(0.65, -0.125, depth);
            glVertex3f(0.7, -0.2, depth);
        glEnd();
        glBegin(GL_QUADS);//Connection
            glVertex3f(0.35, -0.125, depth);
            glVertex3f(0.35, -0.075, depth);
            glVertex3f(0.45, -0.075, depth);
            glVertex3f(0.45, -0.125, depth);
        glEnd();
        glBegin(GL_QUADS);//Screen Container
            glVertex3f(0.0, -0.075, depth);
            glVertex3f(0.0, 0.4, depth);
            glVertex3f(0.8, 0.4, depth);
            glVertex3f(0.8, -0.075, depth);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);//Screen
            glVertex3f(0.05, -0.025, depth);
            glVertex3f(0.05, 0.35, depth);
            glVertex3f(0.75, 0.35, depth);
            glVertex3f(0.75, -0.025, depth);
        glEnd();

        //Mouse holes
        glBegin(GL_QUADS);//Mouse hole 1
            glVertex3f(-0.18, -0.6, depth);
            glVertex3f(-0.18, -0.55, depth);
            glVertex3f(-0.12, -0.55, depth);
            glVertex3f(-0.12, -0.6, depth);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3f(-0.18, -0.55, depth);
            glVertex3f(-0.17, -0.52, depth);
            glVertex3f(-0.13, -0.52, depth);
            glVertex3f(-0.12, -0.55, depth);
        glEnd();

        glBegin(GL_QUADS);//Mouse hole 2
            glVertex3f(-0.83, 0.8, depth);
            glVertex3f(-0.83, 0.85, depth);
            glVertex3f(-0.77, 0.85, depth);
            glVertex3f(-0.77, 0.8, depth);
        glEnd();
        glBegin(GL_QUADS);
            glVertex3f(-0.83, 0.85, depth);
            glVertex3f(-0.82, 0.88, depth);
            glVertex3f(-0.78, 0.88, depth);
            glVertex3f(-0.77, 0.85, depth);
        glEnd();
    }
};

class Book : public ClickableObject{
protected:
    float x;
    float y;
    float height;
    float r;
    float g;
    float b;

    int selected;

public:
    static int numSelected;

    Book(){
        x = 0;
        y = 0;
        height = 0;
        r = 0;
        g = 0;
        b = 0;
        pressed = false;
        selected = 0;
    }

    Book(float x1, float y1, float h1, float r1, float g1, float b1){
        x = x1;
        y = y1;
        height = h1;
        r = r1;
        g = g1;
        b = b1;
        pressed = false;
        selected = 0;
    }

    ~Book(){
        //
    }

    void paint(){
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
            glVertex3f(x, y, depth);
            glVertex3f(x+0.05, y, depth);
            glVertex3f(x+0.05, y+height, depth);
            glVertex3f(x, y+height, depth);
        glEnd();

        if(selected>0){
            glColor3f(1, 1, 1);//Add page visibility
            glBegin(GL_QUADS);
                glVertex3f(x+0.01, y+height*4/5, depth);
                glVertex3f(x+0.04, y+height*4/5, depth);
                glVertex3f(x+0.04, y+height, depth);
                glVertex3f(x+0.01, y+height, depth);
            glEnd();
            glColor3f(0, 0, 0);//seam
            glBegin(GL_LINES);
                glVertex3f(x+0.00, y+height*7/10, depth);
                glVertex3f(x+0.05, y+height*7/10, depth);
            glEnd();

            glBegin(GL_LINES);//Page Lines
                glVertex3f(x+0.015, y+height, depth);
                glVertex3f(x+0.015, y+height*4/5, depth);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(x+0.02, y+height, depth);
                glVertex3f(x+0.02, y+height*4/5, depth);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(x+0.025, y+height, depth);
                glVertex3f(x+0.025, y+height*4/5, depth);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(x+0.03, y+height, depth);
                glVertex3f(x+0.03, y+height*4/5, depth);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(x+0.035, y+height, depth);
                glVertex3f(x+0.035, y+height*4/5, depth);
            glEnd();
        }
    }

    int press(){
        if(selected == 0){
            if(numSelected >= 0){
                numSelected++;
                selected = numSelected;
            }
        }
        pressed =true;
        if(numSelected >= 6){
            numSelected = 0;
            return 1;
        }
        return 0;
    }

    void release(){
        pressed = false;
    }

    bool inside(float x1, float y1){
        if (shown){
            if((x1 >= x) && (x1<=x+0.05) && (y1>=y) && (y1<=y+height)){
                return true;
            }
        }
        return false;
    }

    void setColor(){
        r = 0;
        b = 0;
        g = 0;
    }

    int getSelected(){
        return selected;
    }

    void setSelected(int num){
        selected = num;
    }
};

class Button : public ClickableObject{
    float x;
    float y;
    float width;
    float height;
    int id;

public:
    static int numButtons;

    Button(){
        x=0;
        y=0;
        width=0;
        height=0;
        pressed=FALSE;
        numButtons++;
        id = numButtons;
    }

    Button(float x1, float y1, float w, float h){
        x=x1;
        y=y1;
        width=w;
        height=h;
        pressed=FALSE;
        numButtons++;
        id = numButtons;
    }

    ~Button(){}

    void paint(){

        if(!pressed){
            glColor3f(0, 0, 0);
            glBegin(GL_QUADS);//Full button
            glVertex3f(x, y, depth);
            glVertex3f(x+width, y, depth);
            glVertex3f(x+width, y+height, depth);
            glVertex3f(x, y+height, depth);
            glEnd();
        }
        else{
            glColor3f(0, 0, 0);
            glBegin(GL_QUADS);//Half button
            glVertex3f(x, y, depth);
            glVertex3f(x, y+height/2, depth);
            glVertex3f(x+width, y+height/2, depth);
            glVertex3f(x+width, y, depth);
            glEnd();
        }

    }

    int press(){
        pressed = true;
        return 100+id;
    }

    bool inside(float x1, float y1){
        if(shown){
            if((x1 >= x) && (x1<=x+width) && (y1>=y) && (y1<=y+height)){
                return true;
            }
        }
        return false;
    }
};

class Screen : public DrawableObject{
public:
    Screen(){
        shown = false;
    };

    ~Screen(){};

    void paint(){
        if(shown){
            float i = 0.1;
            glColor3f(0, 0.8, 0);
            glBegin(GL_QUADS);//Green
            glVertex3f(i, -0.025, depth);
            glVertex3f(i, 0.35, depth);
            glVertex3f(i+0.1, 0.35, depth);
            glVertex3f(i+0.1, -0.025, depth);
            glEnd();

            i+=0.1;
            glColor3f(1, 0, 0);
            glBegin(GL_QUADS);//Red
            glVertex3f(i, -0.025, depth);
            glVertex3f(i, 0.35, depth);
            glVertex3f(i+0.1, 0.35, depth);
            glVertex3f(i+0.1, -0.025, depth);
            glEnd();

            i+=0.1;
            glColor3f(0, 0, 1);
            glBegin(GL_QUADS);//Blue
            glVertex3f(i, -0.025, depth);
            glVertex3f(i, 0.35, depth);
            glVertex3f(i+0.1, 0.35, depth);
            glVertex3f(i+0.1, -0.025, depth);
            glEnd();

            i+=0.1;
            glColor3f(0.7, 0, 1);
            glBegin(GL_QUADS);//Purple
            glVertex3f(i, -0.025, depth);
            glVertex3f(i, 0.35, depth);
            glVertex3f(i+0.1, 0.35, depth);
            glVertex3f(i+0.1, -0.025, depth);
            glEnd();

            i+=0.1;
            glColor3f(1, 1, 1);
            glBegin(GL_QUADS);//White
            glVertex3f(i, -0.025, depth);
            glVertex3f(i, 0.35, depth);
            glVertex3f(i+0.1, 0.35, depth);
            glVertex3f(i+0.1, -0.025, depth);
            glEnd();

            i+=0.1;
            glColor3f(1, 1, 0);
            glBegin(GL_QUADS);//Yellow
            glVertex3f(i, -0.025, depth);
            glVertex3f(i, 0.35, depth);
            glVertex3f(i+0.1, 0.35, depth);
            glVertex3f(i+0.1, -0.025, depth);
            glEnd();
        }
    }
};

class Mouse : public ClickableObject{//I decided to hardcode the start and end location of the mouse since I only plan on using 1
public:
    enum Pos{None=0, Left = 1, upLeft = 2};
private:
    Pos pos;

    float x;
    float y;

    bool cheeseSelected;
    bool stopped;

    int waitTime;

public:
    Mouse(){
        x = -0.2;
        y = -0.58;
        pos = upLeft;
        cheeseSelected = false;
        stopped = false;
        waitTime = 101;
    }

    void paint(){
        switch((int)pos){
        case 0:
            break;
        case 1://Left
            glColor3f(0.8, 0.8, 0.8);
            glBegin(GL_TRIANGLES);//Head
                glVertex3f(x, y, depth);
                glVertex3f(x-0.025, y+0.025, depth);
                glVertex3f(x, y+0.05, depth);
            glEnd();
            glBegin(GL_QUADS);//Body
                glVertex3f(x, y, depth);
                glVertex3f(x+0.075, y, depth);
                glVertex3f(x+0.075, y+0.05, depth);
                glVertex3f(x, y+0.05, depth);
            glEnd();
            glColor3f(1, 0.8, 1);
            glBegin(GL_TRIANGLES);//Tail
                glVertex3f(x+0.07, y+0.05, depth);
                glVertex3f(x+0.075, y+0.035, depth);
                glVertex3f(x+0.13, y+0.065, depth);
            glEnd();
            glBegin(GL_QUADS);//Ear
                glVertex3f(x+0.005, y+0.05, depth);
                glVertex3f(x+0.02, y+0.075, depth);
                glVertex3f(x+0.0325, y+0.07, depth);
                glVertex3f(x+0.03, y+0.05, depth);
            glEnd();
            glBegin(GL_TRIANGLES);//Nose
                glVertex3f(x-0.015, y+0.015, depth);
                glVertex3f(x-0.025, y+0.025, depth);
                glVertex3f(x-0.015, y+0.035, depth);
            glEnd();
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_QUADS);//Eye
                glVertex3f(x+0.00, y+0.035, depth);
                glVertex3f(x+0.005, y+0.04, depth);
                glVertex3f(x+0.01, y+0.035, depth);
                glVertex3f(x+0.005, y+0.03, depth);
            glEnd();
                break;
        case 2://upLeft
            glColor3f(0.8, 0.8, 0.8);
            glBegin(GL_TRIANGLES);//Head
                glVertex3f(x, y, depth);
                glVertex3f(x+0.025, y+0.025, depth);
                glVertex3f(x+0.05, y, depth);
            glEnd();
            glBegin(GL_QUADS);//Body
                glVertex3f(x, y, depth);
                glVertex3f(x, y-0.075, depth);
                glVertex3f(x+0.05, y-0.075, depth);
                glVertex3f(x+0.05, y, depth);
            glEnd();
            glColor3f(1, 0.8, 1);
            glBegin(GL_TRIANGLES);//Tail
                glVertex3f(x+0.05, y-0.07, depth);
                glVertex3f(x+0.035, y-0.075, depth);
                glVertex3f(x+0.065, y-0.13, depth);
            glEnd();
            glBegin(GL_QUADS);//Ear
                glVertex3f(x+0.05, y-0.005, depth);
                glVertex3f(x+0.075, y-0.02, depth);
                glVertex3f(x+0.07, y-0.0325, depth);
                glVertex3f(x+0.05, y-0.03, depth);
            glEnd();
            glBegin(GL_TRIANGLES);//Nose
                glVertex3f(x+0.015, y+0.015, depth);
                glVertex3f(x+0.025, y+0.025, depth);
                glVertex3f(x+0.035, y+0.015, depth);
            glEnd();
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_QUADS);//Eye
                glVertex3f(x+0.035, y, depth);
                glVertex3f(x+0.04, y-0.005, depth);
                glVertex3f(x+0.035, y-0.01, depth);
                glVertex3f(x+0.03, y-0.005, depth);
            glEnd();
                break;
        }
    }

    virtual int press(){
        pressed = true;
        if(cheeseSelected){
            stopped = true;
                return 2;
        }
        return 0;
    }

    void selectCheese(){
        cheeseSelected = true;
    }

    void unselectCheese(){
        cheeseSelected = false;
    }

    void move(){
        if(pos == upLeft){
            y+=0.01;
        }
        if(pos == Left){
            x-=0.01;
        }
        if(y >=0.8){
            pos = Left;
            y-=0.01;
        }
        if(x <=-0.8){
            pos = None;
            x = -0.2;
            y = -0.5;
            waitTime = 0;
        }
        if(waitTime < 100){
            waitTime++;
        }
        else if (waitTime == 100){
            pos = upLeft;
            waitTime = 101;
            if(stopped){
                pos = None;
            }
        }
    }

    bool inside(float x1, float y1){
        if(pos == Left){
            if((x1>=x-.025)&&(x1<=x+0.13)&&(y1>=y)&&(y1<=y+0.065)){
                return true;
            }
        }
        if(pos == upLeft){
            if((x1>=x)&&(x1<=x+0.065)&&(y1>=y-0.13)&&(y1<=y+0.025)){
                return true;
            }
        }
    return false;
    }

    Pos getPosition(){
        return pos;
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }

    int getWaitTime(){
        return waitTime;
    }
};

class Cheese : public MovableObject{
    float width;
    float height;

public:
    Cheese(float x1, float y1, float w, float h){
        xSet = x1;
        x=x1;
        ySet = y1;
        y=y1;
        width = w;
        height = h;
        shown = true;
    }

    ~Cheese(){}

    void paint(){
        if(shown){
            glColor3f(1, 1, 0);
            glBegin(GL_QUADS);//Main Cheese
                glVertex3f(x-width/2, y-height/2, depth);
                glVertex3f(x+width/2, y-height/2, depth);
                glVertex3f(x+width/2, y+height/2, depth);
                glVertex3f(x-width/2, y+height/2, depth);
            glEnd();
            glColor3f(1, 0.8, 0);
            glBegin(GL_QUADS);//Holes
                glVertex3f(x-width/4, y-height/4, depth);
                glVertex3f(x-width/8, y-height/8, depth);
                glVertex3f(x, y-height/4, depth);
                glVertex3f(x-width/8, y-height*3/8, depth);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(x+width/4, y+height/4, depth);
                glVertex3f(x+width/8, y+height/8, depth);
                glVertex3f(x, y+height/4, depth);
                glVertex3f(x+width/8, y+height*3/8, depth);
            glEnd();
        }
    }

    bool inside(float x1, float y1){
        if(shown){
            if((x1>=x-width/2)&&(x1<=x+width/2)&&(y1>=y-height/2)&&(y1<=y+height/2)){
                return true;
            }
        }
        return false;
    }

    bool isCheese(){
        return true;
    }
};

class Key : public MovableObject{
public:
    Key(float x1, float y1){
        xSet = x1;
        ySet=y1;
        x=x1;
        y=y1;
        shown = false;
    }

    void paint(){
        if(shown){
            glColor3f(1, 1, 0);
            glBegin(GL_QUADS);//main Body
                glVertex3f(x+0.005, y+0.015, depth);
                glVertex3f(x+0.005, y-0.025, depth);
                glVertex3f(x-0.005, y-0.025, depth);
                glVertex3f(x-0.005, y+0.015, depth);
            glEnd();
            glBegin(GL_QUADS);//Left part of Loop
                glVertex3f(x+0.005, y+0.015, depth);
                glVertex3f(x-0.01, y+0.035, depth);
                glVertex3f(x-0.02, y+0.035, depth);
                glVertex3f(x-0.005, y+0.015, depth);
            glEnd();
            glBegin(GL_QUADS);//Right part of Loop
                glVertex3f(x+0.005, y+0.015, depth);
                glVertex3f(x+0.02, y+0.035, depth);
                glVertex3f(x+0.01, y+0.035, depth);
                glVertex3f(x-0.005, y+0.015, depth);
            glEnd();
            glBegin(GL_QUADS);//Top part of Loop
                glVertex3f(x+0.02, y+0.035, depth);
                glVertex3f(x-0.02, y+0.035, depth);
                glVertex3f(x-0.02, y+0.045, depth);
                glVertex3f(x+0.02, y+0.045, depth);
            glEnd();
            glBegin(GL_QUADS);//prong
                glVertex3f(x+0.005, y-0.005, depth);
                glVertex3f(x+0.005, y-0.025, depth);
                glVertex3f(x+0.015, y-0.025, depth);
                glVertex3f(x+0.015, y-0.005, depth);
            glEnd();
        }
    }

    bool inside(float x1, float y1){
        if(shown){
            if(x1>=x-0.02 && x1<=x+0.02 && y1>=y-0.025 && y1<=y+0.045){
                return true;
            }
        }
        return false;
    }

    bool isKey(){
        return true;
    }
};

class LockedBox : public ClickableObject{
protected:
    float x;
    float y;
    float w;
    float h;

    bool opened;

public:
    LockedBox(){
        x = 0;
        y = 0;
        w = 0;
        h = 0;
        opened = false;
    }

    LockedBox(float x1, float y1, float w1, float h1){
        x = x1;
        y = y1;
        w = w1;
        h = h1;
        opened = false;
    }

    virtual void paint(){
        glColor3f(0.6, 0.6, 0.6);
        glBegin(GL_QUADS);//main Body
            glVertex3f(x+w, y, depth);
            glVertex3f(x+w, y+h, depth);
            glVertex3f(x, y+h, depth);
            glVertex3f(x, y, depth);
        glEnd();
        glColor3f(0.7, 0.7, 0.7);
        if(!opened){
            glBegin(GL_QUADS);//Door
                glVertex3f(x+w*9/10, y+h/10, depth);
                glVertex3f(x+w*9/10, y+h*9/10, depth);
                glVertex3f(x+w/10, y+h*9/10, depth);
                glVertex3f(x+w/10, y+h/10, depth);
            glEnd();
            glColor3f(0.6, 0.6, 0.6);
            glBegin(GL_QUADS);//Handle
                glVertex3f(x+w*.85, y+h*.55, depth);
                glVertex3f(x+w*.85, y+h*.45, depth);
                glVertex3f(x+w*.65, y+h*.45, depth);
                glVertex3f(x+w*.65, y+h*.55, depth);
            glEnd();
        }
        else{
            glBegin(GL_QUADS);//Opened Door
            glVertex3f(x-w/5, y+h/10, depth);
            glVertex3f(x-w/5, y+h*9/10, depth);
            glVertex3f(x+w/10, y+h*9/10, depth);
            glVertex3f(x+w/10, y+h/10, depth);
            glEnd();

            glColor3f(0.3, 0.3, 0.3);
            glBegin(GL_QUADS);//Inner Box
            glVertex3f(x+w*9/10, y+h/10, depth);
            glVertex3f(x+w*9/10, y+h*9/10, depth);
            glVertex3f(x+w/10, y+h*9/10, depth);
            glVertex3f(x+w/10, y+h/10, depth);
            glEnd();
        }
    }

    virtual bool inside(float x1, float y1){
        if (x1>=x && x1<=x+w && y1>=y && y1<=y+h){
            return true;
        }
        return false;
    }

    virtual int press()=0;

    bool isOpened(){
        return opened;
    }
};

class KeyBox : public LockedBox{
    bool keySelected;

public:
    KeyBox(float x1, float y1, float w1, float h1){
        x = x1;
        y = y1;
        w = w1;
        h = h1;
        opened = false;
    }

    int press(){
        pressed = true;
        if(keySelected){
            opened = true;
            return 3;
        }
        return 0;
    }

    void paint(){
        LockedBox::paint();
        if(!opened){
            glColor3f(0.1, 0.1, 0.1);
            glBegin(GL_QUADS);//Key Hole
                glVertex3f(x+w*.83, y+h*.33, depth);
                glVertex3f(x+w*.83, y+h*.4, depth);
                glVertex3f(x+w*.77, y+h*.4, depth);
                glVertex3f(x+w*.77, y+h*.33, depth);
            glEnd();
                glBegin(GL_QUADS);//Key Hole
                glVertex3f(x+w*.815, y+h*.33, depth);
                glVertex3f(x+w*.815, y+h*.25, depth);
                glVertex3f(x+w*.785, y+h*.25, depth);
                glVertex3f(x+w*.785, y+h*.33, depth);
                glEnd();
        }
    }

    void selectKey(){
        keySelected = true;
    }

    void unselectKey(){
        keySelected = false;
    }

};

class BookBox : public LockedBox{
public:
    BookBox(float x1, float y1, float w1, float h1){
        x = x1;
        y = y1;
        w = w1;
        h = h1;
        opened = false;
    }

    void open(){
        opened = true;
    }

    int press(){
        return 0;
    }
};

class Clock : public DrawableObject{
    float x;
    float y;
    float radius;
    float r;
    float g;
    float b;
    int time;

public:
    Clock(float x1, float y1, float radi1, int time1, float r1, float g1, float b1){
        x = x1;
        y = y1;
        radius = radi1;
        time1 %= 12;
        time = time1;
        r = r1;
        g = g1;
        b = b1;
    }

    void paint(){
        if(shown){
            glColor3f(r, g, b);//Colored Rim of Clock
            glBegin(GL_QUADS);//Top Right park of body
            glVertex3f(x, y, depth);
            glVertex3f(x-radius/2, y+0.866*radius, depth);
            glVertex3f(x+radius/2, y+0.866*radius, depth);
            glVertex3f(x+radius, y, depth);
            glEnd();
            glBegin(GL_QUADS);//Bottom Right park of body
            glVertex3f(x, y, depth);
            glVertex3f(x+radius, y, depth);
            glVertex3f(x+radius/2, y-0.866*radius, depth);
            glVertex3f(x-radius/2, y-0.866*radius, depth);
            glEnd();
            glBegin(GL_QUADS);//Left park of body
            glVertex3f(x, y, depth);
            glVertex3f(x-radius/2, y-0.866*radius, depth);
            glVertex3f(x-radius, y, depth);
            glVertex3f(x-radius/2, y+0.866*radius, depth);
            glEnd();

            glColor3f(1, 1, 1); //White Face of Clock
            glBegin(GL_QUADS);//Top Right park of body
            glVertex3f(x, y, depth);
            glVertex3f(x-radius/2*0.7, y+0.866*radius*0.7, depth);
            glVertex3f(x+radius/2*0.7, y+0.866*radius*0.7, depth);
            glVertex3f(x+radius*0.7, y, depth);
            glEnd();
            glBegin(GL_QUADS);//Bottom Right park of body
            glVertex3f(x, y, depth);
            glVertex3f(x+radius*0.7, y, depth);
            glVertex3f(x+radius/2*0.7, y-0.866*radius*0.7, depth);
            glVertex3f(x-radius/2*0.7, y-0.866*radius*0.7, depth);
            glEnd();
            glBegin(GL_QUADS);//Left park of body
            glVertex3f(x, y, depth);
            glVertex3f(x-radius/2*0.7, y-0.866*radius*0.7, depth);
            glVertex3f(x-radius*0.7, y, depth);
            glVertex3f(x-radius/2*0.7, y+0.866*radius*0.7, depth);
            glEnd();

            glColor3f(0, 0, 0); //Minute Hand
            glBegin(GL_QUADS);
            glVertex3f(x-0.005, y-0.005, depth);
            glVertex3f(x+0.005, y-0.005, depth);
            glVertex3f(x+0.005, y+0.866*radius*0.7, depth);
            glVertex3f(x-0.005, y+0.866*radius*0.7, depth);
            glEnd();

            switch(time){
            case 3:
                glBegin(GL_QUADS);
                glVertex3f(x, y-0.005, depth);
                glVertex3f(x, y+0.005, depth);
                glVertex3f(x+0.866*radius*0.5, y+0.005, depth);
                glVertex3f(x+0.866*radius*0.5, y-0.005, depth);
                glEnd();
                break;
            case 6:
                glBegin(GL_QUADS);
                glVertex3f(x-0.005, y, depth);
                glVertex3f(x+0.005, y, depth);
                glVertex3f(x+0.005, y-0.866*radius*0.5, depth);
                glVertex3f(x-0.005, y-0.866*radius*0.5, depth);
                glEnd();
                break;
            case 9:
                glBegin(GL_QUADS);
                glVertex3f(x, y-0.005, depth);
                glVertex3f(x, y+0.005, depth);
                glVertex3f(x-0.866*radius*0.5, y+0.005, depth);
                glVertex3f(x-0.866*radius*0.5, y-0.005, depth);
                glEnd();
                break;
            case 0:
                glBegin(GL_QUADS);
                glVertex3f(x-0.005, y, depth);
                glVertex3f(x+0.005, y, depth);
                glVertex3f(x+0.005, y+0.866*radius*0.5, depth);
                glVertex3f(x-0.005, y+0.866*radius*0.5, depth);
                glEnd();
                break;
            }
        }
    }
};

class CodeInput : public ClickableObject{
protected:
    int num;

    float x;
    float y;

    float radius;

    static int id;
    int thisId;

public:
    CodeInput(float x1, float y1){
        x = x1;
        y = y1;
        num=0;
        radius = 0.1;
        thisId = id;
        id++;
    }

    void paint(){

        glColor3f(0.4, 0.6, 0.6);
        glBegin(GL_QUADS);
        glVertex3f(x, y-radius*0.5, depth);
        glVertex3f(x-radius*0.5, y, depth);
        glVertex3f(x, y+radius*0.5, depth);
        glVertex3f(x+radius*0.5, y, depth);
        glEnd();


        switch(thisId){
        case 0:
        glColor3f(1, 0, 0);
        break;

        case 1:
        glColor3f(0, 1, 0);
        break;

        case 2:
        glColor3f(0, 0, 1);
        break;
        }

        switch(num){
        case 3:
            glBegin(GL_QUADS);
            glVertex3f(x, y-0.005, depth);
            glVertex3f(x, y+0.005, depth);
            glVertex3f(x+radius*0.5, y+0.005, depth);
            glVertex3f(x+radius*0.5, y-0.005, depth);
            glEnd();
            break;
        case 6:
            glBegin(GL_QUADS);
            glVertex3f(x-0.005, y, depth);
            glVertex3f(x+0.005, y, depth);
            glVertex3f(x+0.005, y-radius*0.5, depth);
            glVertex3f(x-0.005, y-radius*0.5, depth);
            glEnd();
            break;
        case 9:
            glBegin(GL_QUADS);
            glVertex3f(x, y-0.005, depth);
            glVertex3f(x, y+0.005, depth);
            glVertex3f(x-radius*0.5, y+0.005, depth);
            glVertex3f(x-radius*0.5, y-0.005, depth);
            glEnd();
            break;
        case 0:
            glBegin(GL_QUADS);
            glVertex3f(x-0.005, y, depth);
            glVertex3f(x+0.005, y, depth);
            glVertex3f(x+0.005, y+radius*0.5, depth);
            glVertex3f(x-0.005, y+radius*0.5, depth);
            glEnd();
            break;
        }
    }

    int press(){
        numInc();
        return 4;
    }


    void numInc(){
        num +=3;
        if (num >= 12)
            num = 0;
    }

    int getNum(){
        return num;
    }

    bool inside(float x1, float y1){
        if(x1>=x-radius*0.5&&x1<=x+radius*0.5&&y1>=y-radius*0.5&&y1<=y+radius*0.5){
            return true;
        }
        return false;
    }

};

class WinScreen : public DrawableObject{
public:
    WinScreen(){
        depth = 0.99;
    }

    void paint(){
        if(shown){
            glColor3f(0.5, 1, 1);
            glBegin(GL_QUADS);
                glVertex3f(-1, -1, depth);
                glVertex3f(-1, 1, depth);
                glVertex3f(1, 1, depth);
                glVertex3f(1, -1, depth);
            glEnd();
            glColor3f(1, 0.9, 0.3);
            glBegin(GL_QUADS);//Trophy Cup
                glVertex3f(-0.3, 0.4, depth);
                glVertex3f(0.3, 0.4, depth);
                glVertex3f(0.2, 0, depth);
                glVertex3f(-0.2, 0, depth);
            glEnd();
            glBegin(GL_QUADS);//Trophy Stem
                glVertex3f(-0.05, -0.3, depth);
                glVertex3f(0.05, -0.3, depth);
                glVertex3f(0.05, 0, depth);
                glVertex3f(-0.05, 0, depth);
            glEnd();
            glBegin(GL_QUADS);//Trophy Base
                glVertex3f(-0.15, -0.3, depth);
                glVertex3f(0.15, -0.3, depth);
                glVertex3f(0.2, -0.4, depth);
                glVertex3f(-0.2, -0.4, depth);
            glEnd();
        }
    }
};

#endif // OBJECTS_H
