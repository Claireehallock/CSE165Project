
#ifndef OBJECTS_H
#define OBJECTS_H

#include <QObject>

class DrawableObject : public QObject{//Abstract class for all visible objects
protected:
    float depth;
public:
    virtual void paint();

    int compareTo(DrawableObject a){
        if (depth > a.depth)
            return 1;
        else if (a.depth > depth)
            return -1;
        else
            return 0;
    }
};

class ClickableObject : public DrawableObject{//Abstract class for all objects that can be interacted with
public:
    virtual void press();
    virtual void release();
};



#endif // OBJECTS_H
