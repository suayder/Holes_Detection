#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <highgui.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->imageinput = NULL;
    this->auxTomove = false;
    this->auxToSelect = true;
    this->directoyimages = QDir("../Weightless_Neural_Network/dataBaseImages");
    this->setListDirectoryImages();
    connect(ui->graphicsView, SIGNAL(Mouse_Pressed()), SLOT(mouse_is_clicked()));
    connect(ui->graphicsView, SIGNAL(Mouse_Move()), SLOT(mouse_Move()));
    connect(ui->graphicsView, SIGNAL(Mouse_Released()), SLOT(mouse_Release()));

    this->scene = NULL;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setListDirectoryImages(){ //List all archives in qlistview

    QFileInfoList files = this->directoyimages.entryInfoList();
    foreach (QFileInfo file, files) {
        if(file.isFile()){
            ui->imageList->addItem(file.fileName());
        }
    }
}

void MainWindow::on_imageList_activated(const QModelIndex &index)
{
    this->current = ui->imageList->currentRow();
    this->imageinput = new originImageManipulation();
    this->imageinput->imageRead((this->directoyimages.filePath(ui->imageList->currentItem()->text())).toStdString());
    this->imageinput->thresholding();

    this->imagePixmap = new QPixmap((this->directoyimages.filePath(ui->imageList->currentItem()->text())));
    this->scene = new QGraphicsScene(this);
    *this->imagePixmap = this->imagePixmap->scaledToWidth(ui->graphicsView->width(), Qt::SmoothTransformation);
    this->scene->addPixmap(*this->imagePixmap);
    ui->graphicsView->setScene(scene);
}

void MainWindow::mouse_is_clicked() //If was pressed
{    

    this->rectToDraw = NULL;

    foreach (QGraphicsRectItem *rect, this->rects) {
       if(rect->isUnderMouse()){
           this->rectToDraw = rect;
           this->originPoint = this->rectToDraw->rect().topLeft().toPoint();
           this->endPoint = this->rectToDraw->rect().bottomRight().toPoint();
           ui->x1->setText("x1: " + QString::number(this->originPoint.x()));
           ui->y1->setText("y1: " + QString::number(this->originPoint.y(), 10));
           ui->x2->setText("x2: " + QString::number(this->endPoint.x()));
           ui->y2->setText("y2: " + QString::number(this->endPoint.y()));
           break;
       }
    }
    if(this->rectToDraw!=NULL && this->rectToDraw->isUnderMouse()){

        this->auxHeight1 = ((ui->graphicsView->getPoint2().y()) - this->originPoint.y());
        this->auxWidth1 = ((ui->graphicsView->getPoint2().x()) - (this->originPoint.x()));
        this->auxHeight2 = (this->endPoint.y() - ui->graphicsView->getPoint2().y());
        this->auxWidth2 = (this->endPoint.x() - ui->graphicsView->getPoint2().x());
        this->auxTomove = true;
        //this->auxToSelect = true;

        qDebug() << "Aux Width 1"<< this->auxWidth1;

    }
    else{
        this->originPoint = ui->graphicsView->getPoint1(); //top left
        this->endPoint = ui->graphicsView->getPoint2();  //button right
        this->rectToDraw = new QGraphicsRectItem();
        this->rectToDraw->setPen((QPen(Qt::red, 3, Qt::SolidLine)));
    }
}

void MainWindow::mouse_Move()
{
    if(this->scene!=NULL){


        if(this->rectToDraw->isUnderMouse() && this->auxTomove == true){

            this->originPoint.setY((ui->graphicsView->getPoint2().y()) - this->auxHeight1);
            this->originPoint.setX((ui->graphicsView->getPoint2().x()) - this->auxWidth1);
            //qDebug()<< this->endPoint.x();
            this->endPoint.setX((ui->graphicsView->getPoint2().x() + this->auxWidth2));
            this->endPoint.setY((ui->graphicsView->getPoint2().y() + this->auxHeight2));

            ui->graphicsView->setPoint1(this->originPoint);
            ui->graphicsView->setPoint2(this->endPoint);
        }
        else{
            this->endPoint = ui->graphicsView->getPoint2();
        }

        QRect rectangle(this->originPoint, this->endPoint);

        this->scene->addItem(this->rectToDraw);
        this->rectToDraw->setRect(rectangle);

        // Set points in the ui

        ui->x1->setText("x1: " + QString::number(this->originPoint.x()));
        ui->y1->setText("y1: " + QString::number(this->originPoint.y(), 10));
        ui->x2->setText("x2: " + QString::number(ui->graphicsView->getPoint2().x()));
        ui->y2->setText("y2: " + QString::number(ui->graphicsView->getPoint2().y()));

        this->auxToSelect = false;

    }
}

void MainWindow::mouse_Release()
{
  if(this->scene){

      this->endPoint = ui->graphicsView->getPoint2();
      this->imageinput->setCorrespondingPoins(this->originPoint.x(), this->originPoint.y(),
                                              ui->graphicsView->getPoint2().x(), ui->graphicsView->getPoint2().y(),
                                              this->imagePixmap->width(), this->imagePixmap->height());

       qDebug() << QString::number(this->imageinput->rectangleSize());

       if(!this->rects.contains(this->rectToDraw)) this->rects.append(this->rectToDraw);
  }
  this->auxHeight1 = 0;
  this->auxHeight2 = 0;
  this->auxWidth1 = 0;
  this->auxWidth2 = 0;
  this->auxTomove = false;
  //  qDebug() << QString::number( this->scene->sizeframe());
}

void MainWindow::on_ButtonInputRamBits_clicked()
{
    qDebug() <<"Selected" << this->rectToDraw->isSelected();

    bool flag = true;
    if(!(ui->lineInputBits->text().isEmpty())){
        for(int i = 0;i<ui->lineInputBits->text().count();i++){
            if(!ui->lineInputBits->text()[i].isNumber()) flag = false;
        }
        if(flag == true){
            ui->numberRans->setText(QString::number((this->imageinput->rectangleSize())/(ui->lineInputBits->text()).toFloat()));
        }
    }
}

void MainWindow::on_StartTrain_clicked()
{
    QMessageBox msg;
    if(!this->rectToDraw){
        msg.critical(0,"ERROR", "Select an area to be get");
    }
    else{
        int i = 0;
        while(i<50000){
            this->imageinput->getRandomPoint();
            i++;
            qDebug() << i;
       }
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{

    if(ev->key() == Qt::Key_Delete){
        if(this->rectToDraw != NULL){
            this->scene->removeItem(this->rectToDraw);
            this->rects.removeOne(this->rectToDraw);
        }
    }

}

void MainWindow::on_Salve_DBF_triggered()
{
    QMessageBox msg;
    if(this->scene!=NULL){
        QJsonObject object;
        QJsonArray pointsHoles;
        foreach (QGraphicsRectItem *iter, this->rects) {
            QJsonObject objectPoint;
            objectPoint.insert("TopLeft_X", iter->rect().topLeft().x());
            objectPoint.insert("TopLeft_Y", iter->rect().topLeft().y());
            objectPoint.insert("BottonRight_X", iter->rect().bottomRight().x());
            objectPoint.insert("BottonRight_Y", iter->rect().bottomRight().y());

            pointsHoles.append(objectPoint);
        }
        object.insert("name", QJsonValue(ui->imageList->item(this->current)->text()));
        object.insert("number_holes", QJsonValue(this->rects.length()));
        object.insert("points", QJsonArray(pointsHoles));
        qDebug() << object.value("points");

        this->SaveInfo.setObject(object);

        file.setFileName("../Weightless_Neural_Network/JsonFiles/"+ui->imageList->item(this->current)->text().remove(".JPG",Qt::CaseSensitive)+".json");
        if(file.exists()) file.remove();
        file.setFileName("../Weightless_Neural_Network/JsonFiles/"+ui->imageList->item(this->current)->text().remove(".JPG",Qt::CaseSensitive)+".json");
        if(!file.open(QIODevice::ReadWrite)){
            msg.warning(0,"Warning", "Check your image directory!\nDirectory to save: Weightless_Neural_Network/JsonFiles/");
        }

        else{
            file.write(this->SaveInfo.toJson());
            file.close();
            msg.setText("Saved Successfully. To access in "+file.fileName());
            msg.exec();
        }

    }
    else{
        msg.warning(0,"Warning", "Select a image!");
    }

}
