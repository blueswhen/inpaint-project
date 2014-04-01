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
    ui(new Ui::MainWindow) {
    this->setAttribute(Qt::WA_PaintOutsidePaintEvent);
    QToolBar *bar = this->addToolBar("Tools");
    QActionGroup *group = new QActionGroup(bar);
    ui->setupUi(this);
    pix = QPixmap(500,500);
    pix.fill(Qt::white);
    isDrawing = false;

    QAction *chooseAction = new QAction("Choose",bar);
    chooseAction->setToolTip(tr("Save."));
    chooseAction->setStatusTip(tr("Save."));
    chooseAction->setCheckable(true);

    group->addAction(chooseAction);
    bar->addAction(chooseAction);
    connect(chooseAction,SIGNAL(triggered()),this,SLOT(chooseBmp()));

    QAction *saveAction = new QAction("Save",bar);
    saveAction->setToolTip(tr("Save."));
    saveAction->setStatusTip(tr("Save."));
    saveAction->setCheckable(true);

    group->addAction(saveAction);
    bar->addAction(saveAction);
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveBmp()));
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        isDrawing = true;   
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons()&Qt::LeftButton) {
        endPoint = event->pos();
        update();
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        endPoint = event->pos();
        isDrawing = false;    
        update();
    }
}
void MainWindow::paintEvent(QPaintEvent *) {
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    QPainter painter(this);
    if(isDrawing) {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.fillRect (x,y,w,h, Qt::green );
        painter.drawPixmap(0,0,tempPix);
        pp.end();
    } else {
        QPainter pp(&pix);
        pp.fillRect (x,y,w,h, Qt::green );
        painter.drawPixmap(0,0,pix);
        pp.end();
    }
    painter.end();
}

void MainWindow::saveBmp() {
    pix.save("pix.bmp");
    inpainting test("pix.bmp");
    test.Process();
    pix.load("result.bmp");
    QPainter painter(this);
    QPainter pp(&pix);
    pp.fillRect (0,0,0,0, Qt::green );
    painter.drawPixmap(0,0,pix);
    pp.end();
}
void MainWindow::chooseBmp() {
    QString filename=QFileDialog::getOpenFileName(this,
                                                  tr("Open Image"),"",
                                                  tr("BMP(*.bmp);;JPG(*.jpg);;ALL files(*.*)"));
         if(filename.isEmpty()) {
             QMessageBox::information(this,
                                      tr("Open Image"),
                                      tr("Please select an image to open"));
             filename=QFileDialog::getOpenFileName(this,
                                                   tr("Open Image"),"",
                                                   tr("BMP(*.bmp);;JPG(*.jpg);;ALL files(*.*)"));
         }

         if(!(pix.load(filename))) {
             QMessageBox::information(this,
                                      tr("Unable to open the Image"),
                                      tr("Please select a valid image."));
            return;
          }
         QWidget::update();
}
MainWindow::~MainWindow() {
    delete ui;
}
