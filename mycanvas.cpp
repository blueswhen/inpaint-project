#include "mycanvas.h"

Mycanvas::Mycanvas(QObject *parent) :
    QGraphicsScene(parent),image(":/image/in.bmp")
{
ellipseItem.setRect(80, 50, 100, 80);

imageItem.setPixmap(image);  //将图片文件添加进去  新增加的
imageItem.setPos(0,0);     //设置坐标点          新增加的
addItem(&imageItem);     //将图片添加到数据结构里面去  新增加的
}
