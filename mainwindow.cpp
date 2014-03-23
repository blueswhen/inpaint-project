#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QStatusBar>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inpainting.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setAttribute(Qt::WA_PaintOutsidePaintEvent);
    QToolBar *bar = this->addToolBar("Tools");
    QActionGroup *group = new QActionGroup(bar);
    ui->setupUi(this);
    //ui->graphicsView->setScene(&canvas );
    pix = QPixmap(500,500);
        pix.fill(Qt::white);
        pix.load(":/image/in.bmp");
        isDrawing = false;

        QAction *chooseAction = new QAction("Choose",bar);
            chooseAction->setToolTip(tr("Save."));
            chooseAction->setStatusTip(tr("Save."));
            chooseAction->setCheckable(true);

            group->addAction(chooseAction);
            bar->addAction(chooseAction);
            connect(chooseAction,SIGNAL(triggered()),this,
                        SLOT(chooseBmp()));

        QAction *saveAction = new QAction("Save",bar);
            saveAction->setToolTip(tr("Save."));
            saveAction->setStatusTip(tr("Save."));
            saveAction->setCheckable(true);

            group->addAction(saveAction);
            bar->addAction(saveAction);
            connect(saveAction,SIGNAL(triggered()),this,
                        SLOT(saveBmp()));
      /*       QLabel *statusMsg = new QLabel;       //set status bar
            statusBar()->addWidget(statusMsg);

            PaintWidget *paintWidget = new PaintWidget(this);
            setCentralWidget(paintWidget);
            connect(saveAction,SIGNAL(triggered()),this,
                        SLOT(saveActionTriggered()));

                connect(this,SIGNAL(changeCurrentShape(Shape::Code)),paintWidget,
                        SLOT(setCurrentShape(Shape::Code)));*/
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) //鼠标左键按下
    {
        lastPoint = event->pos();
        isDrawing = true;   //正在绘图
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
    {
        endPoint = event->pos();
        update();
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) //鼠标左键释放
    {
        endPoint = event->pos();
        isDrawing = false;    //结束绘图
        update();
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{

    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;

    QPainter painter(this);
    if(isDrawing)     //如果正在绘图
    {
        tempPix = pix;    //将以前pix中的内容复制到tempPix中，这样实现了交互绘图
        QPainter pp(&tempPix);
      //  pp.drawRect(x,y,w,h);
        pp.fillRect (x,y,w,h, Qt::green );
        painter.drawPixmap(0,0,tempPix);
    }
    else
    {
        QPainter pp(&pix);
        //pp.drawRect(x,y,w,h);
          pp.fillRect (x,y,w,h, Qt::green );
        painter.drawPixmap(0,0,pix);
    }
}
/*****************/
void MainWindow::saveActionTriggered()
{
    emit changeCurrentShape(Shape::Pie);
}
void MainWindow::saveBmp()
{
    pix.save("pix.bmp");
    inpainting test("pix.bmp");
    test.process();
   /* QPainter painter(this);
    if(isDrawing)     //如果正在绘图
    {
        tempPix = pix;    //将以前pix中的内容复制到tempPix中，这样实现了交互绘图
        QPainter pp(&tempPix);
      //  pp.drawRect(x,y,w,h);
        pix.save("pix.bmp");
        inpainting test("pix.bmp");
                test.process();
    }
    else
    {
        QPainter pp(&pix);
        //pp.drawRect(x,y,w,h);
        pix.save("pix.bmp");
        inpainting test("pix.bmp");
                test.process();
    }*/
}
void MainWindow::chooseBmp()
{

}
MainWindow::~MainWindow()
{
    delete ui;
}
