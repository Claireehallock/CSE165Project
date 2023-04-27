
#ifndef OBJECTS_H
#define OBJECTS_H

#include <QObject>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/GLU.h>
#include <climits>

class DrawableObject : public QObject{//Abstract class for all visible objects
protected:
    float depth;
    bool shown;
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
};

class ClickableObject : public DrawableObject{//Abstract class for all objects that can be interacted with
protected:
    bool pressed;
public:
    virtual void press() = 0;
    virtual void release() = 0;
    virtual bool inside(double x, double y) = 0;

    virtual bool Clickable(){
        return true;
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

public:
    Book(){
        x = 0;
        y = 0;
        height = 0;
        r = 0;
        g = 0;
        b = 0;
        pressed = false;
    }

    Book(float x1, float y1, float h1, float r1, float g1, float b1){
        x = x1;
        y = y1;
        height = h1;
        r = r1;
        g = g1;
        b = b1;
        pressed = false;
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
    }

    void press(){
        pressed =true;
        height -=0.05;
    }

    void release(){
        pressed = false;
        height +=0.05;
    }

    bool inside(double x1, double y1){
        if((x1 >= x) && (x1<=x+0.05) && (y1>=y) && (y1<=y+height)){
            return true;
        }
        return false;
    }
};

#endif // OBJECTS_H
