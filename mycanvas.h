#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QGraphicsScene>
#include<QGraphicsEllipseItem>
#include<QGraphicsPixmapItem>
class Mycanvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Mycanvas(QObject *parent = 0);

signals:

public slots:
protected:
QGraphicsEllipseItem ellipseItem;
QGraphicsTextItem TextItem;
QGraphicsPixmapItem imageItem;
    QPixmap image;
};

#endif // MYCANVAS_H
