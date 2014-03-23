#include "pie.h"

Pie::Pie()
{
}

void Pie::paint(QPainter &painter)
{

    painter.drawPie(start.x(),start.y(),end.x()-start.x(),end.y()-start.y(),60*16,270*16);
}
