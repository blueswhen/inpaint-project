#include "shape.h"

Shape::Shape()
{
}

void Shape::setStart(QPoint s)
{
    start = s;

}

void Shape::setEnd(QPoint e)
{

    end = e;
}

QPoint Shape::startPoint()
{
    return start;
}

QPoint Shape::endPoint()
{
    return end;
}
