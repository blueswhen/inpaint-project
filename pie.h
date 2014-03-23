#ifndef PIE_H
#define PIE_H

#include "shape.h"

class Pie : public Shape
{
public:
    Pie();
    void paint(QPainter &painter);
};

#endif // PIE_H
