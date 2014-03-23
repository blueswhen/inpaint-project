#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mycanvas.h>
#include "paintwidget.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Mycanvas canvas;
    QPixmap pix;
        QPoint lastPoint;
        QPoint endPoint;
        QPixmap tempPix; //临时画布
        bool isDrawing;   //标志是否正在绘图
signals:
    void changeCurrentShape(Shape::Code);
private slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *);
    void saveActionTriggered();
    void chooseBmp();
    void saveBmp();
};

#endif // MAINWINDOW_H
