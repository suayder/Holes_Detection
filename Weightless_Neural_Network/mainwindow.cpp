#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputrectanglesize.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stop->setEnabled(false);
    ui->textConsole->setReadOnly(true);
    this->flagToOperating = false;
    this->imageinput = NULL;
    this->imagePixmap = NULL;
    this->rectToDraw = NULL;
    this->network = NULL;
    this->wizardNetwork = NULL;
    this->scene = NULL;
    this->auxTomove = false;
    this->auxToSelect = true;
    QString dir;
    dir = "/home/suayder/Documents/Holes_Detection/Weightless_Neural_Network/dataBaseImages";
    this->directoyimages = QDir(dir);
    this->setListDirectoryImages();
    this->sizeOfRect = QSize(0,0);
    connect(ui->graphicsView, SIGNAL(Mouse_Pressed()), SLOT(mouse_is_clicked()));
    connect(ui->graphicsView, SIGNAL(Mouse_Move()), SLOT(mouse_Move()));
    connect(ui->graphicsView, SIGNAL(Mouse_Released()), SLOT(mouse_Release()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setListDirectoryImages(){ //List all archives in qlistview

    QFileInfoList files = this->directoyimages.entryInfoList();
    ui->imageList->clear();
    foreach (QFileInfo file, files) {
        if(file.isFile()){
            ui->imageList->addItem(file.fileName());
        }
    }
    ui->imageList->sortItems(Qt::AscendingOrder);
}

void MainWindow::on_imageList_activated(const QModelIndex &index)
{
    this->resetAllValues();
    this->current = index.row();
    if(this->imageinput == NULL)
        this->imageinput = new originImageManipulation();
    this->imageinput->imageRead((this->directoyimages.filePath(ui->imageList->currentItem()->text())).toStdString());

    if(ui->Binary_radioButton->isChecked())
        this->imageinput->thresholding();
    if(this->network){
        this->network->setImage(this->imageinput->getImage());
    }

    this->imagePixmap = new QPixmap((this->directoyimages.filePath(ui->imageList->currentItem()->text())));

    if(this->scene) delete this->scene;
    this->scene = new QGraphicsScene(this);
    *this->imagePixmap = this->imagePixmap->scaledToWidth(ui->graphicsView->width(), Qt::SmoothTransformation);
    this->scene->addPixmap(*this->imagePixmap);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_actionLoad_Image_triggered()
{
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory where there are files to train/tracker"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    this->directoyimages.setPath(dir);
    this->setListDirectoryImages();

}

void MainWindow::mouse_is_clicked()
{

    this->rectToDraw = NULL;
    this->auxUpdateRect = 0;

    foreach (QGraphicsRectItem *rect, this->rects){
       if(rect->isUnderMouse()){
           this->rectToDraw = rect;
           this->originPoint = this->rectToDraw->rect().topLeft().toPoint();
           this->endPoint = this->rectToDraw->rect().bottomRight().toPoint();
           this->imageinput->setPointsWithinVector(this->auxUpdateRect);

           ui->x1->setText("x1: " + QString::number(this->imageinput->getTopLeft().x));
           ui->y1->setText("y1: " + QString::number(this->imageinput->getTopLeft().y));
           ui->x2->setText("x2: " + QString::number(this->imageinput->getButtonRight().x));
           ui->y2->setText("y2: " + QString::number(this->imageinput->getButtonRight().y));
           break;
       }
       this->auxUpdateRect++;
    }
    if(this->rectToDraw!=NULL && this->rectToDraw->isUnderMouse()){

        this->auxHeight1 = ((ui->graphicsView->getPoint2().y()) - this->originPoint.y());
        this->auxWidth1 = ((ui->graphicsView->getPoint2().x()) - (this->originPoint.x()));
        this->auxHeight2 = (this->endPoint.y() - ui->graphicsView->getPoint2().y());
        this->auxWidth2 = (this->endPoint.x() - ui->graphicsView->getPoint2().x());
        this->auxTomove = true;

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


        if(this->rectToDraw->isUnderMouse() && this->auxTomove == true){ //when you are moving a rectangle

            this->originPoint.setY((ui->graphicsView->getPoint2().y()) - this->auxHeight1);
            this->originPoint.setX((ui->graphicsView->getPoint2().x()) - this->auxWidth1);
            this->endPoint.setX((ui->graphicsView->getPoint2().x() + this->auxWidth2));
            this->endPoint.setY((ui->graphicsView->getPoint2().y() + this->auxHeight2));

            ui->graphicsView->setPoint1(this->originPoint);
            ui->graphicsView->setPoint2(this->endPoint);

            if(this->network || this->wizardNetwork){
                this->imageinput->setCorrespondingPoins(this->originPoint.x(), this->originPoint.y(),
                                                        this->imagePixmap->width(), this->imagePixmap->height(),
                                                        (ui->Binary_radioButton->isChecked())?this->network->getSizeOfRect():this->wizardNetwork->getBoundingBox(), this->auxUpdateRect);

                if(this->flagToOperating == true){ //Dragging while it's working

                    int r;
                    if(ui->Binary_radioButton->isChecked()){
                        r = this->network->FunctionOfEachRect(this->imageinput->getTopLeft());
                        if(r>=this->network->getRamNumber()*ui->threshold->value())
                            ui->textConsole->setTextColor(QColor(Qt::red));
                        else
                            ui->textConsole->setTextColor(QColor(Qt::black));
                    }
                    else{
                        r = this->wizardNetwork->testBox(this->imageinput->getTopLeft(), this->imageinput->getImage());
                        if(r>=this->wizardNetwork->getDescriptorSize()*ui->threshold->value())
                            ui->textConsole->setTextColor(QColor(Qt::red));
                        else
                            ui->textConsole->setTextColor(QColor(Qt::black));
                    }
                    ui->textConsole->append("Rams fired: "+QString::number(r)+"|"+QString::number((r*100.0)/this->network->getRamNumber()));
                    ui->progressBar->setValue((int)(100.0*r)/this->network->getRamNumber());
                }
            }
            else{
                this->imageinput->setCorrespondingPoins(this->originPoint.x(), this->originPoint.y(),
                                                        this->endPoint.x(), this->endPoint.y(),
                                                        this->imagePixmap->width(), this->imagePixmap->height());
            }
        }
        else{
            this->endPoint = ui->graphicsView->getPoint2(); //Only when is creating a new rectangle

            this->imageinput->setCorrespondingPoins(this->originPoint.x(), this->originPoint.y(),
                                                    this->endPoint.x(), this->endPoint.y(),
                                                    this->imagePixmap->width(), this->imagePixmap->height());
        }

        QRect rectangle(this->originPoint, this->endPoint);

        this->scene->addItem(this->rectToDraw);
        this->rectToDraw->setRect(rectangle);


        // Set points in the ui

        ui->x1->setText("x1: " + QString::number(this->imageinput->getTopLeft().x));
        ui->y1->setText("y1: " + QString::number(this->imageinput->getTopLeft().y));
        ui->x2->setText("x2: " + QString::number(this->imageinput->getButtonRight().x));
        ui->y2->setText("y2: " + QString::number(this->imageinput->getButtonRight().y));
        ui->labelRectSize->setText(QString::number((this->imageinput->rectangleSize())));

        this->auxToSelect = false;

    }
}

void MainWindow::mouse_Release()
{
  if(this->scene){

      if(this->auxToSelect == true){
          ui->graphicsView->setPoint1(this->originPoint);
          ui->graphicsView->setPoint2(this->endPoint);
          this->imageinput->setTopLeft(Point(this->originPoint.x(),this->originPoint.y()));
          this->imageinput->setButtonRight(Point(this->endPoint.x(), this->endPoint.y()));
      }
      if(this->network){
          this->imageinput->setCorrespondingPoins(this->originPoint.x(), this->originPoint.y(), this->imagePixmap->width(),
                                                  this->imagePixmap->height(), this->network->getSizeOfRect(), this->auxUpdateRect);
      }
      else if(this->wizardNetwork){
          this->imageinput->setCorrespondingPoins(this->originPoint.x(), this->originPoint.y(), this->imagePixmap->width(),
                                                  this->imagePixmap->height(), this->wizardNetwork->getBoundingBox(), this->auxUpdateRect);
      }
      else{
          this->imageinput->setCorrespondingPoins(this->originPoint.x(), this->originPoint.y(),
                                                  this->endPoint.x(), this->endPoint.y(),
                                                  this->imagePixmap->width(), this->imagePixmap->height());
      }

       if(!this->rects.contains(this->rectToDraw)){
           this->rects.append(this->rectToDraw);
           this->imageinput->insertRect();
       }

       if(!ui->lineInputBits->text().isEmpty()) ui->numberRans->setText(QString::number((this->imageinput->rectangleSize())/(ui->lineInputBits->text()).toFloat()));


  }

  this->auxHeight1 = 0;
  this->auxHeight2 = 0;
  this->auxWidth1 = 0;
  this->auxWidth2 = 0;
  this->auxTomove = false;
  this->auxToSelect = true;


}

void MainWindow::on_start_clicked()
{
    QMessageBox msg;
    ui->stop->setEnabled(true);

        if(ui->trainig->isChecked()){
            if(!this->rectToDraw){
                msg.critical(0,"ERROR", "Select an area to be get");
            }
            else{
                if(!this->rects.isEmpty()){
                    this->sizeOfRect.setHeight(this->rectToDraw->rect().height());
                    this->sizeOfRect.setWidth(this->rectToDraw->rect().width());
                }
                if(this->sizeOfRect.isNull()){
                    msg.warning(0,"Warning", "You should to set a parttern size in rectangle");
                    msg.exec();
                }
                else{
                    if(!this->network && !this->wizardNetwork)
                        ui->actionNew_Descriptor->trigger();
                    ui->textConsole->setText("Wait...");
                    QApplication::processEvents();
                    try{
                        if(ui->Binary_radioButton->isChecked()){
                            this->network->training();
                            this->network->p();
                        }
                        else{
                            this->wizardNetwork->training(this->imageinput->getTopLeft(), this->imageinput->getImage());
                        }
                    }
                    catch(exception& e){
                        ui->textConsole->setText("ERROR, EXCEPTION: " + QString(e.what()));
                    }
                    ui->textConsole->setText("Done!");
                }
            }
            ui->stop->setEnabled(false);
        }
        else if(ui->operation->isChecked()){
            if(!this->network && !this->wizardNetwork){
                msg.setText("You have to set a descriptor");
                msg.exec();
            }
            else{
                uint r;
                if(ui->Binary_radioButton->isChecked()){
                    r = this->network->FunctionOfEachRect(this->imageinput->getTopLeft());
                    if(r>=this->network->getRamNumber()*ui->threshold->value())
                        ui->textConsole->setTextColor(QColor(Qt::red));
                    else
                        ui->textConsole->setTextColor(QColor(Qt::black));
                }
                else{
                    r = this->wizardNetwork->testBox(this->imageinput->getTopLeft(), this->imageinput->getImage());

                    if(r>=this->wizardNetwork->getDescriptorSize()*ui->threshold->value())
                        ui->textConsole->setTextColor(QColor(Qt::red));
                    else
                        ui->textConsole->setTextColor(QColor(Qt::black));
                }

                ui->textConsole->append("Rams fired: "+QString::number(r));

                this->flagToOperating = true;
            }
        }
        else{ //Tracker is selected
            //TODO: Implementar orientação a objetos aqui. Crie uma superclasse chamada classificador ou rede neural sem peso.
            // A rede neural wisard binária ou rankeada devem ser filhas desta outra de modo que o código a seguir não precise
            // ficar repetido.
            if(ui->Gray_radioButton->isChecked() ){
                ui->textConsole->setText("Wait...");
                QApplication::processEvents();

                this->wizardNetwork->tracker(this->imageinput->getImage(), String("$HOME/Documents/Holes_Detection/Weightless_Neural_Network/"+ui->imageList->currentItem()->text().toStdString()));

                ui->textConsole->setText("Done and saved result!");
            }else{

                ui->textConsole->setText("Wait...");
                QApplication::processEvents();

                this->network->tracker(this->imageinput->getImage(), String("$HOME/Documents/Holes_Detection/Weightless_Neural_Network/"+ui->imageList->currentItem()->text().toStdString()));

                ui->textConsole->setText("Done and saved result!");
            }
            msg.warning(0, "Warning","Select a Status Mode");
        }
}

void MainWindow::on_stop_clicked()
{
    this->flagToOperating = false;
    ui->stop->setEnabled(false);
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{

    if(ev->key() == Qt::Key_Delete){
        if(this->rectToDraw != NULL){
            this->scene->removeItem(this->rectToDraw);
            this->rects.removeOne(this->rectToDraw);
            if(!this->rects.isEmpty()){ //Change the variables values and set the new labels

                this->rectToDraw = this->rects.last();
                ui->graphicsView->setPoint1(this->rectToDraw->rect().toRect().topLeft());
                ui->graphicsView->setPoint2(this->rectToDraw->rect().toRect().bottomRight());
                this->originPoint = ui->graphicsView->getPoint1(); //top left
                this->endPoint = ui->graphicsView->getPoint2(); //Botton ringht
                ui->x1->setText("x1: " + QString::number(this->originPoint.x()));
                ui->y1->setText("y1: " + QString::number(this->originPoint.y(), 10));
                ui->x2->setText("x2: " + QString::number(ui->graphicsView->getPoint2().x()));
                ui->y2->setText("y2: " + QString::number(ui->graphicsView->getPoint2().y()));
                if(ui->lineInputBits->text() != "") ui->numberRans->setText(QString::number((this->imageinput->rectangleSize())/(ui->lineInputBits->text()).toFloat()));
                this->imageinput->delLastVR();
            }
            else{
                ui->numberRans->setText("");
                ui->x1->setText("x1: ");
                ui->y1->setText("y1: ");
                ui->x2->setText("x2: ");
                ui->y2->setText("y2: ");
                this->rectToDraw = NULL;
            }
        }
    }
    if(ev->key() == Qt::Key_N){
        ui->actionNew->trigger();
    }

}

void MainWindow::on_Salve_json_triggered()
{
    QMessageBox msg;
    if(this->scene!=NULL){
        QJsonObject object;
        QJsonArray pointsHoles;
        foreach (auto iter, this->imageinput->getVr()) {
            QJsonObject objectPoint;
            objectPoint.insert("TopLeft_X", iter.first.x);
            objectPoint.insert("TopLeft_Y", iter.first.y);
            objectPoint.insert("BottonRight_X", iter.second.x);
            objectPoint.insert("BottonRight_Y", iter.second.y);

            pointsHoles.append(objectPoint);
        }
        object.insert("name", QJsonValue(ui->imageList->item(this->current)->text()));
        object.insert("width", this->imageinput->getImage().cols);
        object.insert("heidth", this->imageinput->getImage().rows);
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

void MainWindow::on_actionNew_triggered() //New rectangle
{
    if(this->sizeOfRect!=QSize(0,0)){

        this->rectToDraw = new QGraphicsRectItem();
        this->rectToDraw->setPen((QPen(Qt::red, 3, Qt::SolidLine)));
        QRect rectangle(QPoint(0,0), this->sizeOfRect);
        this->scene->addItem(this->rectToDraw);
        this->rectToDraw->setRect(QRectF(rectangle));

        //this->endPoint = this->rectToDraw->rect().bottomRight().toPoint();
        this->imageinput->setTopLeft(Point(0,0));
        (ui->Binary_radioButton->isChecked())?this->imageinput->setButtonRight(Point(this->network->getSizeOfRect().width,this->network->getSizeOfRect().height)):
                                              this->imageinput->setButtonRight(Point(this->wizardNetwork->getBoundingBox().width,this->wizardNetwork->getBoundingBox().height));
        //qDebug()<<this->imageinput->getButtonRight().x<<this->imageinput->getButtonRight().y;
        //this->imageinput->setCorrespondingPoins(0, 0, this->endPoint.x(), this->endPoint.y(),
         //                                       this->imagePixmap->width(), this->imagePixmap->height());
        this->set_BottomRight_topLeft_Points(this->rectToDraw->rect().topLeft().toPoint(), this->rectToDraw->rect().bottomRight().toPoint());
        this->rects.append(this->rectToDraw);
        this->imageinput->insertRect();
        if(!ui->lineInputBits->text().isEmpty()) ui->numberRans->setText(QString::number((this->imageinput->rectangleSize())/(ui->lineInputBits->text()).toFloat()));
    }
    else{
        QMessageBox m;
        m.warning(0,"Warning", "You forgot to set a size");
    }
}

void MainWindow::on_trainig_clicked()
{
    ui->start->setText("Start Train");
    ui->stop->setText("Stop Train");
}

void MainWindow::on_operation_clicked()
{
    ui->start->setText("Start Working");
    ui->stop->setText("Stop Working");
}

void MainWindow::on_tracker_clicked()
{
    ui->start->setText("Start Tracking");
    ui->stop->setText("Stop Tracking");
}

void MainWindow::on_actionSet_a_Size_triggered()
{
    InputRectangleSize r;
    (this->imagePixmap)?r.setMaximumSizes(this->imagePixmap->height(), this->imagePixmap->width()):r.setMaximumSizes(ui->graphicsView->height(), ui->graphicsView->width());
    r.inputSize(&(this->sizeOfRect));
    r.setModal(true);
    r.exec();
    if(this->network) this->network->setSizeOfRect(this->sizeOfRect.width(), this->sizeOfRect.height(), this->imagePixmap->width(), this->imagePixmap->height());
}

void MainWindow::on_actionNew_Descriptor_triggered()
{
    QMessageBox msg;

    //I will need this code to do a function to set a new wizard

    /*delete this->imageinput;
    if(!this->network){
        delete this->network;
        this->network = NULL;
    }
    else{
        delete this->wizardNetwork;
        this->wizardNetwork = NULL;
    }
    delete this->imagePixmap;
    this->imagePixmap = NULL;
    delete this->scene;
    this->scene = NULL;
    delete this->rectToDraw;
    this->rectToDraw = NULL;
    this->rects.clear();
    this->sizeOfRect.setHeight(0);
    this->sizeOfRect.setWidth(0);
    this->originPoint.setX(0);
    this->originPoint.setY(0);
    this->endPoint.setX(0);
    this->endPoint.setY(0);*/

    if(ui->Binary_radioButton->isChecked()){
        if(this->network == NULL){
            this->imageinput->thresholding();
            if(this->sizeOfRect!=QSize(0,0)){
//                this->network = new Descriptor(Size(this->sizeOfRect.width()*(this->imageinput->getImageSize().width/this->imagePixmap->width()),
//                                                    this->sizeOfRect.height()*(this->imageinput->getImageSize().height/this->imagePixmap->height())),
//                                               ui->lineInputBits->text().toUInt(), &this->imageinput);
                this->network = new Discriminator(Size(this->imageinput->getRectWidth(),this->imageinput->getRecHeight()),
                                               ui->lineInputBits->text().toUInt(), &this->imageinput);
            }
            else
                this->network = new Discriminator(ui->lineInputBits->text().toUInt(), &this->imageinput);
        }
        else{
            msg.warning(0,"Already Exist", "Watch out!, Already Exist a Descriptor");
        }
    }
    else{
        if(this->wizardNetwork == NULL){
            if(this->sizeOfRect!=QSize(0,0))
                this->wizardNetwork = new RankWisard(ui->lineInputBits->text().toUInt(), cv::Size(this->imageinput->getRectWidth(), this->imageinput->getRecHeight()));
            else
                msg.warning(0,"No Rectangle setted", "Watch out!, you have to set a rectangle size");
        }
        else{
            msg.warning(0,"Already Exist", "Watch out!, Already Exist a Descriptor");
        }
    }
}

void MainWindow::on_lineInputBits_textEdited(const QString &arg1)
{
    QMessageBox msg;
    bool flag = true;
    if(!(ui->lineInputBits->text().isEmpty())){
        for(int i = 0;i<ui->lineInputBits->text().count();i++){ //If there is a non number in array
            if(!ui->lineInputBits->text()[i].isNumber()){
                flag = false;
                msg.warning(0, "Warning", "There is a non number, check please!");
                break;
            }
        }
        if(flag == true){
            if(this->imagePixmap!=NULL)
                ui->numberRans->setText(QString::number((this->imageinput->rectangleSize())/arg1.toFloat()));
        }
    }
    else{
        msg.warning(0, "Warning", "Fill out this field!");
    }
}

void MainWindow::on_actionSave_new_WNN_triggered()
{
    QMessageBox msg;
    QJsonObject object;
    QJsonArray ar;
    vector<unsigned int> vet = this->network->getRetinalOrdering();
    if(this->network) {
        this->network->saveNetwork();
        object.insert("width", this->network->getSizeOfRect().width);
        object.insert("numberOfInputsInRam", int(this->network->getRamNumberOfInputs()));
        object.insert("height", this->network->getSizeOfRect().height);

        for(auto& v:vet){
            ar.append(int(v));
        }
        object.insert("retinalOrdering", ar);
        this->SaveInfo.setObject(object);
        file.setFileName("../Weightless_Neural_Network/fileSalved/configurationFile.json");
        msg.setText("Successful");
        msg.exec();

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
}

void MainWindow::on_Load_WNN_triggered()
{
    QMessageBox msg;
    QJsonDocument dJson;
    vector<unsigned int> arrayjson;
    if(!this->network){
        this->network = new Discriminator();
    }
    try{
        this->network->load_a_map();
        if(!this->file.open(QIODevice::ReadOnly)){
            msg.setText("Something wrong to read file");
            msg.exec();
        }
        else{
            this->file.setFileName("../Weightless_Neural_Network/fileSalved/configurationFile.json");
            dJson = QJsonDocument::fromJson(this->file.readAll());
            QJsonObject object = dJson.object();
            this->network->setSizeOfRect(object["width"].toInt(), object["height"].toInt());
            this->network->setRamNumberOfInputs(object["numberOfInputsInRam"].toInt());
            QJsonArray jsonarray = object["retinalOrdering"].toArray();
            for(auto ar:jsonarray){
                arrayjson.push_back(ar.toInt());
            }
            this->network->set_retine(arrayjson);
        }
    }
    catch(...){
        msg.setText("ERROR, Exception ocurred on open wwn");
        msg.exec();
    }
}

void MainWindow::resetAllValues()
{
    delete this->imagePixmap;
    this->imagePixmap = NULL;
    delete this->imageinput;
    this->imageinput = NULL;
    delete this->rectToDraw;
    this->rectToDraw = NULL;
    this->rects.clear();
    this->set_BottomRight_topLeft_Points(QPoint(0,0), QPoint(0,0));
    this->auxTomove = false;
    this->auxToSelect = true;
    ui->stop->click();

    ui->graphicsView->setPoint1(QPoint(0,0));
    ui->graphicsView->setPoint2(QPoint(0,0));
}

void MainWindow::set_BottomRight_topLeft_Points(QPoint _P1, QPoint _P2)
{
    this->originPoint = _P1;
    this->endPoint = _P2;
    if(this->endPoint!=QPoint(0,0)){
        ui->x1->setText("x1: "+QString::number(this->imageinput->getTopLeft().x));
        ui->x2->setText("x2: "+QString::number(this->imageinput->getButtonRight().x));
        ui->y2->setText("y2: "+QString::number(this->imageinput->getButtonRight().y));
        ui->y1->setText("y1: "+QString::number(this->imageinput->getTopLeft().y));
    }
    else{
        ui->x1->setText("x1: "+QString::number(0));
        ui->x2->setText("x2: "+QString::number(0));
        ui->y2->setText("y2: "+QString::number(0));
        ui->y1->setText("y1: "+QString::number(0));
    }
    /*if(this->network && this->network->p()>0) ui->hashNumber->setText("Rect Size: " + QString::number(ui->graphicsView->sizeframe()) + " - Hash: " + QString::number(this->network->p()));
    else{
        ui->hashNumber->setText("");
        ui->hashNumber->setText("Rect Size: " + QString::number(ui->graphicsView->sizeframe()));
    }*/
}

void MainWindow::set_image_to_tracker(int row)
{
    this->resetAllValues();
    ui->imageList->setCurrentRow(row);
    if(this->imageinput == NULL)
        this->imageinput = new originImageManipulation();
    this->imageinput->imageRead((this->directoyimages.filePath(ui->imageList->currentItem()->text())).toStdString());
    if(ui->Binary_radioButton->isChecked()){
        this->imageinput->thresholding();
        if(this->network){
            this->network->setImage(this->imageinput->getImage());
        }
    }

    this->imagePixmap = new QPixmap((this->directoyimages.filePath(ui->imageList->currentItem()->text())));
    if(!this->scene) this->scene = new QGraphicsScene(this);
    *this->imagePixmap = this->imagePixmap->scaledToWidth(ui->graphicsView->width(), Qt::SmoothTransformation);
    this->scene->addPixmap(*this->imagePixmap);
    ui->graphicsView->setScene(this->scene);
}

void MainWindow::on_bottonSetInputs_clicked()
{
    QMessageBox msg;
    if((this->network!=NULL && this->wizardNetwork!=NULL) || ui->labelRectSize->text().isEmpty()){
        msg.warning(0, "Warning", "Verify if any field is missing or already exist a discriminator");
    }
    else{
        this->sizeOfRect.setHeight(this->endPoint.y() - this->originPoint.y());
        qDebug()<<"H: "<<(int)(this->rectToDraw->rect().height()*(this->imageinput->getImageSize().height/(double)this->imagePixmap->height()));
        this->sizeOfRect.setWidth(this->endPoint.x() - this->originPoint.x());
        qDebug()<<"W: "<<(int)(this->rectToDraw->rect().width()*(this->imageinput->getImageSize().width/(double)this->imagePixmap->width()));
        if(ui->Binary_radioButton->isChecked()){
            this->imageinput->thresholding();
            this->network = new Discriminator(Size(this->imageinput->getRectWidth(),//this->sizeOfRect.width()*(this->imageinput->getImageSize().width/(double)this->imagePixmap->width()),
                                            this->imageinput->getRecHeight()),
                                           ui->lineInputBits->text().toInt(), &this->imageinput);
        }

        else{
            this->wizardNetwork = new RankWisard(ui->lineInputBits->text().toUInt(), cv::Size(this->imageinput->getRectWidth(), this->imageinput->getRecHeight()));
        }
        qDebug()<<"size rect: "<< this->imageinput->rectangleSize();
        ui->lineInputBits->setReadOnly(true);

        ui->bottonSetInputs->setEnabled(false);
        ui->Binary_radioButton->setEnabled(false);
        ui->Gray_radioButton->setEnabled(false);

    }
}

void MainWindow::on_actionStartTracker_triggered()
{
    QMessageBox msg;

    vector<QPoint> vectorOfPoints;
    vector<QPoint> vectorEndPoints;
    //msg.warning(0, "Image type", "Attention, the image type must be just jpg");

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory where there are files to train"),
                                                 "/home/suayder/Documents/Repository/Holes_Detection/Weightless_Neural_Network/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!this->openFolder(dir)){
        msg.critical(0,"Not Found Directory", "Check your directory, there is some error");
    }
    else{
        QStringList nameFiles = this->getListOfNames(); //Herance to imagejson class
        this->network = new Discriminator(Size(this->averageWidth(), this->averageHeigh()),ui->lineInputBits->text().toUInt(),&this->imageinput);
        ui->lineInputBits->setReadOnly(true);

        ui->textConsole->setText("Wait...");
        QApplication::processEvents();

        int widthRect = this->network->getSizeOfRect().width;
        int heidthRect = this->network->getSizeOfRect().height;
        int dx,dy;
        int widthOfImageRect, heidthOfImageRect;
        coordinates cx, cy;

        Mat imAux;
        if(!QDir(dir+"/treinedImages").exists()){
            qDebug()<<dir;
            QDir().mkdir(dir+"/treinedImages");
        }

        for(auto names:nameFiles){
            int cont = 0;
            for(int i = 0; i<ui->imageList->count();i++){ //Will search in list of images names that there is on list in user interface
                if(ui->imageList->item(i)->text()==names+".JPG" ||
                    ui->imageList->item(i)->text()==names+".jpg" ||
                    ui->imageList->item(i)->text()==names+".png")
                {
                    ui->imageList->setCurrentRow(i);
                    this->set_image_to_tracker(i);//next step is get a array with points
                     imAux = this->imageinput->getImage().clone();
                    try{
                        vectorOfPoints = this->searchPoints(names); //Class imageJson
                        vectorEndPoints = this->searchEndPoints(names);
                        if(vectorOfPoints.empty() || vectorEndPoints.empty())
                            throw std::invalid_argument("This image doesn't have market points");

                        for(int i = 0; i<vectorOfPoints.size(); i++){
                            //See the case where the sum point and average to get last point will not be larger then last point of the image
                            widthOfImageRect = vectorEndPoints[i].x() - vectorOfPoints[i].x();
                            heidthOfImageRect = vectorEndPoints[i].y() - vectorOfPoints[i].y();
                            qDebug()<< "widthOfImageRect "<<widthOfImageRect;
                            qDebug()<< "heidthOfImageRect "<<heidthOfImageRect;
                            dx = widthOfImageRect - widthRect;
                            dy = heidthOfImageRect - heidthRect;

                            cx = vectorOfPoints[i].x();
                            cy = vectorOfPoints[i].y();

                            this->imageinput->setTopLeft(Point(cx, cy));
                            this->imageinput->setButtonRight(Point(cx+widthOfImageRect, cy+heidthOfImageRect));
                            this->imageinput->insertRect();

                            //Crop and resize rect
                            imAux = this->imageinput->getImage()(cv::Rect(vectorOfPoints[i].x(),vectorOfPoints[i].y(),widthOfImageRect, heidthOfImageRect));
                            cv::resize(imAux, imAux,Size(this->averageWidth(), this->averageHeigh()));
                            if(ui->Binary_radioButton->isChecked()){
                                this->network->training(imAux);
                                this->network->p();
                            }

                            else{
                                this->wizardNetwork->training(imAux);
                            }

                            this->imageinput->imageWrite(dir.toStdString()+"/treinedImages/"+names.toStdString()+"_"+QString::number(cont).toStdString()+".JPG", imAux);
                            cont++;
                        }
                    }//To do a part of recognize rect and
                    catch(std::invalid_argument s){
                        ui->textConsole->setText("Something wrong");
                        msg.warning(0, "Not Holes", s.what());
                    }

                    break;
                }
            }
        }
        this->sizeOfRect = QSize(this->averageWidth()*(this->imagePixmap->width()/(double)this->imageinput->getWidthOfImage()),
                                 this->averageHeigh()*(this->imagePixmap->width()/(double)this->imageinput->getHeightOfImage()));

        ui->textConsole->setText("Done");
        QApplication::processEvents();
    }
    //Now will repeat this code but will tracker in each image (very slowly)

    dir.clear();
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory where there are files to tracker"),
                                                 "/home/suayder/Documents/Holes_Detection/Weightless_Neural_Network/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!this->openFolder(dir)){
        msg.critical(0,"Not Found Directory", "Check your directory, there is some error");
    }

    else{
        if(!QDir(dir+"/resultImages").exists()){
            qDebug()<<dir;
            QDir().mkdir(dir+"/resultImages");
        }
        QStringList nameFiles = this->getListOfNames(); //Herance to imagejson class
        qDebug()<<"1";

        ui->textConsole->setText("Wait...");
        QApplication::processEvents();

        for(QString names:nameFiles){ //Walks for all images in directory json file
            qDebug()<<"2";
            for(int i = 0; i<ui->imageList->count();i++){ //Will search in list of images names that there is on list in user interface
                if(ui->imageList->item(i)->text()==names+".JPG" ||
                    ui->imageList->item(i)->text()==names+".jpg" ||
                    ui->imageList->item(i)->text()==names+".png")
                {
                    ui->imageList->setCurrentRow(i);
                    this->set_image_to_tracker(i);//next step is get a array with points

                    //mandar esperar para setar a imagem no scene

                    vector<Rect> sSearch_algorithm = selectiveSearch((this->directoyimages.filePath(ui->imageList->currentItem()->text())).toStdString());

                    if(ui->Binary_radioButton->isChecked()){
                        this->network->recognize(this->imageinput->getImage(),sSearch_algorithm ,(dir.toStdString()+"/resultImages/"+names.toStdString()+".jpg"), ui->threshold->value());
                    }
                    else
                        this->wizardNetwork->_tracker_ssearch(this->imageinput->getImage(), sSearch_algorithm , (dir.toStdString()+"/resultImages/"+names.toStdString()+".jpg"), ui->threshold->value());
                    qDebug()<<"4";

                    break;
                }
            }
        }
        ui->textConsole->setText("Done");
        QApplication::processEvents();
    }
}

void MainWindow::on_actionTracker_triggered()
{
    QMessageBox msg;
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory where there are files to tracker"),
                                                 "/home/suayder/Documents/Holes_Detection/Weightless_Neural_Network/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!this->openFolder(dir)){
        msg.critical(0,"Not Found Directory", "Check your directory, there is some error");
    }

    else{
        QStringList nameFiles = this->getListOfNames(); //Herance to imagejson class
        qDebug()<<"1";

        ui->textConsole->setText("Wait...");
        QApplication::processEvents();

        if(!QDir(dir+"/resultImages").exists()){
            qDebug()<<dir;
            QDir().mkdir(dir+"/resultImages");
        }

        for(QString names:nameFiles){ //Walks for all images in directory json file
            qDebug()<<"2";
            for(int i = 0; i<ui->imageList->count();i++){ //Will search in list of images names that there is on list in user interface
                if(ui->imageList->item(i)->text()==names+".JPG" ||
                    ui->imageList->item(i)->text()==names+".jpg" ||
                    ui->imageList->item(i)->text()==names+".png")
                {
                    ui->imageList->setCurrentRow(i);
                    this->set_image_to_tracker(i);//next step is get a array with points

                    //mandar esperar para setar a imagem no scene

                    vector<Rect> sSearch_algorithm = selectiveSearch((this->directoyimages.filePath(ui->imageList->currentItem()->text())).toStdString());

                    if(ui->Binary_radioButton->isChecked()){
                        this->network->recognize(this->imageinput->getImage(),sSearch_algorithm ,(dir.toStdString()+"/resultImages/"+names.toStdString()+".jpg"), ui->threshold->value());
                    }
                    else
                        this->wizardNetwork->_tracker_ssearch(this->imageinput->getImage(), sSearch_algorithm , (dir.toStdString()+"/resultImages/"+names.toStdString()+".jpg"), ui->threshold->value());

                    break;
                }
            }
        }
        ui->textConsole->setText("Done");
        QApplication::processEvents();
    }

}

void MainWindow::on_actionTrain_triggered()
{
    QMessageBox msg;

    vector<QPoint> vectorOfPoints;
    vector<QPoint> vectorEndPoints;

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory where there are files to train"),
                                                 "$HOME/Documents/Holes_Detection/Weightless_Neural_Network/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    if(!this->openFolder(dir)){
        msg.critical(0,"Not Found Directory", "Check your directory, there is some error");
    }
    else{
        QStringList nameFiles = this->getListOfNames(); //Herance to imagejson class

        //--------Set values in user interface -------------
        ui->labelRectSize->setText(QString::number(this->averageHeigh()*this->averageWidth()));
        ui->numberRans->setText(QString::number((this->averageHeigh()*this->averageWidth())/ui->numberRans->text().toDouble()));
        //---------------------------------------------------

        if(ui->Binary_radioButton->isChecked())
            this->network = new Discriminator(Size(this->averageWidth(), this->averageHeigh()),ui->lineInputBits->text().toUInt(),&this->imageinput);
        else
            this->wizardNetwork = new RankWisard(ui->lineInputBits->text().toUInt(), Size(this->averageWidth(), this->averageHeigh()));
        ui->lineInputBits->setReadOnly(true);

        ui->textConsole->setText("Wait...");
        QApplication::processEvents();

        //To get bounging box size
        int widthRect = (ui->Binary_radioButton->isChecked())?this->network->getSizeOfRect().width:this->wizardNetwork->getBoundingBox().width;
        int heidthRect = (ui->Binary_radioButton->isChecked())?this->network->getSizeOfRect().height:this->wizardNetwork->getBoundingBox().height;

        int dx,dy;
        int widthOfImageRect, heidthOfImageRect;
        coordinates cx, cy;

        Mat imAux;

        for(auto names:nameFiles){
            for(int i = 0; i<ui->imageList->count();i++){ //Will search in list of images names that there is on list in user interface
                if(ui->imageList->item(i)->text()==names+".JPG" ||
                    ui->imageList->item(i)->text()==names+".jpg" ||
                    ui->imageList->item(i)->text()==names+".png")
                {

                    ui->imageList->setCurrentRow(i);
                    //the bellow function is to set some variables and set in scene
                    this->set_image_to_tracker(i);

                    try{
                        vectorOfPoints = this->searchPoints(names); //Class imageJson
                        vectorEndPoints = this->searchEndPoints(names);
                        if(vectorOfPoints.empty() || vectorEndPoints.empty())
                            throw std::invalid_argument("This image doesn't have market points");

                        int cont = 0;
                        if(!QDir(dir+"/treinedImages").exists()){
                            qDebug()<<dir;
                            QDir().mkdir(dir+"/treinedImages");
                        }
                        for(int i = 0; i<vectorOfPoints.size(); i++){
                            //See the case where the sum point and average to get last point will not be larger then last point of the image
                            widthOfImageRect = vectorEndPoints[i].x() - vectorOfPoints[i].x();
                            heidthOfImageRect = vectorEndPoints[i].y() - vectorOfPoints[i].y();
                            qDebug()<< "widthOfImageRect: "<<widthOfImageRect;
                            qDebug()<< "heidthOfImageRect: "<<heidthOfImageRect;
                            dx = widthOfImageRect - widthRect;
                            dy = heidthOfImageRect - heidthRect;

                            cx = vectorOfPoints[i].x();
                            cy = vectorOfPoints[i].y();

                            this->imageinput->setTopLeft(Point(cx, cy));
                            this->imageinput->setButtonRight(Point(cx+widthOfImageRect, cy+heidthOfImageRect));
                            this->imageinput->insertRect();

                            //Crop and resize rect
                            imAux = this->imageinput->getImage()(cv::Rect(vectorOfPoints[i].x(),vectorOfPoints[i].y(),widthOfImageRect, heidthOfImageRect));
                            cv::resize(imAux, imAux,Size(this->averageWidth(), this->averageHeigh()));
                            if(ui->Binary_radioButton->isChecked()){
                                this->network->training(imAux);
                                this->network->p();
                            }

                            else{
                                this->wizardNetwork->training(imAux);
                            }

                            this->imageinput->imageWrite(dir.toStdString()+"/treinedImages/"+names.toStdString()+"_"+QString::number(cont).toStdString()+".JPG", imAux);
                            cont++;
                        }
                    }//To do a part of recognize rect and
                    catch(std::invalid_argument s){
                        ui->textConsole->setText("Something wrong");
                        msg.warning(0, "Not Holes", s.what());
                    }

                    break;
                }
            }
        }
        this->sizeOfRect = QSize(this->averageWidth()*(this->imagePixmap->width()/(double)this->imageinput->getWidthOfImage()),
                                 this->averageHeigh()*(this->imagePixmap->width()/(double)this->imageinput->getHeightOfImage()));

        ui->textConsole->setText("Done");
        QApplication::processEvents();
    }
}

void MainWindow::on_actionTracker_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/suayder", tr("Image Files (*.png *.jpg *.bmp)"));

    this->resetAllValues();
    if(this->imageinput == NULL)
        this->imageinput = new originImageManipulation();
    this->imageinput->imageRead(fileName.toStdString());

    if(ui->Binary_radioButton->isChecked())
        this->imageinput->thresholding();
    if(ui->Binary_radioButton->isChecked() && this->network){
        this->network->setImage(this->imageinput->getImage());
    }

    this->imagePixmap = new QPixmap(fileName);

    if(this->scene) delete this->scene;
    this->scene = new QGraphicsScene(this);
    *this->imagePixmap = this->imagePixmap->scaledToWidth(ui->graphicsView->width(), Qt::SmoothTransformation);
    this->scene->addPixmap(*this->imagePixmap);
    ui->graphicsView->setScene(scene);
    
    vector<Rect> sSearch_algorithm = selectiveSearch((this->directoyimages.filePath(ui->imageList->currentItem()->text())).toStdString());
    
    String pathToSave = QFileDialog::getOpenFileName(this,
        tr("Choose where do you want to save this image"), "/home/suayder").toStdString();

    if(ui->Binary_radioButton->isChecked()){
        this->network->recognize(this->imageinput->getImage(),sSearch_algorithm ,pathToSave, ui->threshold->value());
    }
    else
        this->wizardNetwork->_tracker_ssearch(this->imageinput->getImage(), sSearch_algorithm , pathToSave, ui->threshold->value());

}
