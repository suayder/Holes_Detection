#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//TO DO: See on the action start tracker cliked function, there have a description what i have to do.

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
#include <QThread>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMap>
#include <QRgb>

//**** Libraryes to Json manipulation********

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>

//*************** Classes ********************

#include "eventmouseclass.h"
#include "discriminator.h"
#include "conversion.h"
#include "imagejson.h"
#include "rankwisard.h"
#include "originimagemanipulation.h"
#include "ssearch.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow, private Imagejson
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setListDirectoryImages();

    void resetAllValues();

    void set_BottomRight_topLeft_Points(QPoint, QPoint);

    void set_image_to_tracker(int row);


private slots:
    void on_imageList_activated(const QModelIndex &index);

    void on_actionLoad_Image_triggered();

    void mouse_is_clicked();
    void mouse_Move();
    void mouse_Release();

    void on_start_clicked();

    void on_stop_clicked();

    void keyReleaseEvent(QKeyEvent *ev);

    void on_Salve_json_triggered(); //change place to another file

    void on_actionNew_triggered();

    void on_trainig_clicked();
    
    void on_operation_clicked();

    void on_tracker_clicked();

    void on_actionSet_a_Size_triggered();

    void on_actionNew_Descriptor_triggered();

    void on_lineInputBits_textEdited(const QString &arg1);

    void on_actionSave_new_WNN_triggered();

    void on_Load_WNN_triggered();

    void on_bottonSetInputs_clicked();

    void on_actionStartTracker_triggered();

    void on_actionTracker_triggered();

    void on_actionTrain_triggered();

    void on_actionTracker_Image_triggered();


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

    Discriminator *network;
    RankWisard *wizardNetwork;


    QJsonDocument SaveInfo;
    QFile file;
    int current; //current row of the image list

    // Points of the current rect
    QPoint originPoint; //Top Left
    QPoint endPoint; //Botton Right

    int auxWidth1, auxHeight1, auxWidth2, auxHeight2; // this is to be auxiliary in the rectangle move
    int auxUpdateRect; //Auxiliary when is moving the rect end tell what is the rectangle in original image
    bool auxTomove, auxToSelect;

    bool flagToOperating;

    QThread thread;

};

#endif // MAINWINDOW_H
