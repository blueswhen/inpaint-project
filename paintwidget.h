#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QList>

#include "shape.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
     PaintWidget(QWidget *parent = 0);



public slots:

     void setCurrentShape(Shape::Code s)
     {
        if(s != currShapeCode)
        {
            currShapeCode = s;
        }

     }

 protected:
     void paintEvent(QPaintEvent *);
     void mousePressEvent(QMouseEvent *);
     void mouseMoveEvent(QMouseEvent *);
     void mouseReleaseEvent(QMouseEvent *);

 private:
     Shape::Code currShapeCode;
     Shape *shape;
     bool perm;
     QList<Shape *> shapeList;

};

#endif // PAINTWIDGET_H
