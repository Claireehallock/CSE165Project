
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
};

class ClickableObject : public DrawableObject{//Abstract class for all objects that can be interacted with
public:
    virtual void press() = 0;
    virtual void release() = 0;
};

class Background : public DrawableObject{
public:
    Background(){
        depth = -0.90;
        shown = TRUE;
    }
    void paint(){
        glColor3f(1.0f, 0.85f, 0.51f);
        glBegin(GL_QUADS);
        glVertex3f(-1, -1, depth);
        glVertex3f(1, -1, depth);
        glVertex3f(1, 1, depth);
        glVertex3f(-1, 1, depth);
        glEnd();

        glColor3f(0.96f, 0.4f, 0.28f);
        glBegin(GL_QUADS);
        glVertex3f(-1, -1, depth);
        glVertex3f(1, -1, depth);
        glVertex3f(1, -0.6, depth);
        glVertex3f(-1, -0.6, depth);
        glEnd();
    }
};

#endif // OBJECTS_H
