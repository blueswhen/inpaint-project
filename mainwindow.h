#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QList>
#include <QPainter>
#include <QSizePolicy>
#include <QPaintEvent>
#include <QtGui>
#include <QPoint>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QPixmap pix;
  QPoint lastPoint;
  QPoint endPoint;
  QPixmap tempPix; 
  bool isDrawing;
 private slots:
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void chooseBmp();
  void saveBmp();
};

#endif // MAINWINDOW_H
