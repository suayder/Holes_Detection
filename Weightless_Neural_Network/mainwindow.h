#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//**********Qt Creator Libraryes ***********

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QActionGroup>
#include <QSize>
#include <QMessageBox>

//**********C++ Libraryes*****************

#include <cstdlib>

//**** Libraryes to Json manipulation********

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>

//*************** Classes ********************

#include "originimagemanipulation.h"
#include "eventmouseclass.h"
#include "descriptor.h"
#include "conversion.h"



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

    void resetAllValues();

    void set_BottomRight_topLeft_Points(QPoint, QPoint);



private slots:
    void on_imageList_activated(const QModelIndex &index);

    void mouse_is_clicked();
    void mouse_Move();
    void mouse_Release();

    void on_start_clicked();

    void on_stop_clicked();

    void keyReleaseEvent(QKeyEvent *ev);

    void on_Salve_DBF_triggered();

    void on_actionNew_triggered();

    void on_trainig_clicked();
    
    void on_operation_clicked();

    void on_actionSet_a_Size_triggered();

    void on_actionNew_Descriptor_triggered();

    void on_lineInputBits_textEdited(const QString &arg1);

    void on_actionSave_new_WNN_triggered();

    void on_Load_WNN_triggered();

    void on_bottonSetInputs_clicked();

private:
    Ui::MainWindow *ui;

    QDir directoyimages;
    QPixmap *imagePixmap;
    originImageManipulation *imageinput;
    Conversion convertimages; //Class Conversion
    QGraphicsScene *scene;
    QGraphicsRectItem *rectToDraw;
    QVector<QGraphicsRectItem*> rects;
    QSize sizeOfRect;

    Descriptor *network;

    QJsonDocument SaveInfo;
    QFile file;
    int current; //current row of the image list

    // Points of the current rect
    QPoint originPoint; //Top Left
    QPoint endPoint; //Botton Right

    int auxWidth1, auxHeight1, auxWidth2, auxHeight2; // this is to be auxiliary in the rectangle move
    bool auxTomove, auxToSelect;

    bool flagToOperating;

};

#endif // MAINWINDOW_H
