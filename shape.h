#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>
#include <QPoint>


class Shape
{
public:
    Shape();
    enum Code{Line,Rect,Ellipse,RoundRect,Pie};

    void setStart(QPoint s);
    void setEnd(QPoint e);

    QPoint startPoint();
    QPoint endPoint();

    void virtual paint(QPainter &painter) = 0;

protected:
    QPoint start;
    QPoint end;

};

#endif // SHAPE_H
