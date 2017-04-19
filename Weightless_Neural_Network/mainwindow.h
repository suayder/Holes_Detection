#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <conversion.h>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QObject>
#include <QDialog>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QActionGroup>

#include "originimagemanipulation.h"
#include "eventmouseclass.h"

//#include "eventmouseclassscene.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setListDirectoryImages();
    //void mousePres();


private slots:
    void on_imageList_activated(const QModelIndex &index);
    void mouse_current_position();
    void mouse_Release();
    void mouse_Move();

    void on_ButtonInputRamBits_clicked();


private:
    Ui::MainWindow *ui;
    QDir directoyimages;
    QPixmap *imagePixmap;
    originImageManipulation *imageinput;
    Conversion convertimages;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectToDraw;
    QPoint originPoint;

};

#endif // MAINWINDOW_H
