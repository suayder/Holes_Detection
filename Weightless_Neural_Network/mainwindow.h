#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <conversion.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QActionGroup>


//**** Libraryes to Json manipulation********

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>

//***********************************

#include "originimagemanipulation.h"
#include "eventmouseclass.h"


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



private slots:
    void on_imageList_activated(const QModelIndex &index);

    void mouse_is_clicked();
    void mouse_Move();
    void mouse_Release();

    void on_ButtonInputRamBits_clicked();


    void on_StartTrain_clicked();
    void keyReleaseEvent(QKeyEvent *ev);

    void on_Salve_DBF_triggered();

private:
    Ui::MainWindow *ui;
    QDir directoyimages;
    QPixmap *imagePixmap;
    originImageManipulation *imageinput;
    Conversion convertimages;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectToDraw;
    QVector<QGraphicsRectItem*> rects;

    QJsonDocument SaveInfo;   
    QFile file;
    int current;

    QPoint originPoint;
    QPoint endPoint;

    int auxWidth1, auxHeight1, auxWidth2, auxHeight2; // this is to be auxiliary in the rectangle move
    bool auxTomove, auxToSelect;

};

#endif // MAINWINDOW_H
