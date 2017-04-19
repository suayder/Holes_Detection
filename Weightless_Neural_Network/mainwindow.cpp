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
    this->rectToDraw = NULL;
    this->imageinput = NULL;
    this->directoyimages = QDir("../Weightless_Neural_Network/dataBaseImages");
    this->setListDirectoryImages();
    connect(ui->graphicsView, SIGNAL(Mouse_Pressed()), SLOT(mouse_current_position()));
    connect(ui->graphicsView, SIGNAL(Mouse_Move()), SLOT(mouse_Move()));
    connect(ui->graphicsView, SIGNAL(Mouse_Released()), SLOT(mouse_Release()));
//    connect(this->scene ,SIGNAL(Mouse_Pressed()), SLOT(mouse_current_position()));
//    connect(this->scene, SIGNAL(Mouse_Move()), SLOT(mouse_Move()));
//    connect(this->scene, SIGNAL(Mouse_Released()), SLOT(mouse_Release()));
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
    this->imageinput = new originImageManipulation();
    this->imageinput->imageRead((this->directoyimages.filePath(ui->imageList->currentItem()->text())).toStdString());
    this->imageinput->thresholding();

    this->imagePixmap = new QPixmap((this->directoyimages.filePath(ui->imageList->currentItem()->text())));
    this->scene = new QGraphicsScene(this);
    //this->scene->addPixmap((this->imagePixmap)->scaledToWidth(ui->graphicsView->width(), Qt::SmoothTransformation));
    this->scene->addPixmap(*(this->imagePixmap));
    ui->graphicsView->setScene(scene);
}

void MainWindow::mouse_current_position()
{
    //qDebug() <<"SIZE: "<< QString::number( this->scene->sizeframe());
    this->originPoint = ui->graphicsView->getPoint1();
}

void MainWindow::mouse_Release()
{
  qDebug() << QString::number( ui->graphicsView->sizeframe());
  //  qDebug() << QString::number( this->scene->sizeframe());
}

void MainWindow::mouse_Move()
{
    if(this->scene!=NULL){
        if(!this->rectToDraw){
            this->rectToDraw = new QGraphicsRectItem();
            this->rectToDraw->setPen((QPen(Qt::red, 3, Qt::SolidLine)));
            //this->originPoint = ui->graphicsView->getPoint1();
        }

        //this->originPoint = this->scene->getPoint1();
        QRect rectangle(this->originPoint, ui->graphicsView->getPoint2());
        //QRect rectangle(this->originPoint.x(), this->originPoint.y(), this->scene->getPoint2().x(), this->scene->getPoint2().y());

        this->rectToDraw->setRect(rectangle);
        this->scene->addItem(this->rectToDraw);
        qDebug() << "GRAZADEUS";
        //QRect rectangle((ui->graphicsView->getPoint1().x()), (ui->graphicsView->getPoint1().y()), (ui->graphicsView->getPoint2().x()), (ui->graphicsView->getPoint2().y()));
    }
}

void MainWindow::on_ButtonInputRamBits_clicked()
{

    bool flag = true;
    if(!(ui->lineInputBits->text().isEmpty())){
        for(int i = 0;i<ui->lineInputBits->text().count();i++){
            if(!ui->lineInputBits->text()[i].isNumber()) flag = false;
        }
        if(flag == true){
            ui->numberRans->setText(QString::number((ui->graphicsView->sizeframe())/(ui->lineInputBits->text()).toFloat()));
            //ui->numberRans->setText(QString::number((this->scene->sizeframe())/(ui->lineInputBits->text()).toFloat()));
        }
    }
}
